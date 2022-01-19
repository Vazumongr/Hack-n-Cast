// Troy Records Jr. 2021


#include "MYItemBase.h"


// Sets default values
AMYItemBase::AMYItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMYItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMYItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

