// Troy Records Jr. 2021


#include "MYSurvivalGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "UE5Testing/Actors/MYEnemySpawnPoint.h"
#include "UE5Testing/Characters/MYCharacterBase.h"

void AMYSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AMYSurvivalGameMode::SpawnDrops()
{
	TArray<AActor*> LootSpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMYEnemySpawnPoint::StaticClass(), LootSpawnPoints);
	TArray<AActor*> TempActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMYCharacterBase::StaticClass(), TempActors);
	if(EnemyClass == nullptr)
		return;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	
	uint8 Counter{0};
	
	for(AActor* Actor : LootSpawnPoints)
    {
		if(Counter<TempActors.Num())
			SpawnParameters.Owner = TempActors[Counter];
		else
			SpawnParameters.Owner = TempActors[0];
    	GetWorld()->SpawnActor<AActor>(EnemyClass,Actor->GetActorLocation(),Actor->GetActorRotation(), SpawnParameters);
    	UE_LOG(LogTemp, Warning, TEXT("spawning"));
		Counter++;
    }
}
