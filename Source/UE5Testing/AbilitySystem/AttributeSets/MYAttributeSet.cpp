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
}

void UMYAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMYAttributeSet, Health, OldHealth);
}

void UMYAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMYAttributeSet, MaxHealth, OldMaxHealth);
}

