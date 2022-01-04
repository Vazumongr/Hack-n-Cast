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

	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintCallable)
	void SpawnDrops();
	UFUNCTION()
	void SpawnEnemy();

	UPROPERTY(EditAnywhere)
	uint8 CharNumber = 0;

	int8 CurrentWave{0};
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AActor> EnemySpawnerClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AActor> EnemyClass;
};
