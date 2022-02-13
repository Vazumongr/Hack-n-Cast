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

	virtual void GameOver();

	// Will only be called if GameOver is called on the dedicated server
	virtual void GameOver_DedicatedServer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UMYHUD> HUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> GameOverMessageClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UMYHUD* HUDWidget;
};
