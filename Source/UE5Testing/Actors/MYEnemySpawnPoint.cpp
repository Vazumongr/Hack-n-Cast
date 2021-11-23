// Troy Records Jr. 2021


#include "MYEnemySpawnPoint.h"


// Sets default values
AMYEnemySpawnPoint::AMYEnemySpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMYEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMYEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

