// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UE5Testing/Loot/MYLootEnums.h"

#include "MYItemData.generated.h"

class UMYAbilityDataAsset;
class UMYGameplayAbility;

/**
 * 
 */
UCLASS(Abstract, DefaultToInstanced, EditInlineNew, Blueprintable)
class UE5TESTING_API UMYItemData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UMYAbilityDataAsset* PrimaryAbilityDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<class UMYAbilityDataAsset*> AdditionalAbilityDataAssets;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemRarity ItemRarity;
};
