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
	PrimaryActorTick.bCanEverTick = false;
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
	TArray<AActor*> LootSpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMYEnemySpawnPoint::StaticClass(), LootSpawnPoints);
	AActor* Actor = LootSpawnPoints[FMath::RandRange(0,2)];
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(EnemyClass,Actor->GetActorLocation(),Actor->GetActorRotation(), SpawnParameters);
	if(SpawnedActor == nullptr)
	{
		UE_LOG(LogEnemySpawning, Error, TEXT("Failed to spawn an enemy!"));
		return;
	}
	EnemyCount++;
	EnemiesSpawned++;
}

void AMYRoundSpawner::BeginSpawning()
{
	GetWorldTimerManager().SetTimer(SpawnerTimerHandle,this,&AMYRoundSpawner::TrySpawnEnemy,EnemySpawnTimer,true,0);
}

void AMYRoundSpawner::Spawner_BeginPlay()
{
	StartWave();
}

void AMYRoundSpawner::ActorDied(AActor* DeadActor)
{
	if(DeadActor != nullptr && DeadActor->GetClass() == EnemyClass)
	{
		KillCount++;
		if(--EnemyCount == 0 && bAllEnemiesSpawned)
		{
			EndWave();
		}
		else
		{
			UE_LOG(LogEnemySpawning, Error, TEXT("Enemy Killed! %i/%i remaining!"), TotalEnemiesToSpawn-KillCount, TotalEnemiesToSpawn);
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
	GetWorldTimerManager().SetTimer(Th,this,&AMYRoundSpawner::StartWave,5.f);
	UE_LOG(LogEnemySpawning, Warning, TEXT("Wave Ended"));
}

