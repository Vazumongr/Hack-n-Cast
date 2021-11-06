// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE5Testing/UI/MYMenuWidgetBase.h"
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
	void SetInterface(class IMYMainMenuInterface* InMainMenuInterface);

	
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

private:
	UFUNCTION()
	void Host();
	UFUNCTION()
	void Join();


	
	class IMYMainMenuInterface* MainMenuInterface;
	
};