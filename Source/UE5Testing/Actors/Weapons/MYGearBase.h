// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MYGearBase.generated.h"

UCLASS()
class UE5TESTING_API AMYGearBase : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYGearBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
