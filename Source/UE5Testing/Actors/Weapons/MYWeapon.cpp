// Troy Records Jr. 2021


#include "MYWeapon.h"

#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "UE5Testing/Characters/MYCharacterBase.h"
#include "UE5Testing/UE5Testing.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AMYWeapon::AMYWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(RootComponent);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMYWeapon::OnBeginOverlap);
	BoxCollider->SetGenerateOverlapEvents(false);
}

void AMYWeapon::SetGameplayEffect(const FGameplayEffectSpecHandle& InGESpecHandle)
{
	GESpecHandle = InGESpecHandle;
}

void AMYWeapon::SetOwnerASC(UAbilitySystemComponent* InOwnerASC)
{
	if(InOwnerASC == nullptr)
	{
		UE_LOG(LogAbilitySystem, Warning, TEXT("%s was called with a null ASC on %s"), *FString(__FUNCTION__), *GetName());
		return;
	}
	OwnerASC = InOwnerASC;
}

void AMYWeapon::Activate()
{
	BoxCollider->SetGenerateOverlapEvents(true);
	HitActors.Empty();
}

void AMYWeapon::Deactivate()
{
	BoxCollider->SetGenerateOverlapEvents(false);
	HitActors.Empty();
}

void AMYWeapon::BeginPlay()
{
	Super::BeginPlay();
	if(GetNetMode() == NM_Client) bIsClient = true;
	if(GetNetMode() == NM_DedicatedServer) bIsClient = false;

}

void AMYWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if(GetNetMode() == NM_DedicatedServer) return;
	if(!IsValid(OtherActor) || OtherActor==GetOwner()) return;
	
	if(OtherComponent!=nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapping: %s"), *OtherComponent->GetName());
		if(!OtherComponent->IsA(UCapsuleComponent::StaticClass())) return;
	}
	
	if(HitActors.Contains(OtherActor)) return;
	HitActors.Add(OtherActor);
	
	AMYCharacterBase* CharacterHit = Cast<AMYCharacterBase>(OtherActor);
	if(!IsValid(CharacterHit)) return;
	if(CharacterHit->bIsReady)
	{
		UKismetSystemLibrary::PrintString(this, TEXT("Applying effect!"));
		ApplyEffectToTarget_Server(CharacterHit);
	}
}

void AMYWeapon::ApplyEffectToTarget_Server_Implementation(AMYCharacterBase* TargetCharacter)
{
	if(ensureAlways(TargetCharacter) && ensureAlways(OwnerASC))
	{
		OwnerASC->ApplyGameplayEffectSpecToTarget(*GESpecHandle.Data.Get(),TargetCharacter->GetAbilitySystemComponent());
	}
}

void AMYWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMYWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMYWeapon, OwnerASC);
}