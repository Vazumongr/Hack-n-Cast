// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "UE5Testing/AbilitySystem/MYGameplayAbility.h"

#include "MYCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStatChangedDelegate, float, NewHealth);

/**
 * This is the base class for all characters implementing an ability system
 */
UCLASS()
class UE5TESTING_API AMYCharacterBase : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
	AMYCharacterBase();

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMYOverheadHealthBar* OverheadHealthBar;

public:
	/* All the solely related to GAS stuff STARTS here */
    virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    virtual class UMYAttributeSet* GetAttributeSet() const;

	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/* Attribute Getters */
	UFUNCTION(BlueprintCallable)
	float GetHealth() const;
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable)
	float GetAttackPower() const;
	UFUNCTION(BlueprintCallable)
	float GetAbilityPower() const;
	UFUNCTION(BlueprintCallable)
	float GetCharacterLevel() const;

	FDelegateHandle AttributeHealthChangedDelegateHandle;
	FDelegateHandle AttributeMaxHealthChangedDelegateHandle;
	UPROPERTY(BlueprintAssignable)
	FStatChangedDelegate HealthChangedDelegate;
	UPROPERTY(BlueprintAssignable)
	FStatChangedDelegate MaxHealthChangedDelegate;
    
protected:
	virtual void InitializeAttributes();
	virtual void InitializeAbilities();
	virtual void SetupAttributeCallbacks();
	virtual void OnRep_Controller() override;
	UFUNCTION(BlueprintCallable)
	virtual void ActivatePrimaryAbility(float num);
	UFUNCTION(BlueprintCallable)
	virtual void ActivateSecondaryAbility();

	/* Attribute Change Handlers */
	void HealthChanged(const FOnAttributeChangeData & Data);
	void MaxHealthChanged(const FOnAttributeChangeData & Data);
	
	UFUNCTION(BlueprintCallable)
	virtual void ActivateAbilityByHandle(FGameplayAbilitySpecHandle InHandle);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability System")
	class UMYAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability System")
	class UMYAttributeSet* AttributeSet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability System")
	TSubclassOf<class UGameplayEffect> DefaultLevel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability System")
	TSubclassOf<class UGameplayEffect> LevelUpGameplayEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability System")
	TSubclassOf<class UMYGameplayAbility> PrimaryAbility;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability System")
	TSubclassOf<class UMYGameplayAbility> SecondaryAbility;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability System", Replicated)
	FGameplayAbilitySpecHandle PrimaryAbilityHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability System", Replicated)
	FGameplayAbilitySpecHandle SecondaryAbilityHandle;
	/* All the solely related GAS stuff ENDS here */
};