// Troy Records Jr. 2021


#include "MYVendor.h"

#include "UE5Testing/Characters/MYPlayerCharacter.h"

DEFINE_LOG_CATEGORY(LogVendor);

// Sets default values
AMYVendor::AMYVendor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AMYVendor::Activate()
{
	UE_LOG(LogVendor, Warning, TEXT("Vendor Activated"));
	SetHidden(false);
}

void AMYVendor::Deactivate()
{
	UE_LOG(LogVendor, Warning, TEXT("Vendor Deactivated"));
	SetHidden(true);
}

void AMYVendor::UpgradeWeapon(AMYPlayerCharacter* InteractingCharacter) const
{
	check(InteractingCharacter);
	InteractingCharacter->ApplyBuff_Server(WeaponBuffEffect);
}

void AMYVendor::UpgradeSpellTome(AMYPlayerCharacter* InteractingCharacter) const
{
	check(InteractingCharacter);
	InteractingCharacter->ApplyBuff_Server(SpellTomeBuffEffect);
}

void AMYVendor::Interact_Implementation(AMYPlayerCharacter* InteractingActor)
{
	check(InteractingActor);
	//InteractingActor->BuffYourself();
	UE_LOG(LogVendor, Warning, TEXT("Vendor interaction called"));
}

// Called when the game starts or when spawned
void AMYVendor::BeginPlay()
{
	Super::BeginPlay();
}

