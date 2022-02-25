// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MYEnemyController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAI, All, All);


UCLASS()
class UE5TESTING_API AMYEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYEnemyController();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ActivatePrimaryAbility() const;

	virtual void OnPossess(APawn* InPawn) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GameOver();

	// Will only be called if GameOver is called on the dedicated server
	virtual void GameOver_DedicatedServer();

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviorTree;

	UPROPERTY()
	class AMYCharacterBase* BaseCharacter;
};
