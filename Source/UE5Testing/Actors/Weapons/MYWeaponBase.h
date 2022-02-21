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
class UMYWeaponData;
class UMYWeaponSMADA;

class UStaticMeshComponent;
class UStaticMesh;

UCLASS(NotPlaceable, Blueprintable, BlueprintType)
class UE5TESTING_API AMYWeaponBase : public AMYItemBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYWeaponBase();

	virtual void BeginPlay() override;

	virtual class UMYAbilityDataAsset* GetPrimaryAbilityAsset() const;

	UFUNCTION(BlueprintCallable)
	void SetGameplayEffect(const FGameplayEffectSpecHandle& InGESpecHandle);
	UFUNCTION(BlueprintCallable)
	void HitCharacter(class AMYCharacterBase* TargetCharacter);
	UFUNCTION(BlueprintCallable)
	void Initialize();
	UFUNCTION(BlueprintCallable)
	void Deactivate();
	virtual void Deconstruct() override;

	UFUNCTION(BlueprintCallable)
	void ActivateRightHandWeapon();
	UFUNCTION(BlueprintCallable)
	void ActivateLeftHandWeapon();
	UFUNCTION(BlueprintCallable)
	void DeactivateRightHandWeapon();
	UFUNCTION(BlueprintCallable)
	void DeactivateLeftHandWeapon();

	TArray<AActor*>* GetHitActors(TArray<AActor*>& OutHitActors);

protected:
	UFUNCTION(Server, Reliable)
	virtual void ApplyEffectToTarget_Server(class AMYCharacterBase* TargetCharacter);

	virtual void SpawnWeaponActors();
	UFUNCTION(NetMulticast, Reliable)
	virtual void SpawnWeaponActors_Multicast();
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Replicated)
	class AMYWeaponActor* RightHandWeapon;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Replicated)
	class AMYWeaponActor* LeftHandWeapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayEffectSpecHandle GESpecHandle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> HitActors;
	
};
