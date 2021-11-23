// Troy Records Jr. 2021
#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"

#include "MYOverheadHealthBar.generated.h"

UCLASS()
/**
 * Class for overhead health bars
 */
class UE5TESTING_API UMYOverheadHealthBar : public UWidgetComponent
{
    GENERATED_BODY()
	UMYOverheadHealthBar();
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	virtual void InitWidget() override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class APlayerController* PlayerController;
private:
};
