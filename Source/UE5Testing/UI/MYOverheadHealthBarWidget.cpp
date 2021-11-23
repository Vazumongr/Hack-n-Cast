// Fill out your copyright notice in the Description page of Project Settings.


#include "MYOverheadHealthBarWidget.h"

#include "UE5Testing/Characters/MYCharacterBase.h"

void UMYOverheadHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMYOverheadHealthBarWidget::SetOwningActor(AActor* InActor)
{
	if(InActor != nullptr)
	OwningActor = InActor;
	AMYCharacterBase* OwningCharacter = Cast<AMYCharacterBase>(OwningActor);
	if(!ensure(OwningCharacter)) return;
	OwningCharacter->HealthChangedDelegate.AddDynamic(this, &UMYOverheadHealthBarWidget::UpdateCurrentHealth);
	OwningCharacter->MaxHealthChangedDelegate.AddDynamic(this, &UMYOverheadHealthBarWidget::UpdateMaxHealth);
	InitializeHealthBar();
}
