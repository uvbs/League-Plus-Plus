#include "Plugin.h"
#include "Menu.h"

void Menu::Initialize()
{
	GPlugin->AddMenu("Drawings", "Drawings");
	{
		GPlugin->AddCheckBox("Drawings", "Q", "Draw Q", true);
		GPlugin->AddCheckBox("Drawings", "W", "Draw W", false);
		GPlugin->AddCheckBox("Drawings", "E", "Draw E", true);
		GPlugin->AddCheckBox("Drawings", "E.Damage", "Draw E Damage", true);
		GPlugin->AddCheckBox("Drawings", "R", "Draw R", true);
		GPlugin->AddCheckBox("Drawings", "Ready", "Draw only if spell is ready", true);
	}

	GPlugin->AddMenu("Q", "Q Settings");
	{
		GPlugin->AddCheckBox("Q", "Combo", "Combo Q", true);
		GPlugin->AddCheckBox("Q", "Harass", "Harass Q", true);
		GPlugin->AddCheckBox("Q", "KillSteal", "KillSteal Q", true);
		GPlugin->AddCheckBox("Q", "Lasthit.Unkillable", "Lasthit unkillable minions w/o stacks", false);
	}

	GPlugin->AddMenu("W", "W Settings");
	{
		GPlugin->AddKey("W", "Dragon", "Sentinel Dragon", 'Y');
		GPlugin->AddKey("W", "Baron", "Sentinel Baron", 'T');
	}

	GPlugin->AddMenu("E", "E Settings");
	{
		GPlugin->AddCheckBox("E", "Combo", "Combo E", true);
		GPlugin->AddCheckBox("E", "Harass", "Harass E", true);
		GPlugin->AddCheckBox("E", "Lasthit.Unkillable", "Lasthit unkillable minions", true);
		GPlugin->AddCheckBox("E", "Clear", "Clear E", true);
		GPlugin->AddInteger("E", "Clear.Minions", "^-> Minimum kill {x} minions", 2, 10, 4);
		GPlugin->AddCheckBox("E", "Jungle", "Steal Jungle E", true);
	}

	GPlugin->AddMenu("R", "R Settings");
	{
		GPlugin->AddCheckBox("R", "Save", "Use R to save ally", true);
		GPlugin->AddInteger("R", "Save.Health", "^-> Save at {x}% health", 1, 100, 5);
	}
}
