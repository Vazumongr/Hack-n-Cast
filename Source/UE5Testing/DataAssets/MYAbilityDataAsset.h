﻿// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/DataAsset.h"
#include "MYAbilityDataAsset.generated.h"

/** A seed file that is created to mark referenced assets as part of this primary asset */
UCLASS(BlueprintType)
class UE5TESTING_API UMYAbilityDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UMYGameplayAbility> Ability;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AbilityName;
};
