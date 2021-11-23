// Troy Records Jr. 2021
#include "MYPlayerCharacter.h"

#include "Components/SphereComponent.h"
#include "UE5Testing/Loot/MYDroppedLootBase.h"

AMYPlayerCharacter::AMYPlayerCharacter()
{
	LootPickerUpper = CreateDefaultSubobject<USphereComponent>("LootPickerUpper");
	LootPickerUpper->SetupAttachment(GetMesh());
	LootPickerUpper->OnComponentBeginOverlap.AddDynamic(this, &AMYPlayerCharacter::LootPickUp);
}

void AMYPlayerCharacter::AddControllerPitchInput(float Val)
{
	Super::AddControllerPitchInput(Val * MouseSensitivity);
}

void AMYPlayerCharacter::AddControllerYawInput(float Val)
{
	Super::AddControllerYawInput(Val * MouseSensitivity);
}

void AMYPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("PrimaryAbility", IE_Pressed, this, &AMYPlayerCharacter::PrimaryAttack);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMYPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMYPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

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
	ActivateAbilityByHandle(PrimaryAbilityHandle);
	if(++AttackChainCounter>3) AttackChainCounter = 0;
}

void AMYPlayerCharacter::LootPickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMYDroppedLootBase* Loot = Cast<AMYDroppedLootBase>(OtherActor);
	if(Loot != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pickup"));
		Loot->ProximityPickUp(this);
	}
}
