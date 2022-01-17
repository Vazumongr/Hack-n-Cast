// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "UE5Testing/Loot/MYLootEnums.h"

#include "MYWeaponBase.generated.h"

class AMYWeapon;
class UMYGameplayAbility;
class UStaticMeshComponent;
class UStaticMesh;

UCLASS(Abstract, NotPlaceable, Blueprintable, BlueprintType)
class UE5TESTING_API AMYWeaponBase : public AActor
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

	void ActivateRightHandWeapon();
	void ActivateLeftHandWeapon();
	void DeactivateRightHandWeapon();
	void DeactivateLeftHandWeapon();

protected:
	UFUNCTION(Server, Reliable)
	virtual void ApplyEffectToTarget_Server(class AMYCharacterBase* TargetCharacter);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText WeaponName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UMYGameplayAbility> PrimaryAbility;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<class UMYGameplayAbility>> AdditionalAbilities;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemRarity ItemRarity;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EWeaponType WeaponType;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UStaticMesh* RightHandWeaponMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UStaticMesh* LeftHandWeaponMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class AMYWeapon* RightHandWeapon;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class AMYWeapon* LeftHandWeapon;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	class UAbilitySystemComponent* OwnerASC;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayEffectSpecHandle GESpecHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> HitActors;
};
