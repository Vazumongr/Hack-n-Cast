// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "UE5Testing/AbilitySystem/MYGameplayAbility.h"

#include "MYCharacterBase.generated.h"


/**
 * This is the base class for all characters implementing an ability system
 */
UCLASS()
class UE5TESTING_API AMYCharacterBase : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
	AMYCharacterBase();


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
    
protected:
	virtual void InitializeAttributes();
	virtual void InitializeAbilities();
	virtual void OnRep_Controller() override;
	UFUNCTION(BlueprintCallable)
	virtual void ActivatePrimaryAbility();
	UFUNCTION(BlueprintCallable)
	virtual void ActivateSecondaryAbility();
	
	UFUNCTION(BlueprintCallable)
	virtual void ActivateAbilityByHandle(FGameplayAbilitySpecHandle InHandle);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability System")
	class UMYAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability System")
	class UMYAttributeSet* AttributeSet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability System")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability System")
	TSubclassOf<class UMYGameplayAbility> PrimaryAbility;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability System")
	TSubclassOf<class UMYGameplayAbility> SecondaryAbility;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability System")
	TArray<TSubclassOf<class UMYGameplayAbility>> DefaultAbilities;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability System", Replicated)
	FGameplayAbilitySpecHandle PrimaryAbilityHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability System", Replicated)
	FGameplayAbilitySpecHandle SecondaryAbilityHandle;
	/* All the solely related GAS stuff ENDS here */
};