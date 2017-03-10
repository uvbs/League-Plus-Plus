#include "PluginSDK.h"
#include "sExtensions.h"
#include "sMenu.h"
#include <string>

PluginSetup("NiiceDevelopment");

sMenu* Menu;

PLUGIN_EVENT(void) OnRender()
{
	Vec3 worldToScreenMouse;
	GGame->Projection(GGame->CursorPosition(), &worldToScreenMouse);
	
	if (Menu->DrawMouseLines->Enabled())
	{
		GRender->DrawLine(Vec2(worldToScreenMouse.x, 0), Vec2(worldToScreenMouse.x, GRender->ScreenSize().y), Vec4(255, 255, 255, 255));
		GRender->DrawLine(Vec2(0, worldToScreenMouse.y), Vec2(GRender->ScreenSize().x, worldToScreenMouse.y), Vec4(255, 255, 255, 255));
	}

	if (Menu->DrawMouseInformations->Enabled())
	{
		GRender->DrawTextW(Vec2(worldToScreenMouse.x + 40, worldToScreenMouse.y), Vec4(255, 128, 0, 255), sExtensions::format("Screen Position | X: %d Y: %d", static_cast<int>(worldToScreenMouse.x), static_cast<int>(worldToScreenMouse.y)).c_str());
		GRender->DrawTextW(Vec2(worldToScreenMouse.x + 40, worldToScreenMouse.y + 20), Vec4(255, 128, 0, 255), sExtensions::format("Game Position | X: %d Y: %d Z: %d", static_cast<int>(GGame->CursorPosition().x), static_cast<int>(GGame->CursorPosition().y), static_cast<int>(GGame->CursorPosition().z)).c_str());
	
		GRender->DrawTextW(Vec2(worldToScreenMouse.x + 40, worldToScreenMouse.y + 40), Vec4(255, 128, 0, 255), sExtensions::format("Left Mouse Button: %s", GetAsyncKeyState(VK_LBUTTON) ? "true" : "false").c_str());
		GRender->DrawTextW(Vec2(worldToScreenMouse.x + 40, worldToScreenMouse.y + 60), Vec4(255, 128, 0, 255), sExtensions::format("Right Mouse Button: %s", GetAsyncKeyState(VK_RBUTTON) ? "true" : "false").c_str());
	}

	GRender->DrawCircle(GGame->CursorPosition(), Menu->AnalyzeRange->GetInteger(), Vec4(255, 0, 0, 255));

	for (auto unit : GEntityList->GetAllUnits())
	{
		if ((unit->IsHero() && !Menu->DrawHeroes->Enabled() || !unit->IsHero() && Menu->DrawHeroes->Enabled()) &&
			(unit->IsCreep() && !Menu->DrawCreeps->Enabled() || !unit->IsCreep() && Menu->DrawCreeps->Enabled()) &&
			(unit->IsJungleCreep() && !Menu->DrawJungleCreeps->Enabled() || !unit->IsJungleCreep() && Menu->DrawJungleCreeps->Enabled()) &&
			(unit->IsTurret() && !Menu->DrawTurrets->Enabled() || !unit->IsTurret() && Menu->DrawTurrets->Enabled()) ||
			!unit->IsHero() && !unit->IsCreep() && !unit->IsJungleCreep() && !unit->IsTurret())
			continue;

		auto i = 0;
		auto step = 20;

		Vec3 worldToScreenUnit;
		GGame->Projection(unit->GetPosition(), &worldToScreenUnit);

		if (sExtensions::GetDistance(GGame->CursorPosition(), unit->GetPosition()) <= Menu->AnalyzeRange->GetInteger())
		{
			if (Menu->DrawInformations->Enabled())
			{
				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(255, 128, 0, 255), "Informations:");
				i += step;

				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(160, 160, 160, 255), sExtensions::format("Type Name: %s", unit->GetType() == FL_MISSILE ? "Missile" : unit->GetType() == FL_TURRET ? "Turret" : unit->GetType() == FL_HERO ? "Hero" : unit->GetType() == FL_CREEP ? "Creep" : "invalid").c_str());
				i += step;
				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(160, 160, 160, 255), sExtensions::format("Type: %d", unit->GetType()).c_str());
				i += step;
				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(160, 160, 160, 255), sExtensions::format("Name: %s", unit->GetObjectName()).c_str());
				i += step;
				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(160, 160, 160, 255), sExtensions::format("Position | X: %d Y: %d Z: %d", static_cast<int>(unit->GetPosition().x), static_cast<int>(unit->GetPosition().y), static_cast<int>(unit->GetPosition().z)).c_str());
				i += step;
				GRender->DrawCircle(unit->GetPosition(), unit->BoundingRadius(), Vec4(153, 0, 0, 255));
			}
			
			if (Menu->DrawProperties->Enabled())
			{
				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(255, 128, 0, 255), "Properties:");
				i += step;

				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(160, 160, 160, 255), sExtensions::format("BaseSkinName: %s", unit->GetBaseSkinName()).c_str());
				i += step;
				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(160, 160, 160, 255), sExtensions::format("SkinName: %s", unit->SkinName()).c_str());
				i += step;
				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(160, 160, 160, 255), sExtensions::format("Health: %d", static_cast<int>(unit->GetHealth())).c_str());
				i += step;
				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(160, 160, 160, 255), sExtensions::format("Mana: %d", static_cast<int>(unit->GetMana())).c_str());
				i += step;
				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(160, 160, 160, 255), sExtensions::format("BoundingRadius: %d", static_cast<int>(unit->BoundingRadius())).c_str());
				i += step;
				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(160, 160, 160, 255), sExtensions::format("IsValid: %s", (unit->IsValidObject() ? "true" : "false")).c_str());
				i += step;
				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(160, 160, 160, 255), sExtensions::format("IsVisible: %s", (unit->IsVisible() ? "true" : "false")).c_str());
				i += step;
				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(160, 160, 160, 255), sExtensions::format("IsTargetable: %s", (unit->IsTargetable() ? "true" : "false")).c_str());
				i += step;
				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(160, 160, 160, 255), sExtensions::format("IsDead: %s", (unit->IsDead() ? "true" : "false")).c_str());
				i += step;
			}

			if (Menu->DrawBuffs->Enabled())
			{
				GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(255, 128, 0, 255), "Buffs:");
				i += step;

				std::vector<void*> buffs;
				unit->GetAllBuffsData(buffs);

				for (auto buff : buffs)
				{
					if (GBuffData->IsValid(buff))
					{
						auto endTime = max(0, GBuffData->GetEndTime(buff) - GGame->Time());

						if (Menu->DrawExtendedBuffs->Enabled())
						{
							GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(160, 160, 160, 255), sExtensions::format("Name: %s | Caster: %s | SourceName: %s | Count: %d | RemainingTime: %s", GBuffData->GetBuffName(buff), GBuffData->GetCaster(buff)->GetBaseSkinName(), GBuffData->GetCaster(buff)->GetObjectName(), GBuffData->GetStacks(buff), endTime > 1000 ? "Infinite" : std::to_string(endTime).c_str()).c_str());
						} 
						else
						{
							GRender->DrawTextW(Vec2(worldToScreenUnit.x, worldToScreenUnit.y + i), Vec4(160, 160, 160, 255), sExtensions::format("Name: %s | Caster: %s | Count: %d", GBuffData->GetBuffName(buff), GBuffData->GetCaster(buff)->GetBaseSkinName(), GBuffData->GetStacks(buff)).c_str());
						}

						i += step;
					}
				}
			}
		}
	}
}

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	PluginSDKSetup(PluginSDK);

	Menu = new sMenu(GPluginSDK->AddMenu("NiiceDevelopment"));
	
	GEventManager->AddEventHandler(kEventOnRender, OnRender);

	GGame->PrintChat("<font color=\"#0095DA\"><b>NiiceDevelopment</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">Loaded</font>");
}

PLUGIN_API void OnUnload()
{
	Menu->Main->Remove();

	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);

	GGame->PrintChat("<font color=\"#0095DA\"><b>NiiceDevelopment</b></font> - <font color=\"#FFFFFF\">Unloaded</font>");
}