#include "Plugin.h"
#include "Menu.h"

void Menu::Initialize()
{
	GPlugin->AddCheckBox("RecallTracker", "Show RecallTracker", true);
	GPlugin->AddCheckBox("RecallTracker.Chat", "^-> Show in chat", true);
	GPlugin->AddCheckBox("RecallTracker.Notification", "^-> Show as notification", true);
	GPlugin->AddCheckBox("BaseUlt", "Base Ult", true);
	GPlugin->AddKey("PanicKey", "^-> Not while holding key", 32);
}
