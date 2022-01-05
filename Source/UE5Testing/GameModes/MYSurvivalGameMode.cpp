// Troy Records Jr. 2021


#include "MYSurvivalGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "SpawnRules/MYRoundSpawner.h"
#include "UE5Testing/Actors/MYEnemySpawnPoint.h"
#include "UE5Testing/Characters/MYCharacterBase.h"

void AMYSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
	Spawner = GetWorld()->SpawnActor<AMYRoundSpawner>(SpawnerClass);
	if(Spawner != nullptr)
	{
		Spawner->Spawner_BeginPlay();
	}
}

void AMYSurvivalGameMode::SpawnDrops()
{
	TArray<AActor*> LootSpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMYEnemySpawnPoint::StaticClass(), LootSpawnPoints);
	TArray<AActor*> TempActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMYCharacterBase::StaticClass(), TempActors);
	if(LootClass == nullptr)
		return;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	
	uint8 Counter{0};
	
	for(AActor* Actor : LootSpawnPoints)
    {
		if(Counter<TempActors.Num())
			SpawnParameters.Owner = TempActors[Counter];
		else
			SpawnParameters.Owner = TempActors[0];
    	GetWorld()->SpawnActor<AActor>(LootClass,Actor->GetActorLocation(),Actor->GetActorRotation(), SpawnParameters);
		Counter++;
    }
}

void AMYSurvivalGameMode::ActorDied(AActor* DeadActor)
{
	Spawner->ActorDied(DeadActor);
}
