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
	//UE_LOG(LogTemp, Error, TEXT("Setting up GE"));
	//UKismetSystemLibrary::PrintString(this, TEXT("Setting up GE!"));
	GESpecHandle = InGESpecHandle;
}

void AMYWeapon::SetOwnerASC(UAbilitySystemComponent* InOwnerASC)
{
	if(InOwnerASC == nullptr)
	{
		UE_LOG(LogAbilitySystem, Warning, TEXT("%s was called with a null ASC on %s"), *FString(__FUNCTION__), *GetName());
		return;
	}
	//UE_LOG(LogTemp, Error, TEXT("Setting up ASC"));
	//UKismetSystemLibrary::PrintString(this, TEXT("Setting up ASC!"));
	OwnerASC = InOwnerASC;
}

void AMYWeapon::Activate()
{
	//UE_LOG(LogTemp, Error, TEXT("Activating!"));
	//UKismetSystemLibrary::PrintString(this, TEXT("Weapon is Activating!"));
	BoxCollider->SetGenerateOverlapEvents(true);
	HitActors.Empty();
}

void AMYWeapon::Deactivate()
{
	//UE_LOG(LogTemp, Error, TEXT("Deactivating!!"));
	//UKismetSystemLibrary::PrintString(this, TEXT("Deactivating!"));
	BoxCollider->SetGenerateOverlapEvents(false);
	HitActors.Empty();
}

// Called when the game starts or when spawned
void AMYWeapon::BeginPlay()
{
	Super::BeginPlay();
	if(GetNetMode() == NM_Client) bIsClient = true;
	if(GetNetMode() == NM_DedicatedServer) bIsClient = false;

}

void AMYWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	//UKismetSystemLibrary::PrintString(this, TEXT("Overlapped!"));
	if(GetNetMode() == NM_DedicatedServer) return;
	if(!IsValid(OtherActor) || OtherActor==GetOwner()) return;
	//if(OtherActor == nullptr || OtherActor==GetOwner()) return;
	if(HitActors.Contains(OtherActor)) return;
	HitActors.Add(OtherActor);
	AMYCharacterBase* CharacterHit = Cast<AMYCharacterBase>(OtherActor);
	if(!IsValid(CharacterHit)) return;
	//if(CharacterHit == nullptr) return;
	// if(!IsValid(OwnerASC))
	// {
	// 	UE_LOG(LogAbilitySystem, Warning, TEXT("%s was called with a null ASC on %s"), *FString(__FUNCTION__), *GetName());
	// 	return;
	// }
	if(CharacterHit->bIsReady)
	{
		//UE_LOG(LogTemp, Error, TEXT("Applying effect"));
		UKismetSystemLibrary::PrintString(this, TEXT("Applying effect!"));
		ApplyEffectToTarget_Server(CharacterHit);
		//OwnerASC->ApplyGameplayEffectSpecToTarget(*GESpecHandle.Data.Get(),CharacterHit->GetAbilitySystemComponent());
	}
	//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Weapon hit %s"), *CharacterHit->GetName()));
}

void AMYWeapon::ApplyEffectToTarget_Server_Implementation(AMYCharacterBase* TargetCharacter)
{
	if(ensureAlways(TargetCharacter) && ensureAlways(OwnerASC))
	{
		OwnerASC->ApplyGameplayEffectSpecToTarget(*GESpecHandle.Data.Get(),TargetCharacter->GetAbilitySystemComponent());
	}
}

// Called every frame
void AMYWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMYWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMYWeapon, OwnerASC);
}