// Troy Records Jr. 2021

#pragma once

#include "Engine/DataAsset.h"
#include "MYStartingKitBaseDA.generated.h"

class AMYWeapon;
class UMYGameplayAbility;

/**
 * Starting kits are what the player chooses upon loading into the game.
 * This dictates the gear they start with
 */
UCLASS(BlueprintType)
class UE5TESTING_API UMYStartingKitBaseDA : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FName GetStartingKitName() const { return StartingKitName; }
	TSubclassOf<class AMYWeaponBase> GetWeaponClass() const { return WeaponClass; }
	TSubclassOf<class UMYGameplayAbility> GetAttackAbility() const { return AttackAbility; }
	TSubclassOf<class UMYGameplayAbility> GetSpellAbility() const { return SpellAbility; }

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName StartingKitName;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<class AMYWeaponBase> WeaponClass;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<class UMYGameplayAbility> AttackAbility;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<class UMYGameplayAbility> SpellAbility;
};
