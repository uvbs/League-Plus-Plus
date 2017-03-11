#include "sMenu.h"

sMenu::sMenu(IMenu* menu)
{
	Main = menu;
	{
		Draw = Main->AddMenu("Drawings");
		{
			DrawQ = Draw->CheckBox("Draw Q", true);
			DrawR = Draw->CheckBox("Draw R", true);
			DrawReady = Draw->CheckBox("Draw only if spell is ready", true);
		}

		Q = Main->AddMenu("Q Settings");
		{
			QImmobile = Q->CheckBox("Q on immobile enemies", true);
			QDashing = Q->CheckBox("Q on dashing enemies", true);
			QSemiManual = Q->AddKey("Semi manual cast", 'X');
		}

		W = Main->AddMenu("W Settings");
		{
			WSelectYellow = W->AddKey("Select yellow card", 'W');
			WSelectBlue = W->AddKey("Select blue card", 'E');
			WSelectRed = W->AddKey("Select red card", 'T');
			WAutoYellowR = W->CheckBox("Select yellow card after R", true);
		}

		R = Main->AddMenu("R Settings");
		{
			RPing = R->CheckBox("Ping low health enemies (Local)", true);
		}
	}
}