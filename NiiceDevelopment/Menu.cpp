#include "Plugin.h"
#include "Menu.h"

void Menu::Initialize()
{
	GPlugin->AddCheckBox("Main", "GUI", "Draw GUI", true);
	GPlugin->AddInteger("Main", "Position.X", "^-> GUI X Position", 0, GRender->ScreenSize().x, 10);
	GPlugin->AddInteger("Main", "Position.Y", "^-> GUI Y Position", 0, GRender->ScreenSize().y, 10);
	GPlugin->AddCheckBox("Main", "Mouse.Lines", "Draw Mouse Lines", true);
	GPlugin->AddCheckBox("Main", "Mouse.Informations", "Draw Mouse Informations", true);
}
