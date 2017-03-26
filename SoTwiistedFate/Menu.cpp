#include "Plugin.h"
#include "Menu.h"

void Menu::Initialize()
{
	GPlugin->AddMenu("Drawings", "SoTwiistedFate: Drawings");
	{
		GPlugin->AddCheckBox("Drawings", "Q", "Draw Q", true);
		GPlugin->AddCheckBox("Drawings", "R", "Draw R", true);
		GPlugin->AddCheckBox("Drawings", "Ready", "Draw only if spell is ready", true);
	}

	GPlugin->AddMenu("Q", "SoTwiistedFate: Q Settings");
	{
		GPlugin->AddCheckBox("Q", "Immobile", "Q Immobile enemies", true);
		GPlugin->AddCheckBox("Q", "Dashing", "Q Dashing enemies", true);
		GPlugin->AddKey("Q", "Key", "Semi manual cast", 'X');
	}

	GPlugin->AddMenu("W", "SoTwiistedFate: W Settings");
	{
		GPlugin->AddCheckBox("W", "AutoAttack", "Dont autoattack while rotating", true);
		GPlugin->AddKey("W", "Key.Yellow", "Select yellow card", 'W');
		GPlugin->AddKey("W", "Key.Blue", "Select blue card", 'E');
		GPlugin->AddKey("W", "Key.Red", "Select red card", 'T');
		GPlugin->AddCheckBox("W", "R.Yellow", "Select yellow card after R", true);
	}

	GPlugin->AddMenu("R", "SoTwiistedFate: R Settings");
	{
		GPlugin->AddCheckBox("R", "Ping", "Ping low health enemies (Local)", true);
	}
}
