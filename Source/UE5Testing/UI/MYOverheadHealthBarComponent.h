// Troy Records Jr. 2021
#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"

#include "MYOverheadHealthBarComponent.generated.h"

UCLASS()
/**
 * Class for overhead health bars
 */
class UE5TESTING_API UMYOverheadHealthBarComponent : public UWidgetComponent
{
    GENERATED_BODY()
	UMYOverheadHealthBarComponent();
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	virtual void InitWidget() override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class APlayerController* PlayerController;
private:
};
