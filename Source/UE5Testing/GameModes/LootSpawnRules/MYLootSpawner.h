// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MYLootSpawner.generated.h"

UENUM()
enum class FMYLootSpawnRules
{
	SameLootSeparated,
	DifferentLootSeperated
};

UCLASS()
class UE5TESTING_API AMYLootSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYLootSpawner();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FMYLootSpawnRules LootSpawnRules;
};
