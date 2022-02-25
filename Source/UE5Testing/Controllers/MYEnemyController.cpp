// Troy Records Jr. 2021


#include "MYEnemyController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "UE5Testing/Characters/MYCharacterBase.h"
#include "UE5Testing/GameStates/MYSurvivalGameState.h"


// Sets default values
AMYEnemyController::AMYEnemyController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMYEnemyController::BeginPlay()
{
	Super::BeginPlay();
	AMYSurvivalGameState* GameState = Cast<AMYSurvivalGameState>(GetWorld()->GetGameState());
	check(GameState)
	GameState->GameOverDelegate.AddUObject(this, &AMYEnemyController::GameOver);
	
	if(AIBehaviorTree)
	{
		RunBehaviorTree(AIBehaviorTree);
	}

	BaseCharacter = Cast<AMYCharacterBase>(GetPawn());
	if(BaseCharacter)
	{
		BaseCharacter->ActivatePrimaryAbility();
	}
		
}

void AMYEnemyController::GameOver()
{
	if(GetNetMode() == NM_DedicatedServer)
	{
		GameOver_DedicatedServer();
		return;
	}
}

void AMYEnemyController::GameOver_DedicatedServer()
{
	
}

// Called every frame
void AMYEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

