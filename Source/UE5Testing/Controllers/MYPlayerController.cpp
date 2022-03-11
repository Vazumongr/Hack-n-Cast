// Fill out your copyright notice in the Description page of Project Settings.


#include "MYPlayerController.h"

#include "AbilitySystemComponent.h"
#include "UE5Testing/Characters/MYCharacterBase.h"
#include "UE5Testing/Characters/MYPlayerCharacter.h"
#include "UE5Testing/GameStates/MYSurvivalGameState.h"
#include "UE5Testing/UI/MYHUD.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/SpectatorPawn.h"
#include "UE5Testing/FileWritingTest/MYFileIO.h"


// Sets default values
AMYPlayerController::AMYPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMYPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AMYSurvivalGameState* GameState = Cast<AMYSurvivalGameState>(GetWorld()->GetGameState());
	check(GameState)
	GameState->GameOverDelegate.AddUObject(this, &AMYPlayerController::GameOver);
}

// Called every frame
void AMYPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMYPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(FName("Save"), IE_Pressed, this, &AMYPlayerController::Save);
}

void AMYPlayerController::Save()
{
	UMYFileIO::SaveGame();
}

void AMYPlayerController::CreateHUD()
{
	if(HUDWidget) return;
	if(!ensure(HUDClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s() Missing HUDClass. Please fill in on the Blueprint of the PlayerController."), *FString(__FUNCTION__));
		return;
	}
	if(!IsLocalPlayerController()) return;
	AMYPlayerCharacter* PlayerCharacter = GetPawn<AMYPlayerCharacter>();
	if(!ensure(PlayerCharacter)) return;
	HUDWidget = CreateWidget<UMYHUD>(this, HUDClass);
	if(!ensure(HUDWidget)) return;
	HUDWidget->AddToViewport();
	HUDWidget->SetOwningController(this);
}

void AMYPlayerController::CreateVendorMenu_Implementation()
{
	if(!IsLocalPlayerController()) return;
	if(!ensure(VendorMenuClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s() Missing HUDClass. Please fill in on the Blueprint of the PlayerController."), *FString(__FUNCTION__));
		return;
	}
	if(!IsLocalPlayerController()) return;
	VendorMenu = CreateWidget<UUserWidget>(this, VendorMenuClass);
	if(!ensure(VendorMenu)) return;
	VendorMenu->AddToViewport();
	
}

UMYHUD* AMYPlayerController::GetHUD()
{
	return HUDWidget;
}

void AMYPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	// We initialize the client side of the ASC here
	AMYCharacterBase* CharacterBase = Cast<AMYCharacterBase>(P);
	if(CharacterBase != nullptr)
	{
		CharacterBase->GetAbilitySystemComponent()->InitAbilityActorInfo(CharacterBase, CharacterBase);
		CharacterBase->GetAbilitySystemComponent()->SetOwnerActor(CharacterBase);
	}
	
}

void AMYPlayerController::PawnDied()
{
	if(HasAuthority())
		StartSpectating();
}

void AMYPlayerController::GameOver()
{
	if(HasAuthority())
		StartSpectating();
	if(GetNetMode() == NM_DedicatedServer)
	{
		GameOver_DedicatedServer();
		return;
	}
	if(!IsLocalPlayerController()) return;
	if(!ensureAlways(GameOverMessageClass)) return;
	UUserWidget* GameOverMessage = CreateWidget(this, GameOverMessageClass);
	if(!ensureAlways(GameOverMessage)) return;
	GameOverMessage->AddToViewport();
}

void AMYPlayerController::StartSpectating()
{
	ASpectatorPawn* PawnForSpectating = GetWorld()->SpawnActor<ASpectatorPawn>(SpectatorPawnClass);
	check(PawnForSpectating);
	//SetSpectatorPawn(PawnForSpectating);
	Possess(PawnForSpectating);
}


void AMYPlayerController::GameOver_DedicatedServer()
{
	
}

