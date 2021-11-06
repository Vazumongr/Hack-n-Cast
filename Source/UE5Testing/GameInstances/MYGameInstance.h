// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UE5Testing/Interfaces/MYMainMenuInterface.h"

#include "MYGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5TESTING_API UMYGameInstance : public UGameInstance, public IMYMainMenuInterface
{
	GENERATED_BODY()

public:
	UMYGameInstance();
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void LoadMainMenu();
	
	UFUNCTION(BlueprintCallable)
	void LoadInGameMenu();

	UFUNCTION(Exec)
	void Host();
	
	UFUNCTION(Exec)
	void Join(FString IPAddress);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> MainMenuClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> InGameMenuClass;
	
};
