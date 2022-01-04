// Troy Records Jr. 2021


#include "MYSurvivalGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "UE5Testing/Actors/MYEnemySpawnPoint.h"
#include "UE5Testing/Characters/MYCharacterBase.h"

void AMYSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle EnemySpawnTimer;
	GetWorldTimerManager().SetTimer(EnemySpawnTimer,this,&AMYSurvivalGameMode::SpawnEnemy,3.f,true);
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

void AMYSurvivalGameMode::SpawnEnemy()
{
	TArray<AActor*> LootSpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMYEnemySpawnPoint::StaticClass(), LootSpawnPoints);
	AActor* Actor = LootSpawnPoints[FMath::RandRange(0,2)];
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	GetWorld()->SpawnActor<AActor>(EnemyClass,Actor->GetActorLocation(),Actor->GetActorRotation(), SpawnParameters);
}
