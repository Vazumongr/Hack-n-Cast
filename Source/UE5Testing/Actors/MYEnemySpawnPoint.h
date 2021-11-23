// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "MYEnemySpawnPoint.generated.h"

UCLASS()
class UE5TESTING_API AMYEnemySpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYEnemySpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
