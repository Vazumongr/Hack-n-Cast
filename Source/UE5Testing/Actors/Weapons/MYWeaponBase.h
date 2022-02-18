// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "UE5Testing/Loot/MYLootEnums.h"
#include "UE5Testing/Actors/Weapons/MYItemBase.h"

#include "MYWeaponBase.generated.h"

class AMYCharacterBase;
class AMYWeaponActor;
class UMYAbilityDataAsset;
class UMYGameplayAbility;
class UMYWeaponSMADA;

class UStaticMeshComponent;
class UStaticMesh;

/* Extension of ItemData for weapon specific data */
USTRUCT()
struct FWeaponData : public FItemData
{
	GENERATED_BODY();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EWeaponType WeaponType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UMYWeaponSMADA* WeaponSMADA;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UMYAbilityDataAsset* Ability;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AMYWeaponActor> RHWeaponClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AMYWeaponActor> LHWeaponClass;
};

UCLASS(Abstract, NotPlaceable, Blueprintable, BlueprintType)
class UE5TESTING_API AMYWeaponBase : public AMYItemBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYWeaponBase();

	virtual class UMYAbilityDataAsset* GetAbilityDataAsset() const { return Ability; };

	UFUNCTION(BlueprintCallable)
	void SetGameplayEffect(const FGameplayEffectSpecHandle& InGESpecHandle);
	UFUNCTION(BlueprintCallable)
	void SetOwnerASC(class UAbilitySystemComponent* InOwnerASC);
	UFUNCTION(BlueprintCallable)
	void HitCharacter(class AMYCharacterBase* TargetCharacter);
	UFUNCTION(BlueprintCallable)
	void SetOwningCharacter(class AMYCharacterBase* InOwningCharacter);
	UFUNCTION(BlueprintCallable)
	void Deactivate();

	UFUNCTION(BlueprintCallable)
	void ActivateRightHandWeapon();
	UFUNCTION(BlueprintCallable)
	void ActivateLeftHandWeapon();
	UFUNCTION(BlueprintCallable)
	void DeactivateRightHandWeapon();
	UFUNCTION(BlueprintCallable)
	void DeactivateLeftHandWeapon();

protected:
	UFUNCTION(Server, Reliable)
	virtual void ApplyEffectToTarget_Server(class AMYCharacterBase* TargetCharacter);

	virtual void SpawnWeapons();

	/* begin struct data */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EWeaponType WeaponType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UMYWeaponSMADA* WeaponSMADA;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UMYAbilityDataAsset* Ability;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AMYWeaponActor> RHWeaponClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AMYWeaponActor> LHWeaponClass;
	/* end struct data */
	
	UPROPERTY(Replicated, VisibleDefaultsOnly, BlueprintReadOnly)
	class AMYWeaponActor* RightHandWeapon;
	
	UPROPERTY(Replicated, VisibleDefaultsOnly, BlueprintReadOnly)
	class AMYWeaponActor* LeftHandWeapon;
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	class UAbilitySystemComponent* OwnerASC;
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	FGameplayEffectSpecHandle GESpecHandle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> HitActors;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AMYCharacterBase* OwningCharacter;
};
