// Troy Records Jr. 2021
#include "MYPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "UE5Testing/AbilitySystem/MYAbilitySystemComponent.h"
#include "UE5Testing/Actors/MYVendor.h"
#include "UE5Testing/Actors/Weapons/MYWeaponBase.h"
#include "UE5Testing/Controllers/MYPlayerController.h"
#include "UE5Testing/Loot/MYDroppedLootBase.h"
#include "UE5Testing/DataAssets/MYStartingKitBaseDA.h"
#include "UE5Testing/FileWritingTest/MYFileIO.h"

AMYPlayerCharacter::AMYPlayerCharacter()
{
	LootPickerUpper = CreateDefaultSubobject<USphereComponent>("LootPickerUpper");
	LootPickerUpper->SetupAttachment(GetMesh());
	LootPickerUpper->OnComponentBeginOverlap.AddDynamic(this, &AMYPlayerCharacter::LootPickUp);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraBoom);
}

void AMYPlayerCharacter::AddControllerPitchInput(float Val)
{
	Super::AddControllerPitchInput(Val * MouseSensitivity);
}

void AMYPlayerCharacter::AddControllerYawInput(float Val)
{
	Super::AddControllerYawInput(Val * MouseSensitivity);
}

void AMYPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMYPlayerCharacter, AttackChainCounter);
}

void AMYPlayerCharacter::ApplyBuff_Implementation(TSubclassOf<UGameplayEffect> InGE)
{
	UE_LOG(LogTemp, Warning, TEXT("Buffed"));
	check(AbilitySystemComponent);
	if(!InGE) return;
	UGameplayEffect* GameplayEffect = InGE->GetDefaultObject<UGameplayEffect>();
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	AbilitySystemComponent->ApplyGameplayEffectToSelf(GameplayEffect, 0, EffectContext);
}

void AMYPlayerCharacter::ApplyBuff_Server_Implementation(TSubclassOf<UGameplayEffect> InGE)
{
	ApplyBuff(InGE);
}

void AMYPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("PrimaryAbility", IE_Pressed, this, &AMYPlayerCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("SelectFirstWeapon", IE_Pressed, this, &AMYPlayerCharacter::SelectFirstWeapon);
	PlayerInputComponent->BindAction("SelectSecondWeapon", IE_Pressed, this, &AMYPlayerCharacter::SelectSecondWeapon);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMYPlayerCharacter::Interact);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AMYPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMYPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AMYPlayerCharacter::Destroyed()
{
	AMYPlayerController* PlayerController = Cast<AMYPlayerController>(GetController());
	if(PlayerController)
		PlayerController->PawnDied();
	
	Super::Destroyed();
}

void AMYPlayerCharacter::DownedTagAddedOrRemoved(const FGameplayTag CallbackTag, int32 NewCount)
{
	//FGameplayTagContainer TagContainer;
	//TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Downed")));
	//AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
	Super::DownedTagAddedOrRemoved(CallbackTag, NewCount);
}

void AMYPlayerCharacter::HealthChanged(const FOnAttributeChangeData & Data)
{
	Super::HealthChanged(Data);
}

void AMYPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMYPlayerCharacter::SelectFirstWeapon()
{
	SpawnWeaponsOnServer_Server(0);
}

void AMYPlayerCharacter::SelectSecondWeapon()
{
	SpawnWeaponsOnServer_Server(1);
}

/*
void AMYPlayerCharacter::SpawnWeapon(int8 WeaponIdx)
{
	if (WeaponClass != nullptr)
	{
		Weapon->Deactivate();
		Weapon = nullptr;
		check(InventoryComponent);
		Weapon = GetWorld()->SpawnActor<AMYWeaponBase>(AMYWeaponBase::StaticClass());
		check(Weapon);
		Weapon->SetOwningCharacter(this);
		Weapon->SetOwnerASC(AbilitySystemComponent);
		Weapon->SetItemData(InventoryComponent->GetItemDataAtIndex(WeaponIdx));
		Weapon->Initialize();

		if(HasAuthority())
		{
			UMYAbilityDataAsset* ADA = Weapon->GetPrimaryAbilityAsset();
			check(ADA);
			FGameplayAbilitySpec AbilitySpec;
			AbilitySpec = FGameplayAbilitySpec(ADA->Ability, 1, INDEX_NONE, this);
			PrimaryAbilityHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
}
*/

void AMYPlayerCharacter::MoveForward(float InValue)
{
	if ((Controller != nullptr) && (InValue != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, InValue * MovementSpeed);
	}
}

void AMYPlayerCharacter::MoveRight(float InValue)
{
	if ( (Controller != nullptr) && (InValue != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, InValue * MovementSpeed);
	}
}

void AMYPlayerCharacter::PrimaryAttack()
{
	//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("PrimaryAttack: %f"), AttackChainCounter));
	ActivateAbilityByHandle(PrimaryAbilityHandle);
}

void AMYPlayerCharacter::MyCrouch()
{
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green,FString::Printf(TEXT("Crouch! Time: %i"), FDateTime::Now().GetMillisecond()));
	UE_LOG(LogTemp, Warning, TEXT("Crouch! Time: %i"), FDateTime::Now().GetMillisecond());
}

void AMYPlayerCharacter::Interact()
{
	TArray<FOverlapResult> OverlapResults;
	const FVector Position = GetActorLocation();
	const FQuat Rotation = FQuat::Identity;
	FCollisionShape Shape = FCollisionShape::MakeBox(InteractShapeSize);
	if(GetWorld()->OverlapMultiByChannel(OverlapResults, Position, Rotation, ECC_Camera, Shape))
	{
		for(const FOverlapResult& Result : OverlapResults)
		{
			if(AMYVendor* Vendor = Cast<AMYVendor>(Result.GetActor()))
			{
				Vendor->Interact(this);
			}
		}
	}
}

void AMYPlayerCharacter::SetStartingKit_Server_Implementation(UMYStartingKitBaseDA* InStartingKit)
{
	if(!ensureAlways(AbilitySystemComponent) && !ensureAlways(InStartingKit)) return;

	if(PrimaryAbilityHandle.IsValid())
		AbilitySystemComponent->ClearAbility(PrimaryAbilityHandle);
	if(SecondaryAbilityHandle.IsValid())
		AbilitySystemComponent->ClearAbility(SecondaryAbilityHandle);

	PrimaryAbilityHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(InStartingKit->GetAttackAbility()));
	SecondaryAbilityHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(InStartingKit->GetSpellAbility()));
}

void AMYPlayerCharacter::SetStartingKit(UMYStartingKitBaseDA* InStartingKit)
{
	SetStartingKit_Server(InStartingKit);
}

void AMYPlayerCharacter::LootPickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMYDroppedLootBase* Loot = Cast<AMYDroppedLootBase>(OtherActor);
	if(Loot != nullptr)
	{
		if(Loot->GetOwner() == this)
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup"));
			Loot->ProximityPickUp(this);
		}
	}
}
