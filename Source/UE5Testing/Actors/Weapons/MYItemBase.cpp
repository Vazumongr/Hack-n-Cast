// Troy Records Jr. 2021


#include "MYItemBase.h"

#include "UE5Testing/AbilitySystem/MYAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AMYItemBase::AMYItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMYItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMYItemBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(AMYItemBase, OwnerASC, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(AMYItemBase, OwningCharacter, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(AMYItemBase, ItemData, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(AMYItemBase, NonInstancedItemData, COND_InitialOnly);
}

void AMYItemBase::SetItemData(TObjectPtr<UMYItemData> InItemData)
{
	ItemData = InItemData;
}

void AMYItemBase::SetOwnerASC(UAbilitySystemComponent* InOwnerASC)
{
	check(InOwnerASC);
	if (InOwnerASC == nullptr)
	{
		UE_LOG(LogAbilitySystem, Warning, TEXT("%s was called with a null ASC on %s"), *FString(__FUNCTION__),
			   *GetName());
		return;
	}
	OwnerASC = InOwnerASC;
}

void AMYItemBase::SetOwningCharacter(AMYCharacterBase* InOwningCharacter)
{
	OwningCharacter = InOwningCharacter;
}
void AMYItemBase::Deconstruct()
{
	Destroy();
}

// Called every frame
void AMYItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

