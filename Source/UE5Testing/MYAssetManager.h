// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"

#include "MyAssetManager.generated.h"

/**
 * This is my custom asset manager.
 */
UCLASS()
class UE5TESTING_API UMyAssetManager : public UAssetManager
{
    GENERATED_BODY()
    
public:

    static UMyAssetManager& Get();
    
    /** Starts the initial load, gets called from InitializeObjectReferences */
    virtual void StartInitialLoading() override;
};