// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE5Testing/UI/Menus/MYMenuWidgetBase.h"
#include "MYMainMenuWidget.generated.h"

/**
* 
*/
UCLASS()
class UE5TESTING_API UMYMainMenuWidget : public UMYMenuWidgetBase
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UButton* HostButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UButton* JoinButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UScrollBox* SessionList;

	void OnSessionsFound(TArray<FOnlineSessionSearchResult> Sessions);

private:
	UFUNCTION()
	void Host();
	UFUNCTION(BlueprintCallable)
	void JoinServer(FString IPAddress);
	UFUNCTION()
	void Join();
	UFUNCTION()
	void Quit();


	
	
};