// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MYInventoryComponent.generated.h"


USTRUCT()
struct FInventoryWeapon
{
	GENERATED_BODY()
	
	FInventoryWeapon(){};
	
	FInventoryWeapon(TSubclassOf<class AMYWeapon> InClass)
	{
		WeaponClass = InClass;
	}

	UPROPERTY()
	TSubclassOf<class AMYWeapon> WeaponClass;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UE5TESTING_API UMYInventoryComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMYInventoryComponent();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void AddItem(FInventoryWeapon InInventoryWeapon);
	virtual bool GetInventoryWeaponAtIndex(FInventoryWeapon& OutInventoryWeapon, int32 InIdx) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(Replicated)
	TArray<FInventoryWeapon> InventoryWeapons;
public:
};
