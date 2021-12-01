// Troy Records Jr. 2021


#include "MYSurvivalGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "UE5Testing/Actors/MYEnemySpawnPoint.h"
#include "UE5Testing/Characters/MYCharacterBase.h"

void AMYSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TempActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMYEnemySpawnPoint::StaticClass(), TempActors);
	if(EnemyClass == nullptr)
		return;
	for(AActor* Actor : TempActors)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor<AMYCharacterBase>(EnemyClass,Actor->GetActorLocation(),Actor->GetActorRotation(), SpawnParameters);
		UE_LOG(LogTemp, Warning, TEXT("spawning"));
	}
}
