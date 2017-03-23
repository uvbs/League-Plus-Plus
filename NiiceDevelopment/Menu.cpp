#include "Plugin.h"
#include "Menu.h"

void Menu::Initialize()
{
	GPlugin->AddCheckBox("GUI", "Draw GUI", true);
	GPlugin->AddInteger("Position.X", "^-> GUI X Position", 0, GRender->ScreenSize().x, 10);
	GPlugin->AddInteger("Position.Y", "^-> GUI Y Position", 0, GRender->ScreenSize().y, 10);
	GPlugin->AddCheckBox("Mouse.Lines", "Draw Mouse Lines", true);
	GPlugin->AddCheckBox("Mouse.Informations", "Draw Mouse Informations", true);
}
