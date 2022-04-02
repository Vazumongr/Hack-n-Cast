// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5Testing/GameInstances/MYGameInstance.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "UE5Testing/UI/Menus/MYInGameMenuWidget.h"
#include "UE5Testing/UI/Menus/MYMainMenuWidget.h"
#include "UE5Testing/UI/MYHUD.h"

UMYGameInstance::UMYGameInstance()
{
	
}

void UMYGameInstance::Init()
{
	Super::Init();
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if(Subsystem!=nullptr)
	{
		UE_LOG(LogOnline, Error, TEXT("Found subsystem %s."), *Subsystem->GetSubsystemName().ToString());
		SessionInterface = Subsystem->GetSessionInterface();
		if(SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMYGameInstance::CreateSessionComplete);
			UE_LOG(LogOnline, Error, TEXT("Found session interface."));
		}
	}
	else
	{
		UE_LOG(LogOnline, Error, TEXT("No subsystem found."));
	}
	
}

void UMYGameInstance::CreateSessionComplete(FName SessionName, bool Success)
{
	if(!Success) return;
	UWorld* World = GetWorld();
	if(!ensure(World)) return;
	World->ServerTravel("/Game/Levels/Arena?listen");
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,("Host"));
}

void UMYGameInstance::Host()
{
	if(!SessionInterface.IsValid()) return;
	FOnlineSessionSettings SessionSettings;
	SessionInterface->CreateSession(0,TEXT("My Session Game"), SessionSettings);
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

void UMYGameInstance::CreateSession()
{
	
}

void UMYGameInstance::Join(FString IPAddress)
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,FString::Printf(TEXT("Joining: %s"), *IPAddress));
	APlayerController* PlayerController = GetPrimaryPlayerController();
	if(!ensure(PlayerController)) return;
	PlayerController->ClientTravel(IPAddress,ETravelType::TRAVEL_Absolute);
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
