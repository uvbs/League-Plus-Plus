#include "Plugin.h"
#include "Menu.h"

void Menu::Initialize()
{
	GPlugin->AddMenu("Drawings", "SoJiinx: Drawings");
	{
		GPlugin->AddCheckBox("Drawings", "W", "Draw W", true);
		GPlugin->AddCheckBox("Drawings", "E", "Draw E", false);
		GPlugin->AddCheckBox("Drawings", "R", "Draw R", true);
		GPlugin->AddCheckBox("Drawings", "Ready", "Draw only if spell is ready", true);
	}

	GPlugin->AddMenu("Q", "SoJiinx: Q Settings");
	{
		GPlugin->AddCheckBox("Q", "Combo", "Combo Q", true);
		GPlugin->AddCheckBox("Q", "Combo.Stacks", "^-> Try to hold 3 Q stacks while Fishbone", true);
		GPlugin->AddInteger("Q", "Combo.Enemies", "^-> Force Fishbone if can hit {x} champions", 2, 5, 2);
		GPlugin->AddCheckBox("Q", "Harass", "Harass Q", true);
		GPlugin->AddCheckBox("Q", "Lasthit.OutOfRange", "Force Fishbone to lasthit out of range minions", false);
		GPlugin->AddInteger("Q", "Clear.Minions", "Force Fishbone if can hit {x} minions", 2, 10, 3);
		GPlugin->AddInteger("Q", "Mana.Ignore", "Ignore mana if can kill in {x} autoattacks", 3, 10, 4);
	}

	GPlugin->AddMenu("W", "SoJiinx: W Settings");
	{
		GPlugin->AddCheckBox("W", "Combo", "Combo W", true);
		GPlugin->AddInteger("W", "Combo.Range", "^-> Minimum range to use", 0, 1400, 1000);
		GPlugin->AddCheckBox("W", "Harass", "Harass W", true);
		GPlugin->AddCheckBox("W", "Epics", "Steal epic jungle creeps w/ W", true);
		GPlugin->AddCheckBox("W", "KillSteal", "KillSteal W", true);
		GPlugin->AddKey("W", "Key", "Semi manual cast", 'X');
		GPlugin->AddInteger("W", "Hitchance", "Hitchance (1 = lowest, 4 = highest)", 1, 4, 4);
	}

	GPlugin->AddMenu("E", "SoJiinx: E Settings");
	{
		GPlugin->AddCheckBox("E", "Combo", "Combo E", false);
		GPlugin->AddCheckBox("E", "OnTeleport", "Use on enemy teleport", true);
		GPlugin->AddCheckBox("E", "OnCC", "Use on hard CC", true);
		GPlugin->AddCheckBox("E", "OnSlow", "Use on slow", true);
		GPlugin->AddCheckBox("E", "OnDash", "Use on dash", true);
		GPlugin->AddCheckBox("E", "OnGapCloser", "Use on gapclosers", true);
		GPlugin->AddCheckBox("E", "OnSpecialSpell", "Use on special spell detection", false);
		GPlugin->AddInteger("E", "Enemies", "Use if can catch {x} enemies", 2, 5, 3);
	}

	GPlugin->AddMenu("R", "SoJiinx: R Settings");
	{
		GPlugin->AddCheckBox("R", "KillSteal", "KillSteal R", true);
		GPlugin->AddCheckBox("R", "KillSteal.W", "^-> Dont steal if W is enough", true);
		GPlugin->AddInteger("R", "KillSteal.Allies", "^-> Dont steal if allies near target in {x} range", 0, 1000, 500);
		GPlugin->AddKey("R", "Key", "Semi manual cast", 'T');
		GPlugin->AddSelection("R", "Key.Mode", "^-> Mode", 0, std::vector<std::string>({ "low HP", "AoE" }));
		GPlugin->AddInteger("R", "Range", "Max range", 0, 10000, 3000);
	}

	GPlugin->AddMenu("Mana", "SoJiinx: Mana Manager");
	{
		GPlugin->AddInteger("Mana", "Q.Combo", "Q Combo", 0, 100, 20);
		GPlugin->AddInteger("Mana", "Q.Harass", "Q Harass", 0, 100, 40);
		GPlugin->AddInteger("Mana", "Q.Clear", "Q Clear", 0, 100, 80);
		GPlugin->AddInteger("Mana", "W.Combo", "W Combo", 0, 100, 20);
		GPlugin->AddInteger("Mana", "W.Harass", "W Harass", 0, 100, 40);
		GPlugin->AddInteger("Mana", "E.Combo", "E Combo", 0, 100, 20);
		GPlugin->AddInteger("Mana", "E.Auto", "Auto E", 0, 100, 50);
	}
}
