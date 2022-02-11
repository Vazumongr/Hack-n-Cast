// Troy Records Jr. 2021


#include "MYSurvivalGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "SpawnRules/MYRoundSpawner.h"
#include "UE5Testing/Actors/MYEnemySpawnPoint.h"
#include "UE5Testing/Characters/MYCharacterBase.h"
#include "UE5Testing/Characters/MYPlayerCharacter.h"
#include "UE5Testing/GameStates/MYSurvivalGameState.h"

void AMYSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
	Spawner = GetWorld()->SpawnActor<AMYRoundSpawner>(SpawnerClass);
	if(Spawner != nullptr)
	{
		Spawner->Spawner_BeginPlay();
		//Spawner->BindToWaveStartedDelegate(this, &AMYSurvivalGameMode::WaveStarted);
		Spawner->GetWaveStartedDelegate().AddUObject(this, &AMYSurvivalGameMode::WaveStarted);
		Spawner->GetWaveEndedDelegate().AddUObject(this, &AMYSurvivalGameMode::WaveEnded);
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
	if(DeadActor->IsA(AMYPlayerCharacter::StaticClass()))
	{
		if(--PlayersAlive==0)
			AllPlayersDead();
	}
	else
	{
		Spawner->ActorDied(DeadActor);
	}
}

void AMYSurvivalGameMode::AllPlayersDead()
{
	AllPlayersDeadDelegate.Broadcast();
	UE_LOG(LogSpawn,Warning,TEXT("AllPlayersDead"));
}

void AMYSurvivalGameMode::WaveStarted(int32 InWave)
{
	AMYSurvivalGameState* SurvivalGameState = GetGameState<AMYSurvivalGameState>();
	if(SurvivalGameState != nullptr)
	{
		SurvivalGameState->WaveStarted_Multicast(InWave);
	}
}

void AMYSurvivalGameMode::WaveEnded(int32 InWave)
{
	AMYSurvivalGameState* SurvivalGameState = GetGameState<AMYSurvivalGameState>();
	if(SurvivalGameState != nullptr)
	{
		SurvivalGameState->WaveEnded_Multicast(InWave);
	}
}

APawn* AMYSurvivalGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer,
	const FTransform& SpawnTransform)
{
	APawn* SpawnedPawn = Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);
	if(SpawnedPawn->IsA(AMYPlayerCharacter::StaticClass()))
		PlayersAlive++;
	return SpawnedPawn;
}
