// Troy Records Jr. 2021


#include "MYSessionRow.h"

#include "OnlineSessionSettings.h"
#include "Components/TextBlock.h"

void UMYSessionRow::SetSessionName(FString InSessionName)
{
	SessionName->SetText(FText::FromString(InSessionName));
}

void UMYSessionRow::SetMainMenu(UMYMainMenuWidget* InMenu)
{
	MainMenuWidget = InMenu;
}

void UMYSessionRow::SetSession(FOnlineSessionSearchResult* InSession)
{
	SessionPtr = MakeShareable<FOnlineSessionSearchResult>(InSession);
}

void UMYSessionRow::SetSession(FOnlineSessionSearchResult& InSession)
{
	SessionPtr = MakeShareable<FOnlineSessionSearchResult>(&InSession);
}

void UMYSessionRow::SetIndex(int32 InIndex)
{
	Index = InIndex;
}
