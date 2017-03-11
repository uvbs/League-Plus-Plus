#include "sMenu.h"

sMenu::sMenu(IMenu* menu)
{
	Main = menu;
	{
		Draw = Main->AddMenu("Drawings");
		{
			DrawQ = Draw->CheckBox("Draw Q", true);
			DrawE = Draw->CheckBox("Draw E", true);
			DrawR = Draw->CheckBox("Draw R", true);
			DrawReady = Draw->CheckBox("Draw only if spell is ready", true);
		}

		Q = Main->AddMenu("Q Settings");
		{
			QCombo = Q->CheckBox("Combo Q", true);
			QClear = Q->CheckBox("Clear Q", true);
			QKillSteal = Q->CheckBox("KillSteal Q", true);
			QFlee = Q->CheckBox("Flee Q", true);
		}

		W = Main->AddMenu("W Settings");
		{
			WCombo = W->CheckBox("Combo W", true);
			WComboHeal = W->AddInteger("^-> Switch to heal if health is under {x}%", 0, 100, 50);
			WClear = W->CheckBox("Clear W", true);
			WClearHeal = W->AddInteger("^-> Switch to heal if health is under {x}%", 0, 100, 50);
		}

		E = Main->AddMenu("E Settings");
		{
			ECombo = E->CheckBox("Combo E", true);
			EHarass = E->CheckBox("Harass E", true);
			EClear = E->CheckBox("Clear E", true);
			EKillSteal = E->CheckBox("KillSteal E", true);
			EFlee = E->CheckBox("Flee E", true);
		}

		R = Main->AddMenu("R Settings");
		{
			RCombo = R->CheckBox("Combo E", true);
			RComboEnemyHealth = R->AddInteger("^-> If enemy health is under {x}%", 0, 100, 70);
			RComboEnemyCount = R->AddInteger("^-> Or more than {x} enemies in range", 1, 5, 2);
		}

		Misc = Main->AddMenu("Misc");
		{
			MiscFleeKey = Misc->AddKey("Flee", 'G');
		}
	}
}