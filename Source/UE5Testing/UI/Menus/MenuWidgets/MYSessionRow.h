// Troy Records Jr. 2021
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MYSessionRow.generated.h"

/**
 * 
 */
UCLASS()
class UE5TESTING_API UMYSessionRow : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetSessionName(FString InSessionName);
	void SetMainMenu(class UMYMainMenuWidget* InMenu);
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* SessionName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UMYMainMenuWidget* MainMenuWidget;
};
