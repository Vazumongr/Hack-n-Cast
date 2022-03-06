// Troy Records Jr. 2021

#include "UE5Testing/Characters/MYCharacterBase.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "UE5Testing/AbilitySystem/MYAbilitySystemComponent.h"
#include "UE5Testing/AbilitySystem/AttributeSets/MYAttributeSet.h"
#include "UE5Testing/Actors/Weapons/MYWeaponBase.h"
#include "UE5Testing/Components/ActorComponents/MYInventoryComponent.h"
#include "UE5Testing/Controllers/MYEnemyController.h"
#include "UE5Testing/DataAssets/MYAbilityDataAsset.h"
#include "UE5Testing/GameModes/MYSurvivalGameMode.h"
#include "UE5Testing/GameStates/MYSurvivalGameState.h"
#include "UE5Testing/UI/MYOverheadHealthBarComponent.h"
#include "UE5Testing/UI/MYOverheadHealthBarWidget.h"

AMYCharacterBase::AMYCharacterBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMYAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Mixed;

	AttributeSet = CreateDefaultSubobject<UMYAttributeSet>(TEXT("AttributeSet"));

	OverheadHealthBar = CreateDefaultSubobject<UMYOverheadHealthBarComponent>(TEXT("OverheadHealthBar"));
	OverheadHealthBar->SetupAttachment(RootComponent);

	InventoryComponent = CreateDefaultSubobject<UMYInventoryComponent>(TEXT("InventoryComponent"));
	if(InventoryComponent)
	{
		InventoryComponent->SetIsReplicated(true);
	}
}

void AMYCharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMYCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	SetupAttributeCallbacks();
	if (HasAuthority())
	{
		SpawnWeaponsOnServer(0);
	}
	if(Controller != nullptr && Controller->IsA(AMYEnemyController::StaticClass()))
	{
		ActivatePrimaryAbility();
	}
	//SpawnDefaultWeapon();
	AMYSurvivalGameState* GameState = Cast<AMYSurvivalGameState>(GetWorld()->GetGameState());
	check(GameState)
	GameState->GameOverDelegate.AddUObject(this, &AMYCharacterBase::GameOver);
}

/**
 * Delayed super call because it will finish destruction
 * Need to do some stuff before finishing
 */
void AMYCharacterBase::Destroyed()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		AGameModeBase* GameModeBase = World->GetAuthGameMode();
		AMYSurvivalGameMode* SurvivalGameMode = Cast<AMYSurvivalGameMode>(GameModeBase);
		if (SurvivalGameMode != nullptr)
		{
			SurvivalGameMode->ActorDied(this);
		}
	}
	Super::Destroyed();
}

void AMYCharacterBase::DestroyPrep()
{
	Weapon->Deactivate();
	Destroy();
}

void AMYCharacterBase::GameOver()
{
	
}

void AMYCharacterBase::Die_Implementation()
{
	Destroy();
}

void AMYCharacterBase::Die_Server_Implementation()
{
	AbilitySystemComponent->CancelAllAbilities();
	GetWorldTimerManager().SetTimerForNextTick([this]() { DestroyPrep(); });
}

void AMYCharacterBase::SetupWeapons(const FGameplayEffectSpecHandle& InGESpecHandle)
{
	Weapon->SetGameplayEffect(InGESpecHandle);
}

UAbilitySystemComponent* AMYCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UMYAttributeSet* AMYCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void AMYCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Since the ASC exists on the pawn, we initialize the server side here
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AbilitySystemComponent->SetOwnerActor(this);
		SetupDelegates();
		InitializeAttributes();
		InitializeAbilities();
	}
	// If replication mode is mixed, owner MUST be controller
	SetOwner(NewController);
}

void AMYCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AddSet<UMYAttributeSet>();
	}
}

void AMYCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMYCharacterBase, PrimaryAbilityHandle);
	DOREPLIFETIME(AMYCharacterBase, SecondaryAbilityHandle);
	DOREPLIFETIME(AMYCharacterBase, bIsReady);
	DOREPLIFETIME(AMYCharacterBase, Weapon);
	DOREPLIFETIME(AMYCharacterBase, WeaponClass);
}

void AMYCharacterBase::SetOverheadHealthBarWidget(UMYOverheadHealthBarWidget* InWidget)
{
	if (InWidget != nullptr)
	{
		OverheadHealthBarWidget = InWidget;
	}
}

void AMYCharacterBase::ActivatePrimaryAbility()
{
	ActivateAbilityByHandle(PrimaryAbilityHandle);
}

float AMYCharacterBase::GetHealth() const
{
	if (AbilitySystemComponent != nullptr)
	{
		return AbilitySystemComponent->GetNumericAttribute(UMYAttributeSet::GetHealthAttribute());
	}
	return -1;
}

float AMYCharacterBase::GetMaxHealth() const
{
	if (AbilitySystemComponent != nullptr)
	{
		return AbilitySystemComponent->GetNumericAttribute(UMYAttributeSet::GetMaxHealthAttribute());
	}
	return -1;
}

float AMYCharacterBase::GetAttackPower() const
{
	if (AbilitySystemComponent != nullptr)
	{
		return AbilitySystemComponent->GetNumericAttribute(UMYAttributeSet::GetMaxHealthAttribute());
	}
	return -1;
}

float AMYCharacterBase::GetAbilityPower() const
{
	if (AbilitySystemComponent != nullptr)
	{
		return AbilitySystemComponent->GetNumericAttribute(UMYAttributeSet::GetAbilityPowerAttribute());
	}
	return -1;
}

float AMYCharacterBase::GetCharacterLevel() const
{
	if (AbilitySystemComponent != nullptr)
	{
		return AbilitySystemComponent->GetNumericAttribute(UMYAttributeSet::GetCharacterLevelAttribute());
	}
	return -1;
}

void AMYCharacterBase::InitializeAttributes()
{
	if (AbilitySystemComponent == nullptr)
		return;
	if (DefaultLevel == nullptr)
	{
		UE_LOG(LogAbilitySystem, Warning,
		       TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."),
		       *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	if (DefaultLevel)
	{
		const FGameplayEffectSpecHandle Handle = AbilitySystemComponent->MakeOutgoingSpec(
			DefaultLevel, 1, EffectContext);
		if (Handle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*Handle.Data.Get(), AbilitySystemComponent);
		}
	}
}

void AMYCharacterBase::InitializeAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->bAbilitiesInitialized)
		return;

	FGameplayAbilitySpec AbilitySpec;

	if (PrimaryAbility == nullptr)
	{
		UE_LOG(LogAbilitySystem, Warning,
		       TEXT("%s() Missing PrimaryAbility for %s. Please fill in the character's Blueprint."),
		       *FString(__FUNCTION__), *GetName());
	}
	else
	{
		AbilitySpec = FGameplayAbilitySpec(PrimaryAbility, 1, INDEX_NONE, this);
		PrimaryAbilityHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
	}

	if (SecondaryAbility == nullptr)
	{
		UE_LOG(LogAbilitySystem, Warning,
		       TEXT("%s() Missing SecondaryAbility for %s. Please fill in the character's Blueprint."),
		       *FString(__FUNCTION__), *GetName());
	}
	else
	{
		AbilitySpec = FGameplayAbilitySpec(SecondaryAbility, 1, INDEX_NONE, this);
		SecondaryAbilityHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
	}

	if (DownedAbility == nullptr)
	{
		UE_LOG(LogAbilitySystem, Warning,
		       TEXT("%s() Missing SecondaryAbility for %s. Please fill in the character's Blueprint."),
		       *FString(__FUNCTION__), *GetName());
	}
	else
	{
		AbilitySpec = FGameplayAbilitySpec(DownedAbility, 1, INDEX_NONE, this);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}

	AbilitySystemComponent->bAbilitiesInitialized = true;
}

