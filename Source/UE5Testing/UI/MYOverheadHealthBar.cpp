#include "MYOverheadHealthBar.h"

#include "MYOverheadHealthBarWidget.h"
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
	//AddLocalRotation(FRotator(10,0,0));
}

void UMYOverheadHealthBar::BeginPlay()
{
	Super::BeginPlay();
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
	APawn* Pawn = Cast<APawn>(GetOwner());
	if(!ensure(Pawn)) return;
	AController* Controller = Pawn->GetController();
	if(!ensure(Controller)) return;
	OverheadHealthBar->SetOwningController(Controller);
	
}



