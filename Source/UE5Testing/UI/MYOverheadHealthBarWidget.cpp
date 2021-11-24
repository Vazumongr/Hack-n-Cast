// Fill out your copyright notice in the Description page of Project Settings.


#include "MYOverheadHealthBarWidget.h"

#include "Kismet/KismetSystemLibrary.h"
#include "UE5Testing/Characters/MYCharacterBase.h"

void UMYOverheadHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMYOverheadHealthBarWidget::SetOwningActor(AMYCharacterBase* InMYCharacterBase)
{
	if(InMYCharacterBase != nullptr)
	OwningCharacter = InMYCharacterBase;
	OwningCharacter->HealthChangedDelegate.AddDynamic(this, &UMYOverheadHealthBarWidget::UpdateCurrentHealth);
	OwningCharacter->MaxHealthChangedDelegate.AddDynamic(this, &UMYOverheadHealthBarWidget::UpdateMaxHealth);
	InitializeHealthBar();
}