void AMYCharacterBase::SetupAttributeCallbacks()
{
	if (AttributeSet == nullptr)
	{
		UE_LOG(LogAbilitySystem, Error, TEXT("%s AttributeSet is null inside %s()!"), *GetName(),
		       *FString(__FUNCTION__));
		return;
	}
	if (AbilitySystemComponent == nullptr)
	{
		UE_LOG(LogAbilitySystem, Error, TEXT("%s AbilitySystemComponent is null inside %s()!"), *GetName(),
		       *FString(__FUNCTION__));
		return;
	}
	AttributeHealthChangedDelegateHandle = AbilitySystemComponent->
	                                       GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).
	                                       AddUObject(this, &AMYCharacterBase::HealthChanged);
	AttributeMaxHealthChangedDelegateHandle = AbilitySystemComponent->
	                                          GetGameplayAttributeValueChangeDelegate(
		                                          AttributeSet->GetMaxHealthAttribute()).AddUObject(
		                                          this, &AMYCharacterBase::MaxHealthChanged);
}

void AMYCharacterBase::SetupDelegates()
{
	AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Downed"))).
	                        AddUObject(this, &AMYCharacterBase::DownedTagAddedOrRemoved);
}

void AMYCharacterBase::OnRep_Controller()
{
	Super::OnRep_Controller();
}

void AMYCharacterBase::SpawnWeaponsOnServer(int8 WeaponIdx)
{
	FGameplayTagContainer TagContainer;
	TagContainer.AddTagFast(FGameplayTag::RequestGameplayTag(FName("State.Blocked")));
	if(AbilitySystemComponent->HasAnyMatchingGameplayTags(TagContainer)) return;

	
	AttackChainCounter = 0;
	if(Weapon!=nullptr) // A weapon already exists
	{
		Weapon->Deactivate();
		Weapon = nullptr;
	}
	
	check(InventoryComponent);
	Weapon = GetWorld()->SpawnActorDeferred<AMYWeaponBase>(AMYWeaponBase::StaticClass(),FTransform::Identity,this);
	check(Weapon);
	Weapon->SetOwningCharacter(this);
	Weapon->SetOwnerASC(AbilitySystemComponent);
	Weapon->SetItemData(InventoryComponent->GetItemDataAtIndex(WeaponIdx));
	Weapon->SetReplicates(true);
	UGameplayStatics::FinishSpawningActor(Weapon, FTransform::Identity);
	
	UMYAbilityDataAsset* ADA = Weapon->GetPrimaryAbilityAsset();
	check(ADA);
	FGameplayAbilitySpec AbilitySpec;
	AbilitySpec = FGameplayAbilitySpec(ADA->Ability, 1, INDEX_NONE, this);
	PrimaryAbilityHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
}

void AMYCharacterBase::SpawnWeaponsOnServer_Server_Implementation(int8 WeaponIdx)
{
	SpawnWeaponsOnServer(WeaponIdx);
}

void AMYCharacterBase::DownedTagAddedOrRemoved(const FGameplayTag CallbackTag, int32 NewCount)
{
	UE_LOG(LogAbilitySystem, Warning, TEXT("Blargh! I'm down!"));
	BP_DownedTagAddedOrRemoved(CallbackTag, NewCount);
}

void AMYCharacterBase::HealthChanged(const FOnAttributeChangeData& Data)
{
	HealthChangedDelegate.Broadcast(Data.NewValue);
	if (Data.NewValue <= 0)
	{
		bWasKilled = true;
		AbilitySystemComponent->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Downed")));
	}
}

void AMYCharacterBase::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	MaxHealthChangedDelegate.Broadcast(Data.NewValue);
}

void AMYCharacterBase::ActivateAbilityByHandle(FGameplayAbilitySpecHandle InHandle)
{
	if (AbilitySystemComponent != nullptr)
		AbilitySystemComponent->TryActivateAbility(InHandle);
}
