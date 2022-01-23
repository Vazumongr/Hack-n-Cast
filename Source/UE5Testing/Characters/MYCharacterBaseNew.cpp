// Troy Records Jr. 2021

#include "UE5Testing/Characters/MYCharacterBaseNew.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "UE5Testing/AbilitySystem/MYAbilitySystemComponent.h"
#include "UE5Testing/AbilitySystem/AttributeSets/MYAttributeSet.h"
#include "UE5Testing/Actors/Weapons/MYWeapon.h"
#include "UE5Testing/Actors/Weapons/MYWeaponBase.h"
#include "UE5Testing/Components/ActorComponents/MYInventoryComponent.h"
#include "UE5Testing/GameModes/MYSurvivalGameMode.h"
#include "UE5Testing/UI/MYOverheadHealthBarComponent.h"
#include "UE5Testing/UI/MYOverheadHealthBarWidget.h"

AMYCharacterBaseNew::AMYCharacterBaseNew()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMYAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Mixed;

	AttributeSet = CreateDefaultSubobject<UMYAttributeSet>(TEXT("AttributeSet"));

	OverheadHealthBar = CreateDefaultSubobject<UMYOverheadHealthBarComponent>(TEXT("OverheadHealthBar"));
	OverheadHealthBar->SetupAttachment(RootComponent);

	InventoryComponent = CreateDefaultSubobject<UMYInventoryComponent>(TEXT("InventoryComponent"));
}

void AMYCharacterBaseNew::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMYCharacterBaseNew::BeginPlay()
{
	Super::BeginPlay();
	SetupAttributeCallbacks();
	if (HasAuthority())
	{
		SpawnWeapons();
		SpawnWeapon();
		InventoryComponent->AddItem(FInventoryWeapon(RightHandWeaponClass));
		InventoryComponent->AddItem(FInventoryWeapon(LeftHandWeaponClass));
	}
}

/**
 * Delayed super call because it will finish destruction
 * Need to do some stuff before finishing
 */
void AMYCharacterBaseNew::Destroyed()
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

void AMYCharacterBaseNew::Die_Implementation()
{
	Destroy();
}

void AMYCharacterBaseNew::ActivateRightHandWeapon()
{
	if (RightHandWeapon == nullptr)
	{
		UKismetSystemLibrary::PrintString(
			this, FString::Printf(TEXT("RightHandWeapon is null in %s"), *FString(__FUNCTION__)));
		return;
	}
	ActivateWeapon(RightHandWeapon);
}

void AMYCharacterBaseNew::ActivateLeftHandWeapon()
{
	if (LeftHandWeapon == nullptr)
	{
		UKismetSystemLibrary::PrintString(
			this, FString::Printf(TEXT("LeftHandWeapon is null in %s"), *FString(__FUNCTION__)));
		return;
	}
	ActivateWeapon(LeftHandWeapon);
}

void AMYCharacterBaseNew::DeactivateRightHandWeapon()
{
	if (RightHandWeapon == nullptr)
	{
		UKismetSystemLibrary::PrintString(
			this, FString::Printf(TEXT("RightHandWeapon is null in %s"), *FString(__FUNCTION__)));
		return;
	}
	DeactivateWeapon(RightHandWeapon);
}

void AMYCharacterBaseNew::DeactivateLeftHandWeapon()
{
	if (LeftHandWeapon == nullptr)
	{
		UKismetSystemLibrary::PrintString(
			this, FString::Printf(TEXT("LeftHandWeapon is null in %s"), *FString(__FUNCTION__)));
		return;
	}
	DeactivateWeapon(LeftHandWeapon);
}

void AMYCharacterBaseNew::ActivateWeapon(AMYWeapon* WeaponActor)
{
	if (WeaponActor != nullptr)
		WeaponActor->Activate();
}

void AMYCharacterBaseNew::DeactivateWeapon(AMYWeapon* WeaponActor)
{
	if (WeaponActor != nullptr)
		WeaponActor->Deactivate();
}

void AMYCharacterBaseNew::SetupWeapons(const FGameplayEffectSpecHandle& InGESpecHandle)
{
	if (RightHandWeapon != nullptr)
		RightHandWeapon->SetGameplayEffect(InGESpecHandle);
	if (LeftHandWeapon != nullptr)
		LeftHandWeapon->SetGameplayEffect(InGESpecHandle);
}

UAbilitySystemComponent* AMYCharacterBaseNew::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UMYAttributeSet* AMYCharacterBaseNew::GetAttributeSet() const
{
	return AttributeSet;
}

void AMYCharacterBaseNew::PossessedBy(AController* NewController)
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

void AMYCharacterBaseNew::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AddSet<UMYAttributeSet>();
	}
}

void AMYCharacterBaseNew::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMYCharacterBaseNew, PrimaryAbilityHandle);
	DOREPLIFETIME(AMYCharacterBaseNew, SecondaryAbilityHandle);
	DOREPLIFETIME(AMYCharacterBaseNew, bIsReady);
	DOREPLIFETIME(AMYCharacterBaseNew, RightHandWeapon);
	DOREPLIFETIME(AMYCharacterBaseNew, LeftHandWeapon);
}

void AMYCharacterBaseNew::SetOverheadHealthBarWidget(UMYOverheadHealthBarWidget* InWidget)
{
	if (InWidget != nullptr)
	{
		OverheadHealthBarWidget = InWidget;
	}
}

