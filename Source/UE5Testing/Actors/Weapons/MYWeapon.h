// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Engine/StaticMeshActor.h"
#include "MYWeapon.generated.h"

class UAbilitySystemComponent;
class AMYCharacterBase;
class AMYWeaponBase;
class UBoxComponent;

UCLASS()
class UE5TESTING_API AMYWeapon : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYWeapon();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetOwningWeapon(class AMYWeaponBase* InOwningWeapon);
	void SetActorArrayPtr(TArray<AActor*>* InHitActorsRef);

	void Activate();
	void Deactivate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadOnly)
	class AMYWeaponBase* OwningWeapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxCollider;
	
	TArray<AActor*>* HitActorsRef;
};
