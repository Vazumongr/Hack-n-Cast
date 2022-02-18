// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "MYItemData.h"
#include "MYWeaponData.generated.h"

class AMYWeaponActor;
class UMYAbilityDataAsset;
class UMYWeaponSMADA;

/**
 * Class for containing information to spawn and store Weapons
 */
UCLASS()
class UE5TESTING_API UMYWeaponData : public UMYItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EWeaponType WeaponType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UMYWeaponSMADA* WeaponSMADA;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UMYAbilityDataAsset* AbilityDataAsset;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AMYWeaponActor> RHWeaponClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AMYWeaponActor> LHWeaponClass;
};
