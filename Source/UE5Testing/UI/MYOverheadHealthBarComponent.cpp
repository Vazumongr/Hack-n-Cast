#include "MYOverheadHealthBarComponent.h"

#include "MYOverheadHealthBarWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "UE5Testing/Characters/MYCharacterBase.h"

UMYOverheadHealthBarComponent::UMYOverheadHealthBarComponent()
{
	SetTickMode(ETickMode::Automatic);
}

void UMYOverheadHealthBarComponent::TickComponent(float DeltaTime, ELevelTick Tick,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);
	if(!PlayerController) return;
	if(!PlayerController->PlayerCameraManager) return;
	const FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(), PlayerController->PlayerCameraManager->GetCameraLocation());
	SetWorldRotation(Rotation);
}

void UMYOverheadHealthBarComponent::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if(!ensure(World)) return;
	PlayerController = World->GetFirstPlayerController();
}

void UMYOverheadHealthBarComponent::InitWidget()
{
	Super::InitWidget();
	AActor* Owner = GetOwner();
	if(Owner == nullptr) return;
	UUserWidget* UserWidget = GetWidget();
	if(UserWidget == nullptr) return;
	UMYOverheadHealthBarWidget* OverheadHealthBarWidget = Cast<UMYOverheadHealthBarWidget>(UserWidget);
	if(OverheadHealthBarWidget == nullptr) return;
	AMYCharacterBase* OwningCharacter = Cast<AMYCharacterBase>(Owner);
	if(OwningCharacter == nullptr) return;
	OverheadHealthBarWidget->SetOwningActor(OwningCharacter);
	OwningCharacter->SetOverheadHealthBarWidget(OverheadHealthBarWidget);
}



