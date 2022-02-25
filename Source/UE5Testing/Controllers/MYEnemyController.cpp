// Troy Records Jr. 2021


#include "MYEnemyController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "UE5Testing/Characters/MYCharacterBase.h"
#include "UE5Testing/GameStates/MYSurvivalGameState.h"

DEFINE_LOG_CATEGORY(LogAI);


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
}



void AMYEnemyController::ActivatePrimaryAbility() const
{
	if(IsValid(BaseCharacter))
		BaseCharacter->ActivatePrimaryAbility();
}

void AMYEnemyController::OnPossess(APawn* InPawn)
{
	BaseCharacter = Cast<AMYCharacterBase>(InPawn);
	if(BaseCharacter == nullptr)
	{
		UE_LOG(LogAI, Error, TEXT("%s is trying to possess a pawn that is not of AMYCharacterBase!"), *GetName());
		return;
	}
	Super::OnPossess(InPawn);
	if(AIBehaviorTree)
	{
		RunBehaviorTree(AIBehaviorTree);
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

