// Troy Records Jr. 2021
#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MYDroppedLootBase.generated.h"

UCLASS()
/**
 * Base class for loot objects. Not to be used directly.
 */
class UE5TESTING_API AMYDroppedLootBase : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AMYDroppedLootBase();

	virtual void BeginPlay() override;

	UFUNCTION(Reliable, Client)
	void SetDrop();
	
	UFUNCTION(BlueprintNativeEvent)
	void PickUp();
	
	void ProximityPickUp(AActor* PickerUpper);

	/**
	 * Blueprint event for handling proximity pickups
	 * Only fired if bProximityPickup is true
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnProximityPickUp(AActor* PickerUpper);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UNiagaraComponent* LootBeam;

	/**
	 * Dictates whether the drop is picked up by proximity
	 * or if the player needs to actively pick it up
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Interaction")
	bool bProximityPickup = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Interaction")
	bool bPickedUp = false;
private:
	
};