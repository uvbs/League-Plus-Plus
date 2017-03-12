#include "sMenu.h"

sMenu::sMenu(IMenu* menu)
{
	Main = menu;
	{
		Draw = Main->AddMenu("Drawings");
		{
			DrawR = Draw->CheckBox("Draw R", true);
			DrawEngageRange = Draw->CheckBox("Draw Engage Range", true);
			DrawBurstRange = Draw->CheckBox("Draw Burst Range", true);
			DrawComboDamage = Draw->CheckBox("Draw Combo Damage", true);
		}

		Keys = Main->AddMenu("Key Settings");
		{
			KeysFlee = Keys->AddKey("Flee", 'G');
			KeysBurst = Keys->AddKey("Burst", 'T');;
		}

		Q = Main->AddMenu("Q Settings");
		{
			QKeep = Q->CheckBox("Keep Q", true);
			QGapclose = Q->CheckBox("Use Q to gapclose", true);
			QSafe = Q->CheckBox("Block Q into multiple enemies", true);
			QJungle = Q->CheckBox("Q Jungle", true);
			QClear = Q->CheckBox("Q Clear", true);
		}

		W = Main->AddMenu("W Settings");
		{
			WFlashBurst = W->CheckBox("Use flash in burst before W", true);
			WCombo = W->CheckBox("W Combo", true);
			WInterrupt = W->CheckBox("Use W to interrupt", true);
			WGapCloser = W->CheckBox("Use W on GapClosers", true);
			WJungle = W->CheckBox("W Jungle", true);
			WClear = W->CheckBox("W Clear", true);
			WUnkillable = W->CheckBox("W unkillable minions", true);
		}

		E = Main->AddMenu("E Settings");
		{
			ECombo = E->CheckBox("E Combo", true);
			ESafe = E->CheckBox("Block E into multiple enemies", true);
			EJungle = E->CheckBox("E Jungle", true);
			EClear = E->CheckBox("E Clear", true);
		}

		R1 = Main->AddMenu("R1 Settings");
		{
			R1Combo = R1->CheckBox("R1 Combo", true);
			R1Mode = R1->AddSelection("R1 Mode", 2, std::vector<std::string> { "Normal Kill", "Hard Kill", "Always" });
			R1Overkill = R1->AddInteger("Dont R1 if target health is under {x}%", 0, 100, 25);
		}

		R2 = Main->AddMenu("R2 Settings");
		{
			R2Combo = R2->CheckBox("R2 Combo", true);
			R2Hitchance = R2->AddInteger("Hitchance (1 = lowest, 4 = highest)", 1, 4, 4);
			R2Mode = R2->AddSelection("R2 Mode", 1, std::vector<std::string> { "Kill only", "Max Damage" });
			R2Keep = R2->CheckBox("R2 before expiry", true);
		}
	}
}