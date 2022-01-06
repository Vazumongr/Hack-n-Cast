// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "MYRoundSpawner.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogEnemySpawning, All, All);

DECLARE_MULTICAST_DELEGATE_OneParam(FWaveChangeDelegate, int32 CurrentWave);

UCLASS(notplaceable, BlueprintType, Blueprintable, Transient, hideCategories = (Info, Rendering, MovementReplication, Replication, Actor))
class UE5TESTING_API AMYRoundSpawner : public AInfo
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYRoundSpawner();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginSpawning();
	virtual void Spawner_BeginPlay();
	virtual void ActorDied(AActor* DeadActor);
	
	virtual FWaveChangeDelegate& GetWaveStartedDelegate() { return WaveStarted; }
	virtual FWaveChangeDelegate& GetWaveEndedDelegate() { return WaveEnded; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void TrySpawnEnemy();
	virtual void SpawnEnemy();
	virtual void StartWave();
	virtual void EndWave();

	FWaveChangeDelegate WaveStarted;
	FWaveChangeDelegate WaveEnded;

	FTimerHandle SpawnerTimerHandle;

	bool bAllEnemiesSpawned = false;

	/** Current wave **/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 CurrentWave{0};
	
	/** Current amount of enemies alive **/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 EnemyCount{0};
	
	/** Amount of enemies spawned this wave **/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 EnemiesSpawned{0};
	
	/** Maximum number of enemies allowed to be alive at a time **/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 EnemyLimit{10};

	/** Total amount of enemies to be spawned for the current wave **/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 TotalEnemiesToSpawn{10};
	
	/** Amount to increase wave enemy count by after each wave **/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 EnemySpawnCountIncrease{5};

	/** The time between enemy spawns **/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 EnemySpawnTimer{5};
	
	/** The time between waves  **/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 WaveTimer{5};
	
	int32 KillCount{0};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AActor> EnemyClass;
	
};
