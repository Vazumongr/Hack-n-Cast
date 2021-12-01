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

	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMYOverheadHealthBarComponent* OverheadHealthBar;

public:

	UFUNCTION(BlueprintCallable)
	void IAmATestMethod();

	UFUNCTION(BlueprintCallable)
	void ActivateRightHandWeapon();
	UFUNCTION(BlueprintCallable)
	void ActivateLeftHandWeapon();
	UFUNCTION(BlueprintCallable)
	void DeactivateRightHandWeapon();
	UFUNCTION(BlueprintCallable)
	void DeactivateLeftHandWeapon();
	void ActivateWeapon(class AMYWeapon* WeaponActor);
	void DeactivateWeapon(class AMYWeapon* WeaponActor);
	
	
	UFUNCTION(BlueprintCallable)
	class AMYWeapon* GetWeaponActor() { return RightHandWeapon; }

	UFUNCTION(BlueprintCallable)
	void SetupWeapons(const FGameplayEffectSpecHandle& InGESpecHandle);
	/* All the solely related to GAS stuff STARTS here */
    virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    virtual class UMYAttributeSet* GetAttributeSet() const;

	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void SetOverheadHealthBarWidget(class UMYOverheadHealthBarWidget* InWidget);

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

	UPROPERTY(EditDefaultsOnly)
	FName LeftSocketName;
	UPROPERTY(EditDefaultsOnly)
	FName RightSocketName;
    
protected:
	virtual void InitializeAttributes();
	virtual void InitializeAbilities();
	virtual void SetupAttributeCallbacks();
	virtual void OnRep_Controller() override;
	UFUNCTION(BlueprintCallable)
	virtual void ActivatePrimaryAbility(float num);
	UFUNCTION(BlueprintCallable)
	virtual void ActivateSecondaryAbility();
	virtual void SpawnWeapons();
	virtual void SpawnWeapon(class AMYWeapon*& WeaponActor, TSubclassOf<class AMYWeapon>& RefClass, FName InSocketName);

	/* Attribute Change Handlers */
	void HealthChanged(const FOnAttributeChangeData & Data);
	void MaxHealthChanged(const FOnAttributeChangeData & Data);
	
	UFUNCTION(BlueprintCallable)
	virtual void ActivateAbilityByHandle(FGameplayAbilitySpecHandle InHandle);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MYCharacterBase|UI")
	class UMYOverheadHealthBarWidget* OverheadHealthBarWidget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBase|Combat")
	TSubclassOf<class AMYWeapon> LeftHandWeaponClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MYCharacterBase|Combat")
	class AMYWeapon* LeftHandWeapon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBase|Combat")
	TSubclassOf<class AMYWeapon> RightHandWeaponClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MYCharacterBase|Combat")
	class AMYWeapon* RightHandWeapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MYCharacterBase|Ability System")
	class UMYAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MYCharacterBase|Ability System")
	class UMYAttributeSet* AttributeSet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBase|Ability System")
	TSubclassOf<class UGameplayEffect> DefaultLevel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBase|Ability System")
	TSubclassOf<class UGameplayEffect> LevelUpGameplayEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBase|Ability System")
	TSubclassOf<class UMYGameplayAbility> PrimaryAbility;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBase|Ability System")
	TSubclassOf<class UMYGameplayAbility> SecondaryAbility;
	UPROPERTY(BlueprintReadOnly, Category="MYCharacterBase|Ability System", Replicated)
	FGameplayAbilitySpecHandle PrimaryAbilityHandle;
	UPROPERTY(BlueprintReadOnly, Category="MYCharacterBase|Ability System", Replicated)
	FGameplayAbilitySpecHandle SecondaryAbilityHandle;
	/* All the solely related GAS stuff ENDS here */
};