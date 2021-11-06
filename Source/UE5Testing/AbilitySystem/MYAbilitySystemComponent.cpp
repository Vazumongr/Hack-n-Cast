// Troy Records Jr. 2021
#include "MYAbilitySystemComponent.h"

TArray<FGameplayAttribute> UMYAbilitySystemComponent::GetAttributes()
{
	TArray<FGameplayAttribute> Attributes;
	GetAllAttributes(Attributes);
	return Attributes;
}
