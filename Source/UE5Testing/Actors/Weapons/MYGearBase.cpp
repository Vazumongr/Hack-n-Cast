// Troy Records Jr. 2021


#include "MYGearBase.h"


// Sets default values
AMYGearBase::AMYGearBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMYGearBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMYGearBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

