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

void AMYWeaponActor::SetActorArrayPtr(TArray<AActor*>* InHitActorsRef)
{
	
}

void AMYWeaponActor::Activate()
{
	BoxCollider->SetGenerateOverlapEvents(true);
	TArray<AActor*> HA;
	OwningWeapon->GetHitActors(HA)->Empty();
}

void AMYWeaponActor::Deactivate()
{
	BoxCollider->SetGenerateOverlapEvents(false);
	TArray<AActor*> HA;
	OwningWeapon->GetHitActors(HA);
	HA.Empty();
}

void AMYWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMYWeaponActor::OnBeginOverlap);
}

void AMYWeaponActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	check(OwningWeapon);
	if(GetNetMode() == NM_DedicatedServer) return;
	if(!IsValid(OtherActor) || OtherActor==GetOwner()) return;
	
	if(OtherComponent!=nullptr)
	{
		UE_LOG(LogCollision, Warning, TEXT("Overlapping: %s"), *OtherComponent->GetName());
		if(!OtherComponent->IsA(UCapsuleComponent::StaticClass())) return;
	}


	TArray<AActor*> HA;
	TArray<AActor*>* PTA = OwningWeapon->GetHitActors(HA);
	OwningWeapon->GetHitActors(HA);
	
	if(HA.Contains(OtherActor)) return;
	OwningWeapon->GetHitActors(HA)->Add(OtherActor);
	
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
