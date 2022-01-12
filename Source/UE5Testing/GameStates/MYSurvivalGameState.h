// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MYSurvivalGameState.generated.h"

UCLASS()
class UE5TESTING_API AMYSurvivalGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYSurvivalGameState();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void WaveStarted_Multicast(int32 CurrentWave);

	UFUNCTION(NetMulticast, Reliable)
	virtual void WaveEnded_Multicast(int32 CurrentWave);
/*
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	virtual void PrintPlayerController_Multicast();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	virtual void PrintPlayerController_Server();

	UFUNCTION(BlueprintCallable)
	virtual void PrintPlayerController();
*/
	UFUNCTION(BlueprintImplementableEvent)
	void WaveStarted_BIE(int32 CurrentWave);
	
	UFUNCTION(BlueprintImplementableEvent)
	void WaveEnded_BIE(int32 CurrentWave);

	virtual int32 GetCurrentWave();

	virtual int32 GetTotalEnemyThisWaveCount();
/*
	UPROPERTY(BlueprintReadWrite)
	class AMYPlayerController* LocalPlayerController;
	*/
};
