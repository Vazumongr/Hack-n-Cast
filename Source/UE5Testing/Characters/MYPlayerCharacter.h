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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void DownedTagAddedOrRemoved(const FGameplayTag CallbackTag, int32 NewCount) override;
	virtual void HealthChanged(const FOnAttributeChangeData & Data) override;

	virtual void MoveForward(float InputValue);
	virtual void MoveRight(float InputValue);
	virtual void PrimaryAttack();
	virtual void MyCrouch();
	virtual void MyInteract();

	UFUNCTION()
	virtual void LootPickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USphereComponent* LootPickerUpper;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	uint8 AttackChainCounter{0};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MovementSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MouseSensitivity = 1;
};