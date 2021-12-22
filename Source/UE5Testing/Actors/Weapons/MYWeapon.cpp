// Troy Records Jr. 2021


#include "MYWeapon.h"

#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "UE5Testing/Characters/MYCharacterBase.h"
#include "Engine.h"


// Sets default values
AMYWeapon::AMYWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(RootComponent);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMYWeapon::OnBeginOverlap);
	
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
	bActiveHitbox = true;
	HitActors.Empty();
}

void AMYWeapon::Deactivate()
{
	bActiveHitbox = false;
	HitActors.Empty();
}

// Called when the game starts or when spawned
void AMYWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMYWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if(!bActiveHitbox) return;
	if(OtherActor==GetOwner()) return;
	if(HitActors.Contains(OtherActor)) return;
	HitActors.Add(OtherActor);
	AMYCharacterBase* CharacterHit = Cast<AMYCharacterBase>(OtherActor);
	if(CharacterHit == nullptr) return;
	if(OwnerASC == nullptr)
	{
		UE_LOG(LogAbilitySystem, Warning, TEXT("%s was called with a null ASC on %s"), *FString(__FUNCTION__), *GetName());
		return;
	}
	OwnerASC->ApplyGameplayEffectSpecToTarget(*GESpecHandle.Data.Get(),CharacterHit->GetAbilitySystemComponent());
}

// Called every frame
void AMYWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

