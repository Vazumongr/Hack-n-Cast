// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "MYBlueprintLibrary.generated.h"

class AController;
class APawn;

UCLASS()
class UE5TESTING_API UMYBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="MyPersonalLibrary")
	static AController* GetAndCastController(APawn* TargetPawn, TSubclassOf<AController> TargetClass);

	UFUNCTION(BlueprintCallable, Category="Math|Vector")
	static float AngleBetweenVectors(const FVector& FirstVector, const FVector& SecondVector);
};
