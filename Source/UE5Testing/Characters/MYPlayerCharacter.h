// Troy Records Jr. 2021

#pragma once
#include "MYCharacterBase.h"

#include "MYPlayerCharacter.generated.h"

class UCameraComponent;
class UMYStartingKitBaseDA;
class USphereComponent;
class USpringArmComponent;

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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BuffYourself();
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void BuffYourself_Server();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Destroyed() override;
	virtual void DownedTagAddedOrRemoved(const FGameplayTag CallbackTag, int32 NewCount) override;
	virtual void HealthChanged(const FOnAttributeChangeData & Data) override;
	virtual void BeginPlay() override;
	virtual void SelectFirstWeapon();
	virtual void SelectSecondWeapon();
	//virtual void SpawnWeapon(int8 WeaponIdx);

	virtual void MoveForward(float InputValue);
	virtual void MoveRight(float InputValue);
	virtual void PrimaryAttack();
	virtual void MyCrouch();
	virtual void Interact();
	UFUNCTION(BlueprintCallable)
	virtual void SetStartingKit(class UMYStartingKitBaseDA* InStartingKit);
	UFUNCTION(Server, Reliable)
	virtual void SetStartingKit_Server(class UMYStartingKitBaseDA* InStartingKit);

	UFUNCTION()
	virtual void LootPickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class USphereComponent* LootPickerUpper;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MovementSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MouseSensitivity = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Setup")
	FVector InteractShapeSize{50,50,50};
};