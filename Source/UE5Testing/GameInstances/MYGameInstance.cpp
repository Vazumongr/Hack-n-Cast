// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5Testing/GameInstances/MYGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "UE5Testing/UI/MYInGameMenuWidget.h"
#include "UE5Testing/UI/MYMainMenuWidget.h"

UMYGameInstance::UMYGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor"));
}

void UMYGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Init"));
}

void UMYGameInstance::Host()
{
	UWorld* World = GetWorld();
	if(!ensure(World)) return;
	World->ServerTravel("/Game/Levels/Arena?listen");
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,("Host"));
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
	InGameMenu->Setup();
}

void UMYGameInstance::Join(FString IPAddress)
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,FString::Printf(TEXT("Joining: %s"), *IPAddress));
	APlayerController* PlayerController = GetPrimaryPlayerController();
	if(!ensure(PlayerController)) return;
	PlayerController->ClientTravel(IPAddress,ETravelType::TRAVEL_Absolute);
}
