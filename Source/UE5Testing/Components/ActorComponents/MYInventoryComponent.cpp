﻿// Troy Records Jr. 2021


#include "MYInventoryComponent.h"

#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UMYInventoryComponent::UMYInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMYInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMYInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMYInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UMYInventoryComponent, InventoryWeapons);
}

void UMYInventoryComponent::AddItem(FInventoryWeapon InInventoryWeapon)
{
	InventoryWeapons.Add(InInventoryWeapon);
}

bool UMYInventoryComponent::GetInventoryWeaponAtIndex(FInventoryWeapon& OutInventoryWeapon, int32 InIdx) const
{
	if(InventoryWeapons.Num() > InIdx)
	{
		OutInventoryWeapon = InventoryWeapons[InIdx];
		return true;
	}
	return false;
}
