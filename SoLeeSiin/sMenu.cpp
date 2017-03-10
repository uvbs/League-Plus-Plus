#include "sMenu.h"

sMenu::sMenu(IMenu* menu)
{
	Main = menu;
	{
		Draw = Main->AddMenu("Drawings");
		{

			DrawQ = Draw->CheckBox("Draw Q", true);
			DrawW = Draw->CheckBox("Draw W", true);
			DrawE = Draw->CheckBox("Draw E", true);
			DrawR = Draw->CheckBox("Draw R", true);
			DrawInsec = Draw->CheckBox("Draw Insec", true);
			DrawInsecLines = Draw->CheckBox("Draw Insec Lines", true);
			DrawReady = Draw->CheckBox("Draw only if spell is ready", true);
		}

		Q = Main->AddMenu("Q Settings");
		{
			QCombo = Q->CheckBox("Combo Q", true);
			Q2Combo = Q->CheckBox("Combo Q2", true);
		}

		W = Main->AddMenu("W Settings");
		{
			WCombo = W->CheckBox("Combo W", true);
			WJumpKey = W->AddKey("Escape Key", 71);
			WJumpMouse = W->CheckBox("Jump to mouse", true);
			WJumpMinions = W->CheckBox("Jump to minions", true);
			WJumpHeroes = W->CheckBox("Jump to heroes", true);
		}

		E = Main->AddMenu("E Settings");
		{
			ECombo = E->CheckBox("Combo E", true);
		}

		R = Main->AddMenu("R Settings");
		{
			RCombo = R->CheckBox("Combo R", true);
			RFlash = R->AddKey("Flash + R", 88);
		}
	}
}