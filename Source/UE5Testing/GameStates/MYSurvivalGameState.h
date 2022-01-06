// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MYSurvivalGameState.generated.h"

UCLASS()
class UE5TESTING_API AMYSurvivalGameState : public AGameState
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYSurvivalGameState();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual int32 GetCurrentWave();

	virtual int32 GetTotalEnemyThisWaveCount();
protected:
};
