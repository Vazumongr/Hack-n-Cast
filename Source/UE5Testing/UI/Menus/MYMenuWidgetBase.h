// Troy Records Jr. 2021
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MYMenuWidgetBase.generated.h"
/**
 * Base class for menus
 */
UCLASS()
class UE5TESTING_API UMYMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual bool Setup();
	UFUNCTION(BlueprintCallable)
	virtual bool Teardown();
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
	void SetInterface(class IMYMainMenuInterface* InMainMenuInterface);
	class IMYMainMenuInterface* MainMenuInterface;
};