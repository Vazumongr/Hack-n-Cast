// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MYVendor.generated.h"

class AMYPlayerCharacter;
class UGameplayEffect;

DECLARE_LOG_CATEGORY_EXTERN(LogVendor, All, All);

UCLASS()
class UE5TESTING_API AMYVendor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYVendor();

	void Activate();
	void Deactivate();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(class AMYPlayerCharacter* InteractingCharacter);
	UFUNCTION(BlueprintCallable)
	void UpgradeWeapon(class AMYPlayerCharacter* InteractingCharacter) const;
	UFUNCTION(BlueprintCallable)
	void UpgradeSpellTome(class AMYPlayerCharacter* InteractingCharacter) const;
	UFUNCTION(BlueprintCallable)
	void UpgradeMaxHealth(class AMYPlayerCharacter* InteractingCharacter) const;
	UFUNCTION(BlueprintCallable)
	void UpgradeAttackDamage(class AMYPlayerCharacter* InteractingCharacter) const;
	UFUNCTION(BlueprintCallable)
	void UpgradeAbilityPower(class AMYPlayerCharacter* InteractingCharacter) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TSubclassOf<class UGameplayEffect> WeaponBuffEffect;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TSubclassOf<class UGameplayEffect> SpellTomeBuffEffect;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TSubclassOf<class UGameplayEffect> MaxHealthBuffEffect;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TSubclassOf<class UGameplayEffect> AttackDamageBuffEffect;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	TSubclassOf<class UGameplayEffect> AbilityPowerBuffEffect;
};
