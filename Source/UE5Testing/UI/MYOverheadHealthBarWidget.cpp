// Fill out your copyright notice in the Description page of Project Settings.


#include "MYOverheadHealthBarWidget.h"

void UMYOverheadHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(OwningController == nullptr) return;
}

void UMYOverheadHealthBarWidget::SetOwningController(AController* InController)
{
	if(InController != nullptr)
	OwningController = InController;
}

void UMYOverheadHealthBarWidget::SetOwningActor(AActor* InActor)
{
	if(InActor != nullptr)
	OwningActor = InActor;
}
