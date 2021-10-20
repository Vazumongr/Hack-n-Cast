// Fill out your copyright notice in the Description page of Project Settings.


#include "MYPlayerController.h"

#include "AbilitySystemComponent.h"
#include "UE5Testing/Characters/MYCharacterBase.h"


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

void AMYPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	// We initialize the client side of the ASC here
	AMYCharacterBase* CharacterBase = Cast<AMYCharacterBase>(P);
	UE_LOG(LogTemp, Warning, TEXT("Aknowledging possession"));
	if(CharacterBase != nullptr)
	{
		UE_LOG(LogAbilitySystem, Warning, TEXT("Should be initialized on client"));
		CharacterBase->GetAbilitySystemComponent()->InitAbilityActorInfo(CharacterBase, CharacterBase);
		CharacterBase->GetAbilitySystemComponent()->SetOwnerActor(CharacterBase);
	}
	
}

