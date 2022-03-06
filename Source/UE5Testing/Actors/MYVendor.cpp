// Troy Records Jr. 2021


#include "MYVendor.h"

DEFINE_LOG_CATEGORY(LogVendor);

// Sets default values
AMYVendor::AMYVendor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AMYVendor::Activate()
{
	SetHidden(false);
}

void AMYVendor::Deactivate()
{
	SetHidden(true);
}

void AMYVendor::Interact()
{
	UE_LOG(LogVendor, Warning, TEXT("Vendor interaction called"));
}

// Called when the game starts or when spawned
void AMYVendor::BeginPlay()
{
	Super::BeginPlay();
}

