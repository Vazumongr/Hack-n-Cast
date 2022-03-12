// Troy Records Jr. 2021


#include "MYBlueprintLibrary.h"

#include "GameFramework/Controller.h"

AController* UMYBlueprintLibrary::GetAndCastController(APawn* TargetPawn, TSubclassOf<AController> TargetClass)
{
	if(TargetPawn==nullptr) return nullptr;
	if(TargetPawn->GetController()->IsA(TargetClass))
	{
		return TargetPawn->GetController();
	}
	return nullptr;
}

float UMYBlueprintLibrary::AngleBetweenVectors(const FVector& FirstVector, const FVector& SecondVector)
{
	return FMath::Acos((FVector::DotProduct(FirstVector, SecondVector)) / (FirstVector.Length() * SecondVector.Length()));
}
