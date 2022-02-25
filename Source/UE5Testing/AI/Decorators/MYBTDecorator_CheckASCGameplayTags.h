// Troy Records Jr. 2021

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_CheckGameplayTagsOnActor.h"

#include "MYBTDecorator_CheckASCGameplayTags.generated.h"

/**
 * 
 */
UCLASS()
class UE5TESTING_API UMYBTDecorator_CheckASCGameplayTags : public UBTDecorator_CheckGameplayTagsOnActor
{
public:
    GENERATED_BODY()

	UMYBTDecorator_CheckASCGameplayTags();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
