// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MYHUD.generated.h"

UCLASS()
/**
 * 
 */
class UE5TESTING_API UMYHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetOwningController(class APlayerController* InController);
	UFUNCTION(BlueprintImplementableEvent)
	void OnOwnerSet();
	UFUNCTION(BlueprintNativeEvent)
	void Setup();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APlayerController* PlayerController;
};
