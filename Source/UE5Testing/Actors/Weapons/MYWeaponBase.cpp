// Troy Records Jr. 2021


#include "MYWeaponBase.h"

#include "Net/UnrealNetwork.h"
#include "UE5Testing/AbilitySystem/MYAbilitySystemComponent.h"
#include "UE5Testing/Actors/Weapons/MYWeaponActor.h"
#include "UE5Testing/Characters/MYCharacterBase.h"
#include "UE5Testing/DataAssets/MYWeaponSMADA.h"
#include "UE5Testing/DataTypes/MYWeaponData.h"


// Sets default values
AMYWeaponBase::AMYWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

UMYAbilityDataAsset* AMYWeaponBase::GetAbilityDataAsset() const
{
	check(ItemData);
	return ItemData->PrimaryAbilityDataAsset;
}

UMYAbilityDataAsset* AMYWeaponBase::GetPrimaryAbilityAsset() const
{
	check(ItemData);
	return ItemData->PrimaryAbilityDataAsset;
}

void AMYWeaponBase::SetGameplayEffect(const FGameplayEffectSpecHandle& InGESpecHandle)
{
	GESpecHandle = InGESpecHandle;
}

void AMYWeaponBase::SetOwnerASC(UAbilitySystemComponent* InOwnerASC)
{
	check(InOwnerASC);
	if (InOwnerASC == nullptr)
	{
		UE_LOG(LogAbilitySystem, Warning, TEXT("%s was called with a null ASC on %s"), *FString(__FUNCTION__),
		       *GetName());
		return;
	}
	OwnerASC = InOwnerASC;
}

void AMYWeaponBase::HitCharacter(AMYCharacterBase* TargetCharacter)
{
	ApplyEffectToTarget_Server(TargetCharacter);
}

void AMYWeaponBase::SetOwningCharacter(AMYCharacterBase* InOwningCharacter)
{
	OwningCharacter = InOwningCharacter;
}

void AMYWeaponBase::Initialize()
{
	SpawnWeaponActors();
}

void AMYWeaponBase::Deactivate()
{
	check(RightHandWeapon);
	check(LeftHandWeapon);
	RightHandWeapon->Destroy();
	LeftHandWeapon->Destroy();
	Destroy();
}

void AMYWeaponBase::ActivateRightHandWeapon()
{
	check(RightHandWeapon);
	RightHandWeapon->Activate();
}

void AMYWeaponBase::ActivateLeftHandWeapon()
{
	check(LeftHandWeapon);
	LeftHandWeapon->Activate();
}

void AMYWeaponBase::DeactivateRightHandWeapon()
{
	check(RightHandWeapon);
	RightHandWeapon->Deactivate();
}

void AMYWeaponBase::DeactivateLeftHandWeapon()
{
	check(LeftHandWeapon);
	LeftHandWeapon->Deactivate();
}

void AMYWeaponBase::SpawnWeaponActors()
{
	check(OwningCharacter);
	const UMYWeaponData* WeaponData = Cast<UMYWeaponData>(ItemData);
	check(WeaponData);
	UWorld* World = GetWorld();
	if (World == nullptr) return;
	if (WeaponData->RHWeaponClass != nullptr)
	{
		RightHandWeapon = World->SpawnActor<AMYWeaponActor>(WeaponData->RHWeaponClass);
		check(RightHandWeapon);
		
		RightHandWeapon->AttachToComponent(OwningCharacter->GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, OwningCharacter->RightSocketName);
		RightHandWeapon->SetOwningWeapon(this);
		RightHandWeapon->SetActorArrayPtr(&HitActors);
		if (WeaponData->WeaponSMADA != nullptr)
			RightHandWeapon->GetStaticMeshComponent()->SetStaticMesh(WeaponData->WeaponSMADA->GetPrimaryStaticMesh());
	}
	if (WeaponData->LHWeaponClass != nullptr)
	{
		LeftHandWeapon = World->SpawnActor<AMYWeaponActor>(WeaponData->LHWeaponClass);
		check(LeftHandWeapon);
		
		LeftHandWeapon->AttachToComponent(OwningCharacter->GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, OwningCharacter->LeftSocketName);
		LeftHandWeapon->SetOwningWeapon(this);
		LeftHandWeapon->SetActorArrayPtr(&HitActors);
		if (WeaponData->WeaponSMADA != nullptr)
			LeftHandWeapon->GetStaticMeshComponent()->SetStaticMesh(WeaponData->WeaponSMADA->GetSecondaryStaticMesh());
	}
}

void AMYWeaponBase::ApplyEffectToTarget_Server_Implementation(AMYCharacterBase* TargetCharacter)
{
	if (ensureAlways(TargetCharacter) && ensureAlways(OwnerASC))
	{
		OwnerASC->ApplyGameplayEffectSpecToTarget(*GESpecHandle.Data.Get(),
		                                          TargetCharacter->GetAbilitySystemComponent());
	}
}

void AMYWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMYWeaponBase, OwnerASC);
}
