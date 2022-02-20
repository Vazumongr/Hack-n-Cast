// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE5Testing/Loot/MYLootEnums.h"

#include "MYItemBase.generated.h"

class UMYGameplayAbility;
class UMYItemData;

UCLASS(Abstract, NotPlaceable, Blueprintable, BlueprintType)
class UE5TESTING_API AMYItemBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYItemBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetItemData(TObjectPtr<class UMYItemData> InItemData);
	UFUNCTION(BlueprintCallable)
	void SetOwnerASC(class UAbilitySystemComponent* InOwnerASC);
	UFUNCTION(BlueprintCallable)
	void SetOwningCharacter(class AMYCharacterBase* InOwningCharacter);

	virtual void Deconstruct();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Replicated)
	TObjectPtr<class UMYItemData> ItemData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated)
	TObjectPtr<class UMYItemData> NonInstancedItemData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	class AMYCharacterBase* OwningCharacter;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	class UAbilitySystemComponent* OwnerASC;
	

};
