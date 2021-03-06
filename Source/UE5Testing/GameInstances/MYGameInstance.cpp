// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5Testing/GameInstances/MYGameInstance.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "UE5Testing/UI/Menus/MYInGameMenuWidget.h"
#include "UE5Testing/UI/Menus/MYMainMenuWidget.h"
#include "UE5Testing/UI/MYHUD.h"

void UMYGameInstance::Init()
{
	Super::Init();
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if(Subsystem!=nullptr)
	{
		UE_LOG(LogOnline, Error, TEXT("Found subsystem %s."), *Subsystem->GetSubsystemName().ToString());
		OSSName = Subsystem->GetSubsystemName();
		SessionInterface = Subsystem->GetSessionInterface();
		if(SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMYGameInstance::CreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMYGameInstance::OnDestroySessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMYGameInstance::OnJoinSessionComplete);
			UE_LOG(LogOnline, Error, TEXT("Found session interface."));
		}
	}
	else
	{
		UE_LOG(LogOnline, Error, TEXT("No subsystem found."));
	}
	
}

void UMYGameInstance::CreateSessionComplete(FName InSessionName, bool bSuccess)
{
	if(!bSuccess) return;
	UWorld* World = GetWorld();
	if(!ensure(World)) return;
	World->ServerTravel("/Game/Levels/Arena?listen");
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,("Host"));
}

void UMYGameInstance::OnDestroySessionComplete(FName InSessionName, bool bResult)
{
	if(bResult)
	UE_LOG(LogTemp, Warning, TEXT("Session Destroyed"));
}

void UMYGameInstance::Host()
{
	CreateSession();
}

void UMYGameInstance::CreateSession()
{
	if(!SessionInterface.IsValid()) return;
	
	FOnlineSessionSettings SessionSettings;
	if(OSSName.IsEqual(FName(TEXT("NULL"))))
	{
		SessionSettings.bShouldAdvertise	= true;
		SessionSettings.bIsLANMatch			= true;
		SessionSettings.NumPublicConnections = 2;
	}
	else if(OSSName.IsEqual(FName(TEXT("Steam"))))
	{
		SessionSettings.bShouldAdvertise	= true;
		SessionSettings.bIsLANMatch			= false;
		SessionSettings.bUsesPresence		= true;
		SessionSettings.bUseLobbiesIfAvailable = true;
		SessionSettings.NumPublicConnections = 2;
	}
	
    SessionInterface->CreateSession(0,SessionName, SessionSettings);
}

void UMYGameInstance::LoadMainMenu()
{
	if(!ensure(MainMenuClass)) return;
	UMYMainMenuWidget* MainMenu = CreateWidget<UMYMainMenuWidget>(this, MainMenuClass);
	if(!ensure(MainMenu != nullptr)) return;
	MainMenu->Setup();
	MainMenu->SetInterface(this);
}

void UMYGameInstance::LoadInGameMenu()
{
	if(!ensure(InGameMenuClass)) return;
	UMYInGameMenuWidget* InGameMenu = CreateWidget<UMYInGameMenuWidget>(this, InGameMenuClass);
	if(!ensure(InGameMenu != nullptr)) return;
	InGameMenu->SetInterface(this);
	InGameMenu->Setup();
}

void UMYGameInstance::CreateHUD()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if(!ensure(PlayerController)) return;
	if(!ensure(HUDClass)) return;
	UMYHUD* HUD = CreateWidget<UMYHUD>(this, HUDClass);
	if(!ensure(HUD)) return;
	HUD->AddToViewport();
	HUD->SetOwningController(PlayerController);
	HUD->SetOwningPlayer(PlayerController);
}

void UMYGameInstance::FindSessions()
{
	
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if(!SessionInterface.IsValid()) return;

	if(OSSName.IsEqual(FName(TEXT("NULL"))))
	{
		SessionSearch->bIsLanQuery = true;
		//SessionSearch->QuerySettings.Set() // Interfaces with keys defined by OSS API, not FQuerySettings
	}
	else if(OSSName.IsEqual(FName(TEXT("Steam"))))
	{
		SessionSearch->bIsLanQuery = false;
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	}
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMYGameInstance::OnFindSessionsComplete);
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,("Searching"));
}

void UMYGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,("Search Complete"));
	if(!bWasSuccessful) return;

	if(!SessionSearch.IsValid()) return;
	TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
	if(SearchResults.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,("No Sessions Found"));
		return;
	}
	
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,("Found Sessions"));
	for(FOnlineSessionSearchResult SearchResult : SearchResults)
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,FString::Printf(TEXT("Found Session: %s"), *SearchResult.GetSessionIdStr()));
	}

	SessionsFoundDelegate.Execute(SearchResults);
}

void UMYGameInstance::Join(FString IPAddress)
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,FString::Printf(TEXT("Joining: %s"), *IPAddress));
	APlayerController* PlayerController = GetPrimaryPlayerController();
	if(!ensure(PlayerController)) return;
	PlayerController->ClientTravel(IPAddress,ETravelType::TRAVEL_Absolute);
}

void UMYGameInstance::JoinSession(int32 InIndex)
{
	if(!SessionInterface.IsValid() || !SessionSearch.IsValid()) return;
	FOnlineSessionSearchResult& SearchResult = SessionSearch->SearchResults[InIndex];
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,FString::Printf(TEXT("Selected Index: %d"), InIndex));

	//SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMYGameInstance::OnJoinSessionComplete);
	SessionInterface->JoinSession(0, FName(SearchResult.GetSessionIdStr()), SearchResult);
}

void UMYGameInstance::OnJoinSessionComplete(FName InName, EOnJoinSessionCompleteResult::Type InType)
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,TEXT("OnJoinSessionComplete"));
	if(InType != EOnJoinSessionCompleteResult::Success || !SessionInterface.IsValid()) return;
	FString Address;
	if(!SessionInterface->GetResolvedConnectString(InName, Address)) return;
	
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,FString::Printf(TEXT("Address: %s"), *Address));
	
	APlayerController* PlayerController = GetPrimaryPlayerController();
	if(!ensure(PlayerController)) return;
	PlayerController->ClientTravel(Address,ETravelType::TRAVEL_Absolute);
}

void UMYGameInstance::QuitToMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("Quitting to main menu"));
	APlayerController* PlayerController = GetPrimaryPlayerController();
	if(!ensure(PlayerController)) return;
	PlayerController->ClientTravel("/Game/Levels/MainMenuLevel",ETravelType::TRAVEL_Absolute);
}

void UMYGameInstance::QuitGame()
{
	UWorld* World = GetWorld();
	if(!ensure(World)) return;
	APlayerController* PlayerController = GetPrimaryPlayerController();
	if(!ensure(PlayerController)) return;
	PlayerController->ConsoleCommand("quit");
}

void UMYGameInstance::Shutdown()
{
	SessionInterface->DestroySession(SessionName);
	Super::Shutdown();
}
