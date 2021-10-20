// Troy Records Jr. 2021

#include "MyAssetManager.h"
#include "AbilitySystemGlobals.h"

UMyAssetManager& UMyAssetManager::Get()
{
	UMyAssetManager* Singleton = Cast<UMyAssetManager>(GEngine->AssetManager);

	if(Singleton)
	{
		return *Singleton;
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be GDAssetManager!"));
		return *NewObject<UMyAssetManager>();	 // never calls this
	}
}

void UMyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
