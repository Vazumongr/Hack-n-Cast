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

	UFUNCTION(BlueprintCallable, Category="MyPersonalLibrary", meta=(DeterminesOutputType="ClassType", DefaultToSelf="TargetPawn"))
	static AController* GetTypedController(TSubclassOf<AController> ClassType, APawn* TargetPawn);

	UFUNCTION(BlueprintCallable, Category="MyPersonalLibrary", meta=(DeterminesOutputType="ClassType", DefaultToSelf="TargetController"))
	static APawn* GetTypedPawn(TSubclassOf<APawn> ClassType, AController* TargetController);

	UFUNCTION(BlueprintCallable, Category="Math|Vector")
	static float AngleBetweenVectors(const FVector& FirstVector, const FVector& SecondVector);
};
