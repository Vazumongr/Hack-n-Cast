// Troy Records Jr. 2021
#pragma once

#include "CoreMinimal.h"
#include "MYMainMenuInterface.generated.h"

// This class does not need to be modified
UINTERFACE(MinimalAPI)
class UMYMainMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class UE5TESTING_API IMYMainMenuInterface
{
	GENERATED_BODY()
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface
public:
	UFUNCTION(Exec)
	virtual void Host() = 0;
	
	UFUNCTION(Exec)
	virtual void Join(FString IPAddress) = 0;
};