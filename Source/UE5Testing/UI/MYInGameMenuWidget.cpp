// Troy Records Jr.


#include "MYInGameMenuWidget.h"
#include "UE5Testing/UE5Testing.h"
#include "Components/Button.h"
#include "UE5Testing/Interfaces/MYMainMenuInterface.h"

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
	if(!ensure(MainMenuInterface)) return;
	MainMenuInterface->QuitToMainMenu();
}

void UMYInGameMenuWidget::Cancel()
{
	Teardown();
}
