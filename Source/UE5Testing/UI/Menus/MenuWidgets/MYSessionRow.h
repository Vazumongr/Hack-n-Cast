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
	void SetSession(FOnlineSessionSearchResult* InSession);
	void SetSession(FOnlineSessionSearchResult& InSession);
	void SetIndex(int32 InIndex);
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* SessionName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	int32 Index;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UMYMainMenuWidget* MainMenuWidget;

	FOnlineSessionSearchResult* Session;
	TSharedPtr<FOnlineSessionSearchResult> SessionPtr;
};
