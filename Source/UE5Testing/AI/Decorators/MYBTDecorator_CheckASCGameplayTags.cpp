// Troy Records Jr. 2021


#include "MYBTDecorator_CheckASCGameplayTags.h"

#include "AbilitySystemInterface.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UE5Testing/AbilitySystem/MYAbilitySystemComponent.h"

UMYBTDecorator_CheckASCGameplayTags::UMYBTDecorator_CheckASCGameplayTags()
{
	NodeName = "ASCGameplay Tag Condition";
}

bool UMYBTDecorator_CheckASCGameplayTags::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                                     uint8* NodeMemory) const
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == nullptr)
	{
		return false;
	}

	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(ActorToCheck.GetSelectedKeyID()));
	if (AbilitySystemInterface == nullptr)
	{
		return false;
	}

	UAbilitySystemComponent* ASC = AbilitySystemInterface->GetAbilitySystemComponent();
	if(ASC == nullptr)
	{
		return false;
	}
	
	switch (TagsToMatch)
	{
		case EGameplayContainerMatchType::All:
			return ASC->HasAllMatchingGameplayTags(GameplayTags);

		case EGameplayContainerMatchType::Any:
			return ASC->HasAnyMatchingGameplayTags(GameplayTags);

		default:
			{
				UE_LOG(LogBehaviorTree, Warning, TEXT("Invalid value for TagsToMatch (EGameplayContainerMatchType) %d.  Should only be Any or All."), static_cast<int32>(TagsToMatch));
				return false;
			}
	}
}
