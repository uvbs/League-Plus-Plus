#include "Plugin.h"
#include "Menu.h"
#include "Extension.h"

void Menu::Initialize()
{
	GPlugin->AddMenu("Drawings", "Drawings");
	{
		GPlugin->AddCheckBox("Drawings", "W", "Draw W", false);
		GPlugin->AddCheckBox("Drawings", "E", "Draw E", true);
		GPlugin->AddCheckBox("Drawings", "R", "Draw R", true);
		GPlugin->AddCheckBox("Drawings", "Ready", "Draw only if spell is ready", true);
	}

	GPlugin->AddMenu("Q", "Q Settings");
	{
		GPlugin->AddCheckBox("Q", "Combo", "Combo Q", true);
		GPlugin->AddCheckBox("Q", "E.Check", "^- Only use when E target is in range", true);
	}

	GPlugin->AddMenu("E", "E Settings");
	{
		GPlugin->AddCheckBox("E", "Focus", "Focus E target", false);
		GPlugin->AddCheckBox("E", "Combo", "Combo E", true);

		GPlugin->AddMenu("E.Whitelist", "Whitelist", "E");
		GPlugin->AddMenu("E.Priority", "Priority", "E");
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				auto dangerLevel = GExtension->GetDangerLevel(enemy);

				GPlugin->AddCheckBox("E.Whitelist", const_cast<char*>(enemy->ChampionName()), const_cast<char*>(GExtension->format("Use E on: %s", enemy->ChampionName()).c_str()), dangerLevel >= 4 ? true : false);
				GPlugin->AddInteger("E.Priority", const_cast<char*>(enemy->ChampionName()), const_cast<char*>(GExtension->format("Priority for: %s", enemy->ChampionName()).c_str()), 1, 5, dangerLevel);
			}
		}
	}

	GPlugin->AddMenu("R", "R Settings");
	{
		GPlugin->AddCheckBox("R", "Finisher", "Use R to finish", true);
		GPlugin->AddCheckBox("R", "E.Overkill", "^-> Dont use R if E explosion is enough", true);
	}
}