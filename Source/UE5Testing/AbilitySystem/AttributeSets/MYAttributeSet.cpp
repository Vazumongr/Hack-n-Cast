// Fill out your copyright notice in the Description page of Project Settings.
#include "MYAttributeSet.h"

#include "Net/UnrealNetwork.h"


// Sets default values
UMYAttributeSet::UMYAttributeSet()
{
	
}

void UMYAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UMYAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMYAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMYAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMYAttributeSet, AbilityPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMYAttributeSet, CharacterLevel, COND_None, REPNOTIFY_Always);
}

void UMYAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMYAttributeSet, Health, OldHealth);
}

void UMYAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMYAttributeSet, MaxHealth, OldMaxHealth);
}

void UMYAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMYAttributeSet, AttackPower, OldAttackPower);
}

void UMYAttributeSet::OnRep_AbilityPower(const FGameplayAttributeData& OldAbilityPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMYAttributeSet, AbilityPower, OldAbilityPower);
}

void UMYAttributeSet::OnRep_CharacterLevel(const FGameplayAttributeData& OldCharacterLevel)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMYAttributeSet, CharacterLevel, OldCharacterLevel);
}


