// Troy Records Jr. 2021
#include "MYAbilitySystemComponent.h"

UMYAbilitySystemComponent::UMYAbilitySystemComponent()
{
	SetIsReplicatedByDefault(true);
}

TArray<FGameplayAttribute> UMYAbilitySystemComponent::GetAttributes()
{
	TArray<FGameplayAttribute> Attributes;
	GetAllAttributes(Attributes);
	return Attributes;
}
