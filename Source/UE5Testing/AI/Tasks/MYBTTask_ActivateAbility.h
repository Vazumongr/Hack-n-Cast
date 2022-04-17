// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MYBTTask_ActivateAbility.generated.h"

class UBehaviorTree;

UCLASS()
class UE5TESTING_API UMYBTTask_ActivateAbility : public UBTTaskNode
{
	GENERATED_BODY()

	UMYBTTask_ActivateAbility();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/*
#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif // WITH_EDITOR
	*/
};
