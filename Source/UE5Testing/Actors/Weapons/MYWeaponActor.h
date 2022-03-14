// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MYWeaponActor.generated.h"

class AMYWeaponBase;

UCLASS()
class UE5TESTING_API AMYWeaponActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYWeaponActor();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetOwningWeapon(class AMYWeaponBase* InOwningWeapon);

	void Activate();
	void Deactivate();

	bool bShouldDetect{false};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep,
								const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadOnly, Replicated)
	class AMYWeaponBase* OwningWeapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxCollider;
};
