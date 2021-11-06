// Copyright Troy Records Jr. 2021


#include "UE5Testing/AbilitySystem/MYAsyncTaskAttributeChanged.h"

UMYAsyncTaskAttributeChanged* UMYAsyncTaskAttributeChanged::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	UMYAsyncTaskAttributeChanged* WaitForAttributeChangedTask = NewObject<UMYAsyncTaskAttributeChanged>();
	WaitForAttributeChangedTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributeToListenFor = Attribute;

	if (!IsValid(AbilitySystemComponent) || !Attribute.IsValid())
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UMYAsyncTaskAttributeChanged::AttributeChanged);

	return WaitForAttributeChangedTask;
}

UMYAsyncTaskAttributeChanged * UMYAsyncTaskAttributeChanged::ListenForAttributesChange(UAbilitySystemComponent * AbilitySystemComponent, TArray<FGameplayAttribute> Attributes)
{
	UMYAsyncTaskAttributeChanged* WaitForAttributeChangedTask = NewObject<UMYAsyncTaskAttributeChanged>();
	WaitForAttributeChangedTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributesToListenFor = Attributes;

	if (!IsValid(AbilitySystemComponent) || Attributes.Num() < 1)
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	for (FGameplayAttribute Attribute : Attributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UMYAsyncTaskAttributeChanged::AttributeChanged);
	}

	return WaitForAttributeChangedTask;
}

void UMYAsyncTaskAttributeChanged::EndTask()
{
	if (IsValid(ASC))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);

		for (FGameplayAttribute Attribute : AttributesToListenFor)
		{
			ASC->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);
		}
	}

	SetReadyToDestroy();
	MarkPendingKill();
}

void UMYAsyncTaskAttributeChanged::AttributeChanged(const FOnAttributeChangeData & Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}