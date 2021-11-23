// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MYOverheadHealthBarWidget.generated.h"

UCLASS()
/**
* 
*/
class UE5TESTING_API UMYOverheadHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
	public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void SetOwningController(class AController* InController);
	
	UFUNCTION(BlueprintCallable)
	void SetOwningActor(class AActor* InActor);

	protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AController* OwningController;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AActor* OwningActor;
	
};
