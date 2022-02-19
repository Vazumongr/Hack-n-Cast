// Troy Records Jr. 2021


#include "MYInventoryComponent.h"

#include "UE5Testing/DataTypes/MYWeaponData.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UMYInventoryComponent::UMYInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UMYInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if(GetOwnerRole() != ROLE_Authority) return;
	UMYWeaponData* TestData = NewObject<UMYWeaponData>(this, UMYWeaponData::StaticClass());
	TestData->ItemName = FText::FromString("I am test data!");
	InventoryItems.Add(TestData);
}


// Called every frame
void UMYInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMYInventoryComponent::AddItemToInventory_Server_Implementation(UMYItemData* InItemData)
{
	InventoryItems.Add(InItemData);
}

void UMYInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UMYInventoryComponent, InventoryItems);
}

TObjectPtr<UMYItemData> UMYInventoryComponent::GetItemDataAtIndex(int8 InIdx) const
{
	return InIdx <= InventoryItems.Num() ? InventoryItems[InIdx] : nullptr;
}

