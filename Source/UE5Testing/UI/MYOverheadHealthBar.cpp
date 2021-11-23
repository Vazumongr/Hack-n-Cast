#include "MYOverheadHealthBar.h"

#include "MYOverheadHealthBarWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UE5Testing/UE5Testing.h"

UMYOverheadHealthBar::UMYOverheadHealthBar()
{
	SetTickMode(ETickMode::Automatic);
}

void UMYOverheadHealthBar::TickComponent(float DeltaTime, ELevelTick Tick,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);
	if(!ensure(PlayerController)) return;
	if(!ensure(PlayerController->PlayerCameraManager)) return;
	const FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(), PlayerController->PlayerCameraManager->GetCameraLocation());
	SetWorldRotation(Rotation);
}

void UMYOverheadHealthBar::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if(!ensure(World)) return;
	PlayerController = World->GetFirstPlayerController();
}

void UMYOverheadHealthBar::InitWidget()
{
	Super::InitWidget();
	UUserWidget* UserWidget = GetWidget();
	if(UserWidget == nullptr)
		UKismetSystemLibrary::PrintString(this, "Too early!");
	UMYOverheadHealthBarWidget* OverheadHealthBar = Cast<UMYOverheadHealthBarWidget>(UserWidget);
	if(OverheadHealthBar == nullptr)
		return;
	OverheadHealthBar->SetOwningActor(GetOwner());
	return;
	
}



