// Troy Records Jr.
#include "MYDroppedLootBase.h"

#include "NiagaraComponent.h"
#include "GameFramework/GameStateBase.h"


AMYDroppedLootBase::AMYDroppedLootBase()
{
	LootBeam = CreateDefaultSubobject<UNiagaraComponent>("Loot Beam");
	LootBeam->SetupAttachment(RootComponent);
	SetHidden(true);
	bOnlyRelevantToOwner = true;
}

void AMYDroppedLootBase::BeginPlay()
{
	Super::BeginPlay();
	SetDrop();
}

void AMYDroppedLootBase::SetDrop_Implementation()
{
	SetHidden(false);
}

void AMYDroppedLootBase::ProximityPickUp(AActor* PickerUpper)
{
	if(!bProximityPickup || bPickedUp) return;
	UE_LOG(LogTemp, Warning, TEXT("Pickedup"));
	OnProximityPickUp(PickerUpper);
}

void AMYDroppedLootBase::PickUp_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("%s being called! No Blueprint or child override!"), *FString(__FUNCTION__));
}
