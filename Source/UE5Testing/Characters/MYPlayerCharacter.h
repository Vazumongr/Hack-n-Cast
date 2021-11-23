// Troy Records Jr. 2021

#pragma once
#include "MYCharacterBase.h"

#include "MYPlayerCharacter.generated.h"


/**
 * This is the base class for all characters implementing an ability system
 */
UCLASS()
class UE5TESTING_API AMYPlayerCharacter : public AMYCharacterBase
{
    GENERATED_BODY()

	AMYPlayerCharacter();
public:
	virtual void AddControllerPitchInput(float Val) override;
	virtual void AddControllerYawInput(float Val) override;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void MoveForward(float InputValue);
	virtual void MoveRight(float InputValue);
	virtual void PrimaryAttack();

	UFUNCTION()
	virtual void LootPickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USphereComponent* LootPickerUpper;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 AttackChainCounter{0};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MovementSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MouseSensitivity = 1;
};