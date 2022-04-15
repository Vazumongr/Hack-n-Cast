// Troy Records Jr.


#include "MYMainMenuWidget.h"

#include "OnlineSessionSettings.h"
#include "UE5Testing/GameInstances/MYGameInstance.h"
#include "UE5Testing/Interfaces/MYMainMenuInterface.h"
#include "UE5Testing/UI/Menus/MenuWidgets/MYSessionRow.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"

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
	if(SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index: %d"), SelectedIndex.GetValue());
	}
	//MainMenuInterface->Join(IPAddress);
}

void UMYMainMenuWidget::AddListEntry(FString SessionName)
{
	UMYSessionRow* SessionRow = CreateWidget<UMYSessionRow>(this, SessionRowClass);
	if(SessionRow == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create SessionRow"));
		return;
	}
	SessionRow->SetSessionName(SessionName);
	SessionRow->SetMainMenu(this);
	SessionList->AddChild(SessionRow);
}

void UMYMainMenuWidget::Join()
{
	//JoinServer(TEXT("127.0.0.1"));
	if(!ensure(MainMenuInterface)) return;
	MainMenuInterface->SessionsFoundDelegate.BindUObject(this, &UMYMainMenuWidget::OnSessionsFound);
	MainMenuInterface->FindSessions();
}

void UMYMainMenuWidget::OnSessionsFound(TArray<FOnlineSessionSearchResult> Sessions)
{
	for(FOnlineSessionSearchResult& Session : Sessions)
	{
		/*GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,FString::Printf(TEXT("Found Session: %s"), *Session.GetSessionIdStr()));
		UMYSessionRow* SessionRow = CreateWidget<UMYSessionRow>(this, SessionRowClass);
		if(SessionRow == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create SessionRow"));
			return;
		}
		SessionRow->SetSessionName(Session.GetSessionIdStr());
		SessionList->AddChild(SessionRow);*/
		AddListEntry(Session.GetSessionIdStr());
	}
}

void UMYMainMenuWidget::SetIndex(int32 InIndex)
{
	SelectedIndex = InIndex;
}

void UMYMainMenuWidget::Quit()
{
	if(!ensure(MainMenuInterface)) return;
	MainMenuInterface->QuitGame();
}
