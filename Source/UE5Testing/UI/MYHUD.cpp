// Fill out your copyright notice in the Description page of Project Settings.


#include "MYHUD.h"

void UMYHUD::SetOwningController(APlayerController* InController)
{
	if(!ensure(InController)) return;
	PlayerController = InController;
	OnOwnerSet();
}

void UMYHUD::Setup_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("%s not overriden!"), *FString(__FUNCTION__));
}
