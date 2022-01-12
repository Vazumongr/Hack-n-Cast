// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MYSurvivalGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UE5TESTING_API AMYSurvivalGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintCallable)
	void SpawnDrops();

	virtual void ActorDied(AActor* DeadActor);

	void WaveStarted(int32 InWave);
	void WaveEnded(int32 InWave);

protected:
	UPROPERTY(EditAnywhere)
	uint8 CharNumber = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AMYRoundSpawner> SpawnerClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AMYRoundSpawner* Spawner;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AMYRoundSpawner> LootSpawnerClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AMYRoundSpawner* LootSpawner;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AActor> LootClass;
};
