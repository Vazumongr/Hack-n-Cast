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
	PlayerController->SetShowMouseCursor(true);
	PlayerController->SetInputMode(InputMode);
	
	return true;
}

bool UMYMenuWidgetBase::Teardown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if(!ensure(World)) return false;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController)) return false;
	FInputModeGameOnly InputMode;
	PlayerController->SetShowMouseCursor(false);
	PlayerController->SetInputMode(InputMode);

	return true;
}

void UMYMenuWidgetBase::OnLevelRemovedFromWorld(ULevel* MovieSceneBlends, UWorld* InWorld)
{
	Teardown();
	Super::OnLevelRemovedFromWorld(MovieSceneBlends, InWorld);
}


void UMYMenuWidgetBase::SetInterface(IMYMainMenuInterface* InMainMenuInterface)
{
	if(!ensure(InMainMenuInterface)) return;
	MainMenuInterface = InMainMenuInterface;
	UE_LOG(LogTemp, Warning, TEXT("Interface should be set"));
}