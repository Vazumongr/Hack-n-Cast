// Troy Records Jr. 2021
#include "MYMenuWidgetBase.h"

bool UMYMenuWidgetBase::Setup()
{
	AddToViewport();
	UWorld* World = GetWorld();
	if(!ensure(World)) return false;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController)) return false;
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputMode);
	
	return true;
}

bool UMYMenuWidgetBase::Teardown()
{
	RemoveFromViewport();
	UWorld* World = GetWorld();
	if(!ensure(World)) return false;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController)) return false;
	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);

	return true;
}
