// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "UE5Testing/AbilitySystem/MYGameplayAbility.h"
#include "UE5Testing/Loot/MYLootEnums.h"

#include "MYCharacterBase.generated.h"

class AMYWeaponBase;
class AMYWeapon;
class UMYOverheadHealthBar;
class UMYOverheadHealthBarComponent;

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

	virtual void Destroyed() override;

	virtual void DestroyPrep();

	virtual void GameOver();

	UFUNCTION(BlueprintNativeEvent)
	void Die();
	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Die_Server();

	UFUNCTION(BlueprintCallable)
	class UMYInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	UFUNCTION(BlueprintCallable)
	void SetupWeapons(const FGameplayEffectSpecHandle& InGESpecHandle);
	
	
    virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    virtual class UMYAttributeSet* GetAttributeSet() const;

	virtual class AMYWeaponBase* GetWeapon() const { return Weapon; };

	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void SetOverheadHealthBarWidget(class UMYOverheadHealthBarWidget* InWidget);

	void ActivatePrimaryAbility();

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
	
	bool bWasKilled{false};
	
	// This lil bugger prevents the actor from dying prematurely in the case it spawns inside of a collider
	UPROPERTY(Replicated)
	bool bIsReady{false};
	
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

	virtual void SpawnWeaponsOnServer(int8 WeaponIdx);
	UFUNCTION(Server, Reliable)
	virtual void SpawnWeaponsOnServer_Server(int8 WeaponIdx);

	virtual void DownedTagAddedOrRemoved(const FGameplayTag CallbackTag, int32 NewCount);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_DownedTagAddedOrRemoved(const FGameplayTag CallbackTag, int32 NewCount);
	/* Attribute Change Handlers */
	virtual void HealthChanged(const FOnAttributeChangeData & Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData & Data);
	
	UFUNCTION(BlueprintCallable)
	virtual void ActivateAbilityByHandle(FGameplayAbilitySpecHandle InHandle);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMYOverheadHealthBarComponent* OverheadHealthBar;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MYCharacterBase|UI")
	class UMYOverheadHealthBarWidget* OverheadHealthBarWidget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MYCharacterBase|Inventory")
	class UMYInventoryComponent* InventoryComponent;
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category="MYCharacterBase|Combat")
	class AMYWeaponBase* Weapon;
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBase|Combat")
	TSubclassOf<class AMYWeaponBase> WeaponClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	uint8 AttackChainCounter{0};
	
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MYCharacterBase|Ability System")
	TSubclassOf<class UMYGameplayAbility> DownedAbility;
	UPROPERTY(BlueprintReadOnly, Category="MYCharacterBase|Ability System", Replicated)
	FGameplayAbilitySpecHandle PrimaryAbilityHandle;
	UPROPERTY(BlueprintReadOnly, Category="MYCharacterBase|Ability System", Replicated)
	FGameplayAbilitySpecHandle SecondaryAbilityHandle;
	/* All the solely related GAS stuff ENDS here */
};