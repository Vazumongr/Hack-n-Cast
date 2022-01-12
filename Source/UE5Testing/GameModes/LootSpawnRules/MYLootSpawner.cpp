// Troy Records Jr. 2021


#include "MYLootSpawner.h"


// Sets default values
AMYLootSpawner::AMYLootSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMYLootSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMYLootSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

