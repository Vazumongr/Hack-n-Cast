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

	UFUNCTION(BlueprintCallable)
	void CreateHUD();

	UFUNCTION(Exec)
	void Host();
	
	UFUNCTION(Exec)
	void Join(FString IPAddress);

	virtual void QuitToMainMenu() override;
	virtual void QuitGame() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> MainMenuClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> InGameMenuClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> HUDClass;
	
};
