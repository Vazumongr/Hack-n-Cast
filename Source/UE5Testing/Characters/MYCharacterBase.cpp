﻿// Troy Records Jr. 2021

#include "UE5Testing/Characters/MYCharacterBase.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "UE5Testing/AbilitySystem/MYAbilitySystemComponent.h"
#include "UE5Testing/AbilitySystem/AttributeSets/MYAttributeSet.h"
#include "UE5Testing/AbilitySystem/MYGameplayAbility.h"
#include "UE5Testing/UI/MYOverheadHealthBar.h"

AMYCharacterBase::AMYCharacterBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMYAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Mixed;

	AttributeSet = CreateDefaultSubobject<UMYAttributeSet>(TEXT("Attribute Set"));

	OverheadHealthBar = CreateDefaultSubobject<UMYOverheadHealthBar>(TEXT("Overhead Health Bar"));
	OverheadHealthBar->SetupAttachment(RootComponent);
}

void AMYCharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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
		SetupAttributeCallbacks();
		InitializeAttributes();
		InitializeAbilities();
	}
	// If replication mode is mixed, owner MUST be controller
	SetOwner(NewController);
}

void AMYCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->AddSet<UMYAttributeSet>();
	}
}

void AMYCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMYCharacterBase, PrimaryAbilityHandle);
	DOREPLIFETIME(AMYCharacterBase, SecondaryAbilityHandle);
}

float AMYCharacterBase::GetHealth() const
{
	if(AbilitySystemComponent != nullptr)
	{
		return AbilitySystemComponent->GetNumericAttribute(UMYAttributeSet::GetHealthAttribute());
	}
	return -1;
}

float AMYCharacterBase::GetMaxHealth() const
{
	if(AbilitySystemComponent != nullptr)
	{
		return AbilitySystemComponent->GetNumericAttribute(UMYAttributeSet::GetMaxHealthAttribute());
	}
	return -1;
}

float AMYCharacterBase::GetAttackPower() const
{
	if(AbilitySystemComponent != nullptr)
	{
		return AbilitySystemComponent->GetNumericAttribute(UMYAttributeSet::GetMaxHealthAttribute());
	}
	return -1;
}

float AMYCharacterBase::GetAbilityPower() const
{
	if(AbilitySystemComponent != nullptr)
	{
		return AbilitySystemComponent->GetNumericAttribute(UMYAttributeSet::GetAbilityPowerAttribute());
	}
	return -1;
}

float AMYCharacterBase::GetCharacterLevel() const
{
	if(AbilitySystemComponent != nullptr)
	{
		return AbilitySystemComponent->GetNumericAttribute(UMYAttributeSet::GetCharacterLevelAttribute());
	}
	return -1;
}

void AMYCharacterBase::InitializeAttributes()
{
	if(AbilitySystemComponent == nullptr)
		return;
	if(DefaultLevel == nullptr)
	{
		UE_LOG(LogAbilitySystem, Warning, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	
	if(DefaultLevel)
	{
		const FGameplayEffectSpecHandle Handle = AbilitySystemComponent->MakeOutgoingSpec(DefaultLevel, 1, EffectContext);
        if(Handle.IsValid())
        {
        	FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*Handle.Data.Get(), AbilitySystemComponent);
        }
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

	AbilitySystemComponent->bAbilitiesInitialized = true;
}

void AMYCharacterBase::SetupAttributeCallbacks()
{
	if(AttributeSet == nullptr)
	{
		UE_LOG(LogAbilitySystem, Error, TEXT("%s AttributeSet is null inside %s()!"), *GetName(), *FString(__FUNCTION__));
		return;
	}
	if(AbilitySystemComponent == nullptr)
	{
		UE_LOG(LogAbilitySystem, Error, TEXT("%s AbilitySystemComponent is null inside %s()!"), *GetName(), *FString(__FUNCTION__));
		return;
	}
	AttributeHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &AMYCharacterBase::HealthChanged);
	HealthChangedDelegate.AddDynamic(this, &AMYCharacterBase::ActivatePrimaryAbility);
	AttributeMaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &AMYCharacterBase::MaxHealthChanged);
	MaxHealthChangedDelegate.AddDynamic(this, &AMYCharacterBase::ActivatePrimaryAbility);
	
}

void AMYCharacterBase::OnRep_Controller()
{
	Super::OnRep_Controller();
}

void AMYCharacterBase::ActivatePrimaryAbility(float num)
{
	//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Orange,"Yahooooo!");
}

void AMYCharacterBase::ActivateSecondaryAbility()
{
}

void AMYCharacterBase::HealthChanged(const FOnAttributeChangeData& Data)
{
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%s() inside %s"), *FString(__FUNCTION__), *GetName()),true,true,FLinearColor(0,0.66,1), 10);
	HealthChangedDelegate.Broadcast(Data.NewValue);
}

void AMYCharacterBase::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%s() inside %s"), *FString(__FUNCTION__), *GetName()),true,true,FLinearColor(0,0.66,1), 10);
	MaxHealthChangedDelegate.Broadcast(Data.NewValue);
}

void AMYCharacterBase::ActivateAbilityByHandle(FGameplayAbilitySpecHandle InHandle)
{
	if(AbilitySystemComponent != nullptr)
		AbilitySystemComponent->TryActivateAbility(InHandle);
}
