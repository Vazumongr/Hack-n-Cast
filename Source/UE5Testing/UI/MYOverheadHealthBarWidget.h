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
	void SetOwningActor(class AMYCharacterBase* InCharacterBase);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCurrentHealth(float NewCurrentHealth);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateMaxHealth(float NewMaxHealth);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void InitializeHealthBar();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AMYCharacterBase* OwningCharacter;
	
};
