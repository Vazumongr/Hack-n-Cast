// Troy Records Jr.


#include "MYMainMenuWidget.h"
#include "UE5Testing/GameInstances/MYGameInstance.h"
#include "UE5Testing/Interfaces/MYMainMenuInterface.h"
#include "Components/Button.h"

bool UMYMainMenuWidget::Initialize()
{
	bool bSuccess = Super::Initialize();
	if(!bSuccess) return false;
	if(!ensure(HostButton)) return false;
	HostButton->OnClicked.AddDynamic(this,&UMYMainMenuWidget::Host);
	if(!ensure(JoinButton)) return false;
	JoinButton->OnClicked.AddDynamic(this,&UMYMainMenuWidget::Join);

	return true;
}

void UMYMainMenuWidget::SetInterface(IMYMainMenuInterface* InMainMenuInterface)
{
	if(!ensure(InMainMenuInterface)) return;
	MainMenuInterface = InMainMenuInterface;
}

void UMYMainMenuWidget::Host()
{
	if(!ensure(MainMenuInterface)) return;
	MainMenuInterface->Host();
}

void UMYMainMenuWidget::Join()
{
	if(!ensure(MainMenuInterface)) return;
	MainMenuInterface->Join(TEXT("127.0.0.1"));
}
