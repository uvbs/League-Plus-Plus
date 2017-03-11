#include "sMenu.h"

sMenu::sMenu(IMenu* menu)
{
	Main = menu;
	{
		Draw = Main->AddMenu("Drawings");
		{
			DrawW = Draw->CheckBox("Draw W", true);
			DrawE = Draw->CheckBox("Draw E", false);
			DrawR = Draw->CheckBox("Draw R", true);
			DrawReady = Draw->CheckBox("Draw only if spell is ready", true);
		}

		Q = Main->AddMenu("Q Settings");
		{
			QCombo = Q->CheckBox("Combo Q", true);
			QComboAoE = Q->AddInteger("^-> Force Fishbone if can hit {x} champions", 2, 5, 2);
			QHarass = Q->CheckBox("Harass Q", true);
			QFarmOutOfRange = Q->CheckBox("Force Fishbone to lasthit of range minions", false);
			QMinions = Q->AddInteger("Force Fishbone if can hit {x} minions", 2, 10, 3);
			QKillableAutoAttacks = Q->AddInteger("Ignore mana if can kill in {x} AA", 3, 10, 4);
		}

		W = Main->AddMenu("W Settings");
		{
			WCombo = W->CheckBox("Combo W", true);
			WHarass = W->CheckBox("Harass W", true);
			WEpics = W->CheckBox("Steal epics w/ W", true);
			WKillSteal = W->CheckBox("Steal w/ W", true);
			WSemiManual = W->AddKey("Semi manual cast", 'X');
			WHitchance = W->AddInteger("Hitchance (1 = lowest, 4 = highest)", 1, 4, 2);
		}

		E = Main->AddMenu("E Settings");
		{
			ECombo = E->CheckBox("Combo E", true);
			ETeleport = E->CheckBox("Use on enemy teleport", true);
			ECC = E->CheckBox("Use on hard CC", true);
			ESlow = E->CheckBox("Use on slow", true);
			EDash = E->CheckBox("Use on dash", true);
			EGapCloser = E->CheckBox("Use on gapclosers", true);
			ESpecialSpell = E->CheckBox("Use on special spell detection", true);
			EAoE = E->AddInteger("Use if can catch {x} enemies", 2, 5, 3);
		}

		R = Main->AddMenu("R Settings");
		{
			RKillSteal = R->CheckBox("Steal w/ R", true);
			RKillStealW = R->CheckBox("^-> Dont steal if W is enough", true);
			RKillStealAllies = R->AddInteger("^-> Dont steal if allies near target in {x} range", 0, 1000, 500);
			RSemiManual = R->AddKey("Semi manual cast", 'T');
			RSemiManualMode = R->AddSelection("^-> Mode", 0, { "low HP", "AoE" });
			RMaxRange = R->AddInteger("Max Range", 0, 10000, 3000);
		}

		Mana = Main->AddMenu("Mana Manager");
		{
			ManaQCombo = Mana->AddInteger("Q combo", 0, 100, 20);
			ManaQHarass = Mana->AddInteger("Q harass", 0, 100, 40);
			ManaQClear = Mana->AddInteger("Q clear", 0, 100, 80);
			ManaWCombo = Mana->AddInteger("W combo", 0, 100, 20);
			ManaWHarass = Mana->AddInteger("W harass", 0, 100, 40);
			ManaECombo = Mana->AddInteger("E combo", 0, 100, 20);
			ManaE = Mana->AddInteger("E", 0, 100, 75);
		}
	}
}