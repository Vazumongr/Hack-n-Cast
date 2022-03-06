// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MYVendor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogVendor, All, All);

UCLASS()
class UE5TESTING_API AMYVendor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYVendor();

	void Activate();
	void Deactivate();
	void Interact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
