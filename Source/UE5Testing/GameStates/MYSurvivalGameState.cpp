// Troy Records Jr. 2021


#include "MYSurvivalGameState.h"


// Sets default values
AMYSurvivalGameState::AMYSurvivalGameState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMYSurvivalGameState::BeginPlay()
{
	Super::BeginPlay();
	
}

int32 AMYSurvivalGameState::GetCurrentWave()
{
	return 0;
}

int32 AMYSurvivalGameState::GetTotalEnemyThisWaveCount()
{
	return 0;
}

// Called every frame
void AMYSurvivalGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

