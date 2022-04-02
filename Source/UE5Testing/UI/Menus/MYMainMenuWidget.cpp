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
	if(!ensure(QuitButton)) return false;
	QuitButton->OnClicked.AddDynamic(this,&UMYMainMenuWidget::Quit);

	return true;
}

void UMYMainMenuWidget::Host()
{
	if(!ensure(MainMenuInterface)) return;
	MainMenuInterface->Host();
}

void UMYMainMenuWidget::JoinServer(FString IPAddress)
{
	if(!ensure(MainMenuInterface)) return;
	MainMenuInterface->Join(IPAddress);
}

void UMYMainMenuWidget::Join()
{
	JoinServer(TEXT("127.0.0.1"));
}

void UMYMainMenuWidget::Quit()
{
	if(!ensure(MainMenuInterface)) return;
	MainMenuInterface->QuitGame();
}
