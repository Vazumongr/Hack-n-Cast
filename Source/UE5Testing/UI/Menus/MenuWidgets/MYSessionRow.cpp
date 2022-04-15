// Troy Records Jr. 2021


#include "MYSessionRow.h"

#include "Components/TextBlock.h"

void UMYSessionRow::SetSessionName(FString InSessionName)
{
	SessionName->SetText(FText::FromString(InSessionName));
}

void UMYSessionRow::SetMainMenu(UMYMainMenuWidget* InMenu)
{
	MainMenuWidget = InMenu;
}
