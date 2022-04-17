// Troy Records Jr. 2021


#include "MYWeaponActor.h"

#include "MYWeaponBase.h"
#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "UE5Testing/Characters/MYCharacterBase.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AMYWeaponActor::AMYWeaponActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(RootComponent);
	BoxCollider->SetGenerateOverlapEvents(false);
}

void AMYWeaponActor::SetOwningWeapon(AMYWeaponBase* InOwningWeapon)
{
	OwningWeapon = InOwningWeapon;
}

void AMYWeaponActor::Activate()
{
	check(OwningWeapon);
	BoxCollider->SetGenerateOverlapEvents(true);
	OwningWeapon->ClearHitActors();
}

void AMYWeaponActor::Deactivate()
{
	check(OwningWeapon);
	BoxCollider->SetGenerateOverlapEvents(false);
	OwningWeapon->ClearHitActors();
}

void AMYWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMYWeaponActor::OnBeginOverlap);
	
	if(!IsValid(OwningWeapon)) return;
	AMYCharacterBase* OwningCharacter = OwningWeapon->GetOwningCharacter();
	
	if(!IsValid(OwningCharacter)) return;

	/*
	if( (GetNetMode() == NM_Client && OwningCharacter->GetLocalRole() == ROLE_SimulatedProxy) || ( (GetNetMode() == NM_ListenServer) || (GetNetMode() == NM_DedicatedServer) ) && !OwningCharacter->HasAutonomousProxy() )
	{
		bShouldDetect = false;
	}
	*/
}

void AMYWeaponActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	check(OwningWeapon);
	//if(GetNetMode() == NM_DedicatedServer || !bShouldDetect) return;
	if(!IsValid(OtherActor) || OtherActor==OwningWeapon->GetOwningCharacter()) return;
	
	AMYCharacterBase* OwningCharacter = OwningWeapon->GetOwningCharacter();
	if(!IsValid(OwningCharacter)) return;
	
	if((GetNetMode() == NM_Client && OwningCharacter->GetLocalRole() == ROLE_SimulatedProxy) || (((GetNetMode() == NM_ListenServer) || (GetNetMode() == NM_DedicatedServer)) && OwningCharacter->HasAutonomousProxy())) return;

	
	if(OtherComponent!=nullptr)
	{
		UE_LOG(LogCollision, Warning, TEXT("Overlapping: %s"), *OtherComponent->GetName());
		if(!OtherComponent->IsA(UCapsuleComponent::StaticClass())) return;
	}
	
	if(OwningWeapon->HasHitActor(OtherActor)) return;
	OwningWeapon->AddHitActor(OtherActor);
	
	AMYCharacterBase* CharacterHit = Cast<AMYCharacterBase>(OtherActor);
	if(!IsValid(CharacterHit)) return;
	if(CharacterHit->bIsReady)
	{
		UKismetSystemLibrary::PrintString(this, TEXT("Applying effect!"));
		OwningWeapon->HitCharacter(CharacterHit);
	}
}

void AMYWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMYWeaponActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(AMYWeaponActor, OwningWeapon, COND_InitialOnly);
}
