// Troy Records Jr.


#include "MYInGameMenuWidget.h"
#include "UE5Testing/UE5Testing.h"
#include "Components/Button.h"

bool UMYInGameMenuWidget::Initialize()
{
	bool bSuccess = Super::Initialize();
	if(!bSuccess) return false;
	if(!ensure(QuitButton)) return false;
	QuitButton->OnClicked.AddDynamic(this,&UMYInGameMenuWidget::Quit);
	if(!ensure(CancelButton)) return false;
	CancelButton->OnClicked.AddDynamic(this,&UMYInGameMenuWidget::Cancel);

	return true;
}

void UMYInGameMenuWidget::Quit()
{
	UE_LOG(LogUI, Warning, TEXT("Quitting"));
}

void UMYInGameMenuWidget::Cancel()
{
	Teardown();
}
