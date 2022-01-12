// Troy Records Jr. 2021


#include "MYRoundSpawner.h"

#include "Kismet/GameplayStatics.h"
#include "UE5Testing/Actors/MYEnemySpawnPoint.h"
#include "UE5Testing/Characters/MYPlayerCharacter.h"

DEFINE_LOG_CATEGORY(LogEnemySpawning);

// Sets default values
AMYRoundSpawner::AMYRoundSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMYRoundSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMYRoundSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bShouldDebugLog)
	{
		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Purple, FString::Printf(TEXT("CurrentWave: %i"), CurrentWave));
		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Purple, FString::Printf(TEXT("EnemyCount: %i"), EnemyCount));
		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Purple,
		                                 FString::Printf(TEXT("EnemiesSpawned: %i"), EnemiesSpawned));
		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Purple, FString::Printf(TEXT("EnemyLimit: %i"), EnemyLimit));
		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Purple,
		                                 FString::Printf(TEXT("TotalEnemiesToSpawn: %i"), TotalEnemiesToSpawn));
		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Purple, FString::Printf(TEXT("KillCount: %i"), KillCount));
		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Purple,
		                                 FString::Printf(
			                                 TEXT("bAllEnemiesSpawned: %hs"), bAllEnemiesSpawned ? "true" : "false"));
	}
}

void AMYRoundSpawner::TrySpawnEnemy()
{
	if(EnemyCount == EnemyLimit)
	{
		GetWorldTimerManager().PauseTimer(SpawnerTimerHandle);
		return;
	}
	if(EnemiesSpawned == TotalEnemiesToSpawn)
	{
		GetWorldTimerManager().ClearTimer(SpawnerTimerHandle);
		bAllEnemiesSpawned = true;
		return;
	}
	SpawnEnemy();
}

void AMYRoundSpawner::SpawnEnemy()
{
	EnemyCount++;
	EnemiesSpawned++;
	TArray<AActor*> EnemySpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMYEnemySpawnPoint::StaticClass(), EnemySpawnPoints);
	AActor* Actor = EnemySpawnPoints[FMath::RandRange(0,EnemySpawnPoints.Num()-1)];
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParameters.bNoFail = true;
	AMYCharacterBase* SpawnedActor = GetWorld()->SpawnActor<AMYCharacterBase>(EnemyClass,Actor->GetActorLocation(),Actor->GetActorRotation(), SpawnParameters);
	if(!IsValid(SpawnedActor))
	{
		UE_LOG(LogEnemySpawning, Error, TEXT("Failed to spawn an enemy! | %i"), FDateTime::Now().GetMillisecond());
		EnemyCount--;
		EnemiesSpawned--;
		return;
	}
	if(EnemiesSpawned == TotalEnemiesToSpawn)
	{
		bAllEnemiesSpawned = true;
		GetWorldTimerManager().ClearTimer(SpawnerTimerHandle);
	}
	else if(EnemyCount == EnemyLimit)
	{
		GetWorldTimerManager().PauseTimer(SpawnerTimerHandle);
	}
	SpawnedActor->bIsReady = true;
}

void AMYRoundSpawner::BeginSpawning()
{
	GetWorldTimerManager().SetTimer(SpawnerTimerHandle,this,&AMYRoundSpawner::SpawnEnemy,EnemySpawnTimer,true,0);
}

void AMYRoundSpawner::Spawner_BeginPlay()
{
	StartWave();
}

void AMYRoundSpawner::ActorDied(AActor* DeadActor)
{
	AMYCharacterBase* Enemy = Cast<AMYCharacterBase>(DeadActor);
	if(Enemy != nullptr && Enemy->bWasKilled == false)
	{
		UE_LOG(LogEnemySpawning, Warning, TEXT("Enemy was destroyed but not killed!"));
		return;
	}
	if(DeadActor != nullptr && DeadActor->GetClass() == EnemyClass)
	{
		KillCount++;
		EnemyCount--;
		if(EnemyCount == 0 && bAllEnemiesSpawned)
		{
			EndWave();
		}
		else
		{
			UE_LOG(LogEnemySpawning, Error, TEXT("Enemy Killed! %i/%i remaining! | %i"), TotalEnemiesToSpawn-KillCount, TotalEnemiesToSpawn, FDateTime::Now().GetMillisecond());
			GetWorldTimerManager().UnPauseTimer(SpawnerTimerHandle);
		}
	}
}

void AMYRoundSpawner::StartWave()
{
	CurrentWave++;
	EnemyCount = 0;
	EnemiesSpawned = 0;
	KillCount = 0;
	bAllEnemiesSpawned = false;
	BeginSpawning();
	WaveStarted.Broadcast(CurrentWave);
	UE_LOG(LogEnemySpawning, Warning, TEXT("Wave Started"));
}

void AMYRoundSpawner::EndWave()
{
	TotalEnemiesToSpawn += EnemySpawnCountIncrease;
	WaveEnded.Broadcast(CurrentWave);
	FTimerHandle Th;
	GetWorldTimerManager().SetTimer(Th,this,&AMYRoundSpawner::StartWave,WaveTimer);
	UE_LOG(LogEnemySpawning, Warning, TEXT("Wave Ended"));
}
