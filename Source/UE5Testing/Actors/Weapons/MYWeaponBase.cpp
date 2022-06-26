// Troy Records Jr. 2021


#include "MYWeaponBase.h"

#include "Kismet/GameplayStatics.h"
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
	bReplicates = true;
	bAlwaysRelevant = true;
}

void AMYWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	if(HasAuthority())
	{
		SpawnWeaponActors();
	}
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

void AMYWeaponBase::HitCharacter(AMYCharacterBase* TargetCharacter)
{
	ApplyEffectToTarget_Server(TargetCharacter);
}

void AMYWeaponBase::AddHitActor(AActor* InHitActor)
{
	if(!IsValid(InHitActor))
	{
		UE_LOG(LogCollision, Error, TEXT("A nullptr was passed into %s on %s!"), *FString(__FUNCTION__), *GetName());
		return;
	}
	HitActors.Add(InHitActor);
	checkf(true, TEXT("Look at me compile!"))
}

bool AMYWeaponBase::HasHitActor(AActor* InHitActor) const
{
	return HitActors.Contains(InHitActor);
}

void AMYWeaponBase::ClearHitActors()
{
	HitActors.Empty();
}

void AMYWeaponBase::Deactivate()
{
	check(RightHandWeapon);
	check(LeftHandWeapon);
	RightHandWeapon->Destroy();
	LeftHandWeapon->Destroy();
	Destroy();
}

/* Delayed super call because super calls Destroy() */
void AMYWeaponBase::Deconstruct()
{
	RightHandWeapon->Destroy();
	LeftHandWeapon->Destroy();
	Super::Deconstruct();
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
		RightHandWeapon = World->SpawnActorDeferred<AMYWeaponActor>(WeaponData->RHWeaponClass, FTransform::Identity);
		check(RightHandWeapon);
		
		RightHandWeapon->AttachToComponent(OwningCharacter->GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, OwningCharacter->RightSocketName);
		RightHandWeapon->SetOwningWeapon(this);
		RightHandWeapon->SetReplicates(true);

		bool bFirstCheck = (GetNetMode() == NM_Client && OwningCharacter->GetLocalRole() == ROLE_AutonomousProxy);
		bool bSecondCheck = (GetNetMode() == NM_ListenServer && OwningCharacter->GetRemoteRole() == ROLE_SimulatedProxy);
		bool bThirdCheck = (GetNetMode() == NM_Standalone);

		ENetRole OwnerRole = OwningCharacter->GetLocalRole();

		if((GetNetMode() == NM_Client && OwningCharacter->GetLocalRole() == ROLE_AutonomousProxy) || (GetNetMode() == NM_ListenServer && OwningCharacter->GetRemoteRole() == ROLE_SimulatedProxy) || (GetNetMode() == NM_Standalone))
		{
			RightHandWeapon->bShouldDetect = true;
		}
		
		UGameplayStatics::FinishSpawningActor(RightHandWeapon, FTransform::Identity);
		if (WeaponData->WeaponSMADA != nullptr)
			RightHandWeapon->GetStaticMeshComponent()->SetStaticMesh(WeaponData->WeaponSMADA->GetPrimaryStaticMesh());
	}
	
	if (WeaponData->LHWeaponClass != nullptr)
	{
		LeftHandWeapon = World->SpawnActorDeferred<AMYWeaponActor>(WeaponData->LHWeaponClass, FTransform::Identity);
		check(LeftHandWeapon);
		
		LeftHandWeapon->AttachToComponent(OwningCharacter->GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, OwningCharacter->LeftSocketName);
		LeftHandWeapon->SetOwningWeapon(this);
		LeftHandWeapon->SetReplicates(true);

		if((GetNetMode() == NM_Client && OwningCharacter->GetLocalRole() == ROLE_AutonomousProxy) || (GetNetMode() == NM_ListenServer && OwningCharacter->GetRemoteRole() == ROLE_SimulatedProxy) || (GetNetMode() == NM_Standalone))
		{
			LeftHandWeapon->bShouldDetect = true;
		}
		
		UGameplayStatics::FinishSpawningActor(LeftHandWeapon, FTransform::Identity);
		if (WeaponData->WeaponSMADA != nullptr)
			LeftHandWeapon->GetStaticMeshComponent()->SetStaticMesh(WeaponData->WeaponSMADA->GetSecondaryStaticMesh());
	}
}

void AMYWeaponBase::SpawnWeaponActors_Multicast_Implementation()
{
	SpawnWeaponActors();
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
	DOREPLIFETIME(AMYWeaponBase, RightHandWeapon);
	DOREPLIFETIME(AMYWeaponBase, LeftHandWeapon);
}
