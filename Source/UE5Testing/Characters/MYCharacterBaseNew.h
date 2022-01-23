// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "UE5Testing/AbilitySystem/MYGameplayAbility.h"
#include "UE5Testing/Loot/MYLootEnums.h"

#include "MYCharacterBaseNew.generated.h"

class AMYWeaponBase;
class AMYWeapon;
class UMYOverheadHealthBar;
class UMYOverheadHealthBarComponent;

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStatChangedDelegate, float, NewHealth);

/**
 * This is the base class for all characters implementing an ability system
 */
UCLASS()
class UE5TESTING_API AMYCharacterBaseNew : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
	AMYCharacterBaseNew();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	virtual void Destroyed() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMYOverheadHealthBarComponent* OverheadHealthBar;

public:
	bool bWasKilled{false};
	
	// This lil bugger prevents the actor from dying prematurely in the case it spawns inside of a collider
	UPROPERTY(Replicated)
	bool bIsReady{false};

	UFUNCTION(BlueprintNativeEvent)
	void Die();
	
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
	class AMYWeapon* GetWeaponActor() const { return RightHandWeapon; }

	UFUNCTION(BlueprintCallable)
	class UMYInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

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
	//UPROPERTY(BlueprintAssignable)
	//FStatChangedDelegate HealthChangedDelegate;
	//UPROPERTY(BlueprintAssignable)
	//FStatChangedDelegate MaxHealthChangedDelegate;

	UPROPERTY(EditAnywhere, Category="Setup")
	FRotator RightHandWeaponRotation;
	UPROPERTY(EditAnywhere, Category="Setup")
	FRotator LeftHandWeaponRotation;

	UPROPERTY(EditDefaultsOnly)
	FName LeftSocketName;
	UPROPERTY(EditDefaultsOnly)
	FName RightSocketName;
    
protected:
	virtual void InitializeAttributes();
	virtual void InitializeAbilities();
	virtual void SetupAttributeCallbacks();
	virtual void SetupDelegates();
	virtual void OnRep_Controller() override;
	virtual void SpawnWeapons();
	virtual void SpawnWeapon();
	virtual void SpawnWeapon(class AMYWeapon*& WeaponActor, TSubclassOf<class AMYWeapon>& RefClass, FName InSocketName, FRotator SpawnWeaponRotation);
	UFUNCTION(Client, Reliable)
	virtual void SpawnWeapons_Client();

	virtual void DownedTagAddedOrRemoved(const FGameplayTag CallbackTag, int32 NewCount);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_DownedTagAddedOrRemoved(const FGameplayTag CallbackTag, int32 NewCount);
	/* Attribute Change Handlers */
	virtual void HealthChanged(const FOnAttributeChangeData & Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData & Data);
	
	UFUNCTION(BlueprintCallable)
	virtual void ActivateAbilityByHandle(FGameplayAbilitySpecHandle InHandle);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MYCharacterBaseNew|UI")
	class UMYOverheadHealthBarWidget* OverheadHealthBarWidget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBaseNew|Combat")
	TSubclassOf<class AMYWeapon> RightHandWeaponClass;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category="MYCharacterBaseNew|Combat")
	class AMYWeapon* RightHandWeapon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBaseNew|Combat")
	TSubclassOf<class AMYWeapon> LeftHandWeaponClass;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category="MYCharacterBaseNew|Combat")
	class AMYWeapon* LeftHandWeapon;
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category="MYCharacterBaseNew|Inventory")
	class UMYInventoryComponent* InventoryComponent;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category="MYCharacterBaseNew|Combat")
	class AMYWeaponBase* WeaponItemThing;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBaseNew|Combat")
	TSubclassOf<class AMYWeaponBase> WeaponClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MYCharacterBaseNew|Ability System")
	class UMYAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MYCharacterBaseNew|Ability System")
	class UMYAttributeSet* AttributeSet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBaseNew|Ability System")
	TSubclassOf<class UGameplayEffect> DefaultLevel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBaseNew|Ability System")
	TSubclassOf<class UGameplayEffect> LevelUpGameplayEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBaseNew|Ability System")
	TSubclassOf<class UMYGameplayAbility> PrimaryAbility;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBaseNew|Ability System")
	TSubclassOf<class UMYGameplayAbility> SecondaryAbility;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBaseNew|Ability System")
	TSubclassOf<class UMYGameplayAbility> DownedAbility;
	UPROPERTY(BlueprintReadOnly, Category="MYCharacterBaseNew|Ability System", Replicated)
	FGameplayAbilitySpecHandle PrimaryAbilityHandle;
	UPROPERTY(BlueprintReadOnly, Category="MYCharacterBaseNew|Ability System", Replicated)
	FGameplayAbilitySpecHandle SecondaryAbilityHandle;
	/* All the solely related GAS stuff ENDS here */
};