float AMYCharacterBaseNew::GetHealth() const
{
	if (AbilitySystemComponent != nullptr)
	{
		return AbilitySystemComponent->GetNumericAttribute(UMYAttributeSet::GetHealthAttribute());
	}
	return -1;
}

float AMYCharacterBaseNew::GetMaxHealth() const
{
	if (AbilitySystemComponent != nullptr)
	{
		return AbilitySystemComponent->GetNumericAttribute(UMYAttributeSet::GetMaxHealthAttribute());
	}
	return -1;
}

float AMYCharacterBaseNew::GetAttackPower() const
{
	if (AbilitySystemComponent != nullptr)
	{
		return AbilitySystemComponent->GetNumericAttribute(UMYAttributeSet::GetMaxHealthAttribute());
	}
	return -1;
}

float AMYCharacterBaseNew::GetAbilityPower() const
{
	if (AbilitySystemComponent != nullptr)
	{
		return AbilitySystemComponent->GetNumericAttribute(UMYAttributeSet::GetAbilityPowerAttribute());
	}
	return -1;
}

float AMYCharacterBaseNew::GetCharacterLevel() const
{
	if (AbilitySystemComponent != nullptr)
	{
		return AbilitySystemComponent->GetNumericAttribute(UMYAttributeSet::GetCharacterLevelAttribute());
	}
	return -1;
}

void AMYCharacterBaseNew::InitializeAttributes()
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
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
				*Handle.Data.Get(), AbilitySystemComponent);
		}
	}
}

void AMYCharacterBaseNew::InitializeAbilities()
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

void AMYCharacterBaseNew::SetupAttributeCallbacks()
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
	                                       AddUObject(this, &AMYCharacterBaseNew::HealthChanged);
	AttributeMaxHealthChangedDelegateHandle = AbilitySystemComponent->
	                                          GetGameplayAttributeValueChangeDelegate(
		                                          AttributeSet->GetMaxHealthAttribute()).AddUObject(
		                                          this, &AMYCharacterBaseNew::MaxHealthChanged);
}

void AMYCharacterBaseNew::SetupDelegates()
{
	AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Downed"))).
	                        AddUObject(this, &AMYCharacterBaseNew::DownedTagAddedOrRemoved);
}

void AMYCharacterBaseNew::OnRep_Controller()
{
	Super::OnRep_Controller();
}

void AMYCharacterBaseNew::SpawnWeapons()
{
	if (RightHandWeaponClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s does not have RightHandWeaponClass set."), *GetName());
	}
	else
	{
		SpawnWeapon(RightHandWeapon, RightHandWeaponClass, RightSocketName, RightHandWeaponRotation);
	}

	if (LeftHandWeaponClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s does not have LeftHandWeaponClass set."), *GetName());
	}
	else
	{
		SpawnWeapon(LeftHandWeapon, LeftHandWeaponClass, LeftSocketName, LeftHandWeaponRotation);
	}
}

void AMYCharacterBaseNew::SpawnWeapon()
{
	if (WeaponClass != nullptr)
	{
		WeaponItemThing = GetWorld()->SpawnActor<AMYWeaponBase>(WeaponClass);
		//WeaponItemThing->SetOwningCharacter(this);
	}
}

void AMYCharacterBaseNew::SpawnWeapon(AMYWeapon*& WeaponActor, TSubclassOf<AMYWeapon>& RefClass, FName InSocketName,
                                   FRotator SpawnWeaponRotation)
{
	UWorld* World = GetWorld();
	if (!ensure(World)) return;
	FTransform Transform = FTransform(SpawnWeaponRotation);

	if (IsValid(WeaponActor)) WeaponActor->Destroy();

	WeaponActor = World->SpawnActor<AMYWeapon>(RefClass, Transform);
	if (WeaponActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("RightHandWeapon spawning failed!"));
		return;
	}
	WeaponActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, InSocketName);
	WeaponActor->SetOwner(this);
	WeaponActor->SetInstigator(this);
	if (AbilitySystemComponent == nullptr)
	{
		UE_LOG(LogAbilitySystem, Warning, TEXT("%s was called with a null ASC on %s"), *FString(__FUNCTION__),
		       *GetName());
	}
	WeaponActor->SetOwnerASC(AbilitySystemComponent);
}

void AMYCharacterBaseNew::SpawnWeapons_Client_Implementation()
{
}

void AMYCharacterBaseNew::DownedTagAddedOrRemoved(const FGameplayTag CallbackTag, int32 NewCount)
{
	UE_LOG(LogAbilitySystem, Warning, TEXT("Blargh! I'm down!"));
	BP_DownedTagAddedOrRemoved(CallbackTag, NewCount);
}

void AMYCharacterBaseNew::HealthChanged(const FOnAttributeChangeData& Data)
{
	///HealthChangedDelegate.Broadcast(Data.NewValue);
	if (Data.NewValue <= 0)
	{
		bWasKilled = true;
		AbilitySystemComponent->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Downed")));
	}
}

void AMYCharacterBaseNew::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	//MaxHealthChangedDelegate.Broadcast(Data.NewValue);
}

void AMYCharacterBaseNew::ActivateAbilityByHandle(FGameplayAbilitySpecHandle InHandle)
{
	if (AbilitySystemComponent != nullptr)
		AbilitySystemComponent->TryActivateAbility(InHandle);
}
