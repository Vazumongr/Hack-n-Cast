// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE5Testing/UI/MYMenuWidgetBase.h"
#include "MYInGameMenuWidget.generated.h"

/**
* 
*/
UCLASS()
class UE5TESTING_API UMYInGameMenuWidget : public UMYMenuWidgetBase
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

private:
	UFUNCTION()
	void Quit();
	UFUNCTION()
	void Cancel();
	
};