// Troy Records Jr. 2021

#include "UE5Testing/Characters/MYCharacterBase.h"

#include "Net/UnrealNetwork.h"
#include "UE5Testing/AbilitySystem/MYAbilitySystemComponent.h"
#include "UE5Testing/AbilitySystem/AttributeSets/MYAttributeSet.h"
#include "UE5Testing/AbilitySystem/MYGameplayAbility.h"

AMYCharacterBase::AMYCharacterBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMYAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Mixed;

	AttributeSet = CreateDefaultSubobject<UMYAttributeSet>(TEXT("Attribute Set"));
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
	if(AbilitySystemComponent)
	{
		UE_LOG(LogAbilitySystem, Warning, TEXT("Should be initialized on server"));
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AbilitySystemComponent->SetOwnerActor(this);
		InitializeAttributes();
		InitializeAbilities();
	}
	// If replication mode is mixed, owner MUST be controller
	SetOwner(NewController);
}

void AMYCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMYCharacterBase, PrimaryAbilityHandle);
	DOREPLIFETIME(AMYCharacterBase, SecondaryAbilityHandle);
}

void AMYCharacterBase::InitializeAttributes()
{
	if(AbilitySystemComponent == nullptr)
		return;
	if(!DefaultAttributes)
	{
		UE_LOG(LogAbilitySystem, Warning, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if(NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}
}

void AMYCharacterBase::InitializeAbilities()
{
	if(GetLocalRole() != ROLE_Authority || !AbilitySystemComponent | AbilitySystemComponent->bAbilitiesInitialized)
		return;
	
	FGameplayAbilitySpec AbilitySpec(PrimaryAbility,1,INDEX_NONE,this);
	PrimaryAbilityHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
	AbilitySpec = FGameplayAbilitySpec(SecondaryAbility,1,INDEX_NONE,this);
	SecondaryAbilityHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
	
	for(TSubclassOf<UMYGameplayAbility>& Ability : DefaultAbilities)
	{
		AbilitySpec = FGameplayAbilitySpec(Ability,1,INDEX_NONE,this);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
	AbilitySystemComponent->bAbilitiesInitialized = true;
}

void AMYCharacterBase::OnRep_Controller()
{
	Super::OnRep_Controller();
	/*
	// Since the ASC exists on the pawn, we initialize the server side here
	if(AbilitySystemComponent)
	{
		UE_LOG(LogAbilitySystem, Warning, TEXT("Should be initialized on client"));
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AbilitySystemComponent->SetOwnerActor(this);
		InitializeAttributes();
		InitializeAbilities();
	}
	*/
	//InitializeAttributes();
}

void AMYCharacterBase::ActivatePrimaryAbility()
{
}

void AMYCharacterBase::ActivateSecondaryAbility()
{
}

void AMYCharacterBase::ActivateAbilityByHandle(FGameplayAbilitySpecHandle InHandle)
{
	if(AbilitySystemComponent != nullptr)
		AbilitySystemComponent->TryActivateAbility(InHandle);
}
