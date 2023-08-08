// Troy Records Jr. 2021


#include "MYBlueprintLibrary.h"

#include "GameFramework/Controller.h"

AController* UMYBlueprintLibrary::GetTypedController(TSubclassOf<AController> ClassType, APawn* TargetPawn)
{
	if(TargetPawn->GetController()->IsA(ClassType))
	{
		return TargetPawn->GetController();
	}
	return nullptr;
}

APawn* UMYBlueprintLibrary::GetTypedPawn(TSubclassOf<APawn> ClassType, AController* TargetController)
{
	if(TargetController->GetPawn()->IsA(ClassType))
	{
		return TargetController->GetPawn();
	}
	return nullptr;
}

float UMYBlueprintLibrary::AngleBetweenVectors(const FVector& FirstVector, const FVector& SecondVector)
{
	return FMath::Acos((FVector::DotProduct(FirstVector, SecondVector)) / (FirstVector.Length() * SecondVector.Length()));
}
