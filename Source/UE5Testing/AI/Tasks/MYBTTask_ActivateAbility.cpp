// Troy Records Jr. 2021

#include "MYBTTask_ActivateAbility.h"

#include "UE5Testing/Controllers/MYEnemyController.h"


UMYBTTask_ActivateAbility::UMYBTTask_ActivateAbility()
{
	NodeName=TEXT("ActivatePrimaryAbility");
}
/*
FName UMYBTTask_ActivateAbility::GetNodeIconName() const
{
	return Super::GetNodeIconName();
}
*/
EBTNodeResult::Type UMYBTTask_ActivateAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AMYEnemyController* EnemyController = Cast<AMYEnemyController>(OwnerComp.GetOwner());
	if(EnemyController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	EnemyController->ActivatePrimaryAbility();
	return EBTNodeResult::Succeeded;
}
