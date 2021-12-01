// Fill out your copyright notice in the Description page of Project Settings.


#include "MYPlayerController.h"

#include "AbilitySystemComponent.h"
#include "UE5Testing/Characters/MYCharacterBase.h"
#include "UE5Testing/Characters/MYPlayerCharacter.h"
#include "UE5Testing/UI/MYHUD.h"
#include "Blueprint/UserWidget.h"


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
	
}

// Called every frame
void AMYPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

