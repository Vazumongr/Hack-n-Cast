// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
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
	virtual void Init() override;
	void CreateSessionComplete(FName InSessionName, bool bResult);
	void OnDestroySessionComplete(FName InSessionName, bool bResult);

	UFUNCTION(BlueprintCallable)
	void LoadMainMenu();
	
	UFUNCTION(BlueprintCallable)
	void LoadInGameMenu();

	UFUNCTION(BlueprintCallable)
	void CreateHUD();

	virtual void FindSessions() override;
	void OnFindSessionsComplete(bool bWasSuccessful);

	UFUNCTION(Exec)
	void Host();
	void CreateSession();

	UFUNCTION(Exec)
	void Join(FString IPAddress);
	void JoinSession(int32 InIndex);
	void OnJoinSessionComplete(FName InName, EOnJoinSessionCompleteResult::Type InType);

	virtual void QuitToMainMenu() override;
	virtual void QuitGame() override;

	virtual void Shutdown() override;

	const FName SessionName = TEXT("My Session Game");

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> MainMenuClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> InGameMenuClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> HUDClass;

protected:
	IOnlineSessionPtr SessionInterface;
};
