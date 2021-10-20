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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MovementSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MouseSensitivity = 1;
};