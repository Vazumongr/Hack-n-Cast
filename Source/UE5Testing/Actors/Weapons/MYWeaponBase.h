// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "UE5Testing/Loot/MYLootEnums.h"
#include "UE5Testing/Actors/Weapons/MYItemBase.h"

#include "MYWeaponBase.generated.h"

class AMYWeapon;
class UMYAbilityDataAsset;
class AMYCharacterBase;
class UMYGameplayAbility;
class UMYWeaponSMADA;

class UStaticMeshComponent;
class UStaticMesh;

UCLASS(Abstract, NotPlaceable, Blueprintable, BlueprintType)
class UE5TESTING_API AMYWeaponBase : public AMYItemBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYWeaponBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EWeaponType WeaponType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UMYWeaponSMADA* WeaponSMADA;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UMYAbilityDataAsset* Ability;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AMYWeapon> RHWeaponClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AMYWeapon> LHWeaponClass;
	
	UPROPERTY(Replicated, VisibleDefaultsOnly, BlueprintReadOnly)
	class AMYWeapon* RightHandWeapon;
	
	UPROPERTY(Replicated, VisibleDefaultsOnly, BlueprintReadOnly)
	class AMYWeapon* LeftHandWeapon;
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	class UAbilitySystemComponent* OwnerASC;
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	FGameplayEffectSpecHandle GESpecHandle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> HitActors;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AMYCharacterBase* OwningCharacter;
};
