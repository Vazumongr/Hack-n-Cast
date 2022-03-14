// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MYInventoryComponent.generated.h"

class UMYItemData;
/** TODO remove this junk
USTRUCT()
struct FInventoryWeapon
{
	GENERATED_BODY()
	
	FInventoryWeapon(){};
	
	FInventoryWeapon(TSubclassOf<class AMYWeaponBase> InClass)
	{
		WeaponClass = InClass;
	}

	UPROPERTY()
	TSubclassOf<class AMYWeaponBase> WeaponClass;
};
*/

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

	UFUNCTION(Server, Reliable)
	void AddItemToInventory_Server(class UMYItemData* InItemData);

	TObjectPtr<class UMYItemData> GetItemDataAtIndex(int8 InIdx) const;

	UFUNCTION(BlueprintCallable)
	TArray<UMYItemData*> GetInventoryItems() const { return InventoryItems; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Replicated, Instanced)
	TArray<TObjectPtr<class UMYItemData>> InventoryItems;
public:
};
