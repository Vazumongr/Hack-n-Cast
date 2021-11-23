// Troy Records Jr. 2021
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MYMenuWidgetBase.generated.h"
/**
 * 
 */
UCLASS()
class UE5TESTING_API UMYMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Setup();
	virtual bool Teardown();
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
	void SetInterface(class IMYMainMenuInterface* InMainMenuInterface);
	class IMYMainMenuInterface* MainMenuInterface;
};