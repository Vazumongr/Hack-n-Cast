// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MYPlayerController.generated.h"

UCLASS()
class UE5TESTING_API AMYPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYPlayerController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void CreateHUD();

	class UMYHUD* GetHUD();

	virtual void AcknowledgePossession(APawn* P) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UMYHUD> HUDClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UMYHUD* HUDWidget;
};
