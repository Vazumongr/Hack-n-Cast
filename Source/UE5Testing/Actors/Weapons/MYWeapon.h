// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Engine/StaticMeshActor.h"
#include "MYWeapon.generated.h"

class AMYWeapon;
class UAbilitySystemComponent;
class AMYCharacterBase;
class UBoxComponent;

UCLASS()
class UE5TESTING_API AMYWeapon : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMYWeapon();

	UFUNCTION(BlueprintCallable)
	void SetGameplayEffect(const FGameplayEffectSpecHandle& InGESpecHandle);
	UFUNCTION(BlueprintCallable)
	void SetOwnerASC(class UAbilitySystemComponent* InOwnerASC);

	void Activate();
	void Deactivate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bIsClient = false;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(Server, Reliable)
	virtual void ApplyEffectToTarget_Server(class AMYCharacterBase* TargetASC);
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	class UAbilitySystemComponent* OwnerASC;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayEffectSpecHandle GESpecHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bActiveHitbox = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> HitActors;
	UPROPERTY(BlueprintReadOnly)
	class AMYWeapon* OwningWeapon;

	const TArray<AActor*>* HitActorsRef;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxCollider;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
