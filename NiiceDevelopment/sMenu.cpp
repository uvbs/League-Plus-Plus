#include "sMenu.h"

sMenu::sMenu(IMenu* menu)
{
	Main = menu;
	{
		DrawGui = Main->CheckBox("Draw GUI", true);
		GuiX = Main->AddInteger("GUI X Position", 0, GRender->ScreenSize().x, 10);
		GuiY = Main->AddInteger("GUI Y Position", 0, GRender->ScreenSize().y, 10);
		DrawMouseLines = Main->CheckBox("Draw Mouse Lines", true);
		DrawMouseInformations = Main->CheckBox("Draw Mouse Informations", true);
	}
}