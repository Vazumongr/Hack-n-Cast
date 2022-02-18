// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UE5Testing/Loot/MYLootEnums.h"

#include "MYItemData.generated.h"

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
	TSubclassOf<class UMYGameplayAbility> PrimaryAbility;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<class UMYGameplayAbility>> AdditionalAbilities;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemRarity ItemRarity;
};
