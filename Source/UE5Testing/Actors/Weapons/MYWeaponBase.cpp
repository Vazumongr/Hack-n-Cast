// Troy Records Jr. 2021


#include "MYWeaponBase.h"

#include "Net/UnrealNetwork.h"
#include "UE5Testing/AbilitySystem/MYAbilitySystemComponent.h"
#include "UE5Testing/Actors/Weapons/MYWeapon.h"
#include "UE5Testing/Characters/MYCharacterBase.h"
#include "UE5Testing/DataAssets/MYWeaponSMADA.h"


// Sets default values
AMYWeaponBase::AMYWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMYWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	check(World);
	//SpawnWeapons();
	//RightHandWeapon = World->SpawnActor<AMYWeapon>(AMYWeapon::StaticClass());
	//LeftHandWeapon = World->SpawnActor<AMYWeapon>(AMYWeapon::StaticClass());
}

void AMYWeaponBase::SetGameplayEffect(const FGameplayEffectSpecHandle& InGESpecHandle)
{
	GESpecHandle = InGESpecHandle;
}

void AMYWeaponBase::SetOwnerASC(UAbilitySystemComponent* InOwnerASC)
{
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
	SpawnWeapons();
}

void AMYWeaponBase::Deactivate()
{
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

void AMYWeaponBase::SpawnWeapons()
{
	check(OwningCharacter);
	UWorld* World = GetWorld();
	if (World == nullptr) return;
	if (RHWeaponClass != nullptr)
	{
		RightHandWeapon = World->SpawnActor<AMYWeapon>(RHWeaponClass);
		check(RightHandWeapon);
		
		RightHandWeapon->AttachToComponent(OwningCharacter->GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, OwningCharacter->RightSocketName);
		RightHandWeapon->SetOwningWeapon(this);
		RightHandWeapon->SetActorArrayPtr(&HitActors);
		if (WeaponSMADA != nullptr)
			RightHandWeapon->GetStaticMeshComponent()->SetStaticMesh(WeaponSMADA->GetPrimaryStaticMesh());
	}
	if (LHWeaponClass != nullptr)
	{
		LeftHandWeapon = World->SpawnActor<AMYWeapon>(LHWeaponClass);
		check(LeftHandWeapon);
		
		LeftHandWeapon->AttachToComponent(OwningCharacter->GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, OwningCharacter->LeftSocketName);
		LeftHandWeapon->SetOwningWeapon(this);
		LeftHandWeapon->SetActorArrayPtr(&HitActors);
		if (WeaponSMADA != nullptr)
			LeftHandWeapon->GetStaticMeshComponent()->SetStaticMesh(WeaponSMADA->GetSecondaryStaticMesh());
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

// Called every frame
void AMYWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMYWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMYWeaponBase, OwnerASC);
}
