#include "sMenu.h"

sMenu::sMenu(IMenu* menu)
{
	Main = menu;
	{
		DrawHeroes = Main->CheckBox("Check Heroes", true);
		DrawCreeps = Main->CheckBox("Check Creeps", true);
		DrawJungleCreeps = Main->CheckBox("Check JungleCreeps", true);
		DrawTurrets = Main->CheckBox("Check Turrets", true);
		DrawInformations = Main->CheckBox("Draw Informations", true);
		DrawProperties = Main->CheckBox("Draw Properties", true);
		DrawBuffs = Main->CheckBox("Draw Buffs", true);
		DrawExtendedBuffs = Main->CheckBox("^-> Extended Buffs", true);
		DrawMouseLines = Main->CheckBox("Draw Mouse Lines", true);
		DrawMouseInformations = Main->CheckBox("Draw Mouse Informations", true);
		AnalyzeRange = Main->AddInteger("Analyze Range", 10, 500, 500);
	}
}