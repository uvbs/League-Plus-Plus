#include "Plugin.h"
#include "Menu.h"

void Menu::Initialize()
{
	GPlugin->AddMenu("Drawings", "Drawings");
	{
		GPlugin->AddCheckBox("Drawings", "Q", "Draw Q", true);
		GPlugin->AddCheckBox("Drawings", "E", "Draw E", true);
		GPlugin->AddCheckBox("Drawings", "R", "Draw R", true);
		GPlugin->AddCheckBox("Drawings", "Ready", "Draw only if spell is ready", true);
	}

	GPlugin->AddMenu("Q", "Q Settings");
	{
		GPlugin->AddCheckBox("Q", "Combo", "Combo Q", true);
		GPlugin->AddCheckBox("Q", "Clear", "Clear Q", false);
		GPlugin->AddCheckBox("Q", "Jungle", "Jungle Q", true);
		GPlugin->AddCheckBox("Q", "KillSteal", "KillSteal Q", true);
		GPlugin->AddCheckBox("Q", "Flee", "Flee Q", true);
	}

	GPlugin->AddMenu("W", "W Settings");
	{
		GPlugin->AddCheckBox("W", "Combo", "Combo W", true);
		GPlugin->AddInteger("W", "Combo.Heal", "^-> Switch to heal if health is under {x}%", 0, 100, 50);
		GPlugin->AddCheckBox("W", "Clear", "Clear W", false);
		GPlugin->AddInteger("W", "Clear.Heal", "^-> Switch to heal if health is under {x}%", 0, 100, 75);
		GPlugin->AddCheckBox("W", "Jungle", "Jungle W", true);
		GPlugin->AddInteger("W", "Jungle.Heal", "^-> Switch to heal if health is under {x}%", 0, 100, 75);
	}

	GPlugin->AddMenu("E", "E Settings");
	{
		GPlugin->AddCheckBox("E", "Combo", "Combo E", true);
		GPlugin->AddCheckBox("E", "Harass", "Harass E", true);
		GPlugin->AddCheckBox("E", "Clear", "Clear E", true);
		GPlugin->AddCheckBox("E", "Jungle", "Jungle E", true);
		GPlugin->AddCheckBox("E", "KillSteal", "KillSteal E", true);
		GPlugin->AddCheckBox("E", "Flee", "Flee E", true);
	}

	GPlugin->AddMenu("R", "R Settings");
	{
		GPlugin->AddCheckBox("R", "Combo", "Combo R", true);
		GPlugin->AddInteger("R", "Combo.Health", "^-> If enemy health is under {x}%", 0, 100, 70);
		GPlugin->AddInteger("R", "Combo.Enemies", "^-> Or more than {x} enemies in range", 1, 5, 2);
	}

	GPlugin->AddMenu("Keys", "Key Settings");
	{
		GPlugin->AddKey("Keys", "Flee", "Flee Key", 'G');
	}
}
