// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

#include "MYAbilitySystemComponent.generated.h"


UCLASS()
class UE5TESTING_API UMYAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category="Ability System")
	bool bAbilitiesInitialized = false;
};
