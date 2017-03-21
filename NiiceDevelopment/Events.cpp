#include "Events.h"
#include "Plugin.h"
#include "Extension.h"
#include <string>

ITexture* Background;
IUnit* FocusedUnit = nullptr;
bool LastClickBool = false;
int ClickCount = 0;
int LastClick = 0;
Vec3 LastClickPosition = Vec3(0, 0, 0);

void Events::Initialize()
{
	Background = GExtension->GetTexture("niice_development_background.png");

	GPlugin->RegisterGameUpdateEvent(OnGameUpdate);
	GPlugin->RegisterRenderEvent(OnRender);
}

void Events::OnGameUpdate()
{
	if (!GUtility->IsLeagueWindowFocused())
		return;

	if (GetAsyncKeyState(VK_LBUTTON)) {
		if (LastClick <= GGame->TickCount() && ClickCount != 0)
		{
			LastClick = 9999999999;
			ClickCount = 0;
			FocusedUnit = nullptr;
		}

		if (!LastClickBool || ClickCount == 0)
		{
			LastClickBool = true;
			ClickCount++;
			LastClick = GGame->TickCount() + 100;
			LastClickPosition = GGame->CursorPosition();
		}

		if (LastClickBool && GExtension->GetDistance(GGame->CursorPosition(), LastClickPosition) < 50)
		{
			ClickCount++;
			LastClickBool = false;
		}

		for (auto unit : GEntityList->GetAllUnits())
		{
			if (!unit->IsHero() && !unit->IsCreep() && !unit->IsJungleCreep() && !unit->IsTurret())
				continue;

			if (GExtension->GetDistance(GGame->CursorPosition(), unit->GetPosition()) < 80)
			{
				FocusedUnit = unit;
				break;
			}
		}
	}
}

void Events::OnRender()
{
	Vec3 worldToScreenMouse;
	GGame->Projection(GGame->CursorPosition(), &worldToScreenMouse);

	if (GPlugin->GetMenuOption("Main", "Mouse.Lines")->Enabled())
	{
		GRender->DrawLine(Vec2(worldToScreenMouse.x, 0), Vec2(worldToScreenMouse.x, GRender->ScreenSize().y), Vec4(255, 255, 255, 255));
		GRender->DrawLine(Vec2(0, worldToScreenMouse.y), Vec2(GRender->ScreenSize().x, worldToScreenMouse.y), Vec4(255, 255, 255, 255));
	}

	if (GPlugin->GetMenuOption("Main", "Mouse.Informations")->Enabled())
	{
		GRender->DrawTextW(Vec2(worldToScreenMouse.x + 40, worldToScreenMouse.y), Vec4(255, 128, 0, 255), "Screen Position | X: %d Y: %d", static_cast<int>(worldToScreenMouse.x), static_cast<int>(worldToScreenMouse.y));
		GRender->DrawTextW(Vec2(worldToScreenMouse.x + 40, worldToScreenMouse.y + 20), Vec4(255, 128, 0, 255), "Game Position | X: %d Y: %d Z: %d", static_cast<int>(GGame->CursorPosition().x), static_cast<int>(GGame->CursorPosition().y), static_cast<int>(GGame->CursorPosition().z));

		GRender->DrawTextW(Vec2(worldToScreenMouse.x + 40, worldToScreenMouse.y + 40), Vec4(255, 128, 0, 255), "Left Mouse Button: %s", GetAsyncKeyState(VK_LBUTTON) ? "true" : "false");
		GRender->DrawTextW(Vec2(worldToScreenMouse.x + 40, worldToScreenMouse.y + 60), Vec4(255, 128, 0, 255), "Right Mouse Button: %s", GetAsyncKeyState(VK_RBUTTON) ? "true" : "false");
	}

	if (FocusedUnit == nullptr)
		return;

	if (GPlugin->GetMenuOption("Main", "GUI")->Enabled())
	{
		Background->Draw(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger(), GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger());

		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + Background->GetSize().x / 2 - static_cast<std::string>(FocusedUnit->GetObjectName()).length() * 4 / 2, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 22), Vec4(255, 255, 255, 255), FocusedUnit->GetObjectName());
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + Background->GetSize().x / 2 - static_cast<std::string>(FocusedUnit->GetBaseSkinName()).length() * 4 / 2, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 68), Vec4(255, 255, 255, 255), FocusedUnit->GetBaseSkinName());

		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 20, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 100), Vec4(255, 128, 0, 255), "Informations:");
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 20, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 120), Vec4(160, 160, 160, 255), "Type:");
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 150, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 120), Vec4(255, 255, 255, 255), "%s (%d)", FocusedUnit->GetType() == FL_MISSILE ? "Missile" : FocusedUnit->GetType() == FL_TURRET ? "Turret" : FocusedUnit->GetType() == FL_HERO ? "Hero" : FocusedUnit->GetType() == FL_CREEP ? "Creep" : "invalid", FocusedUnit->GetType());
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 20, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 140), Vec4(160, 160, 160, 255), "Position (X | Y | Z):");
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 150, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 140), Vec4(255, 255, 255, 255), "%d | %d | %d", static_cast<int>(FocusedUnit->GetPosition().x), static_cast<int>(FocusedUnit->GetPosition().y), static_cast<int>(FocusedUnit->GetPosition().z));

		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 20, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 200), Vec4(255, 128, 0, 255), "Properties:");
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 20, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 220), Vec4(160, 160, 160, 255), "SkinName:");
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 150, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 220), Vec4(255, 255, 255, 255), FocusedUnit->SkinName());
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 20, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 240), Vec4(160, 160, 160, 255), "Health:");
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 150, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 240), Vec4(255, 255, 255, 255), "%d / %d (%d%%)", static_cast<int>(FocusedUnit->GetHealth()), static_cast<int>(FocusedUnit->GetMaxHealth()), static_cast<int>(FocusedUnit->HealthPercent()));
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 20, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 260), Vec4(160, 160, 160, 255), "Mana:");
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 150, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 260), Vec4(255, 255, 255, 255), "%d / %d (%d%%)", static_cast<int>(FocusedUnit->GetMana()), static_cast<int>(FocusedUnit->GetMaxMana()), static_cast<int>(FocusedUnit->ManaPercent()));
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 20, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 280), Vec4(160, 160, 160, 255), "BoundingRadius:");
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 150, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 280), Vec4(255, 255, 255, 255), std::to_string(static_cast<int>(FocusedUnit->BoundingRadius())).c_str());
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 20, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 300), Vec4(160, 160, 160, 255), "IsValidObject:");
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 150, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 300), Vec4(255, 255, 255, 255), std::to_string(FocusedUnit->IsValidObject()).c_str());
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 20, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 320), Vec4(160, 160, 160, 255), "IsVisible:");
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 150, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 320), Vec4(255, 255, 255, 255), std::to_string(FocusedUnit->IsVisible()).c_str());
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 20, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 340), Vec4(160, 160, 160, 255), "IsTargetable:");
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 150, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 340), Vec4(255, 255, 255, 255), std::to_string(FocusedUnit->IsTargetable()).c_str());
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 20, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 360), Vec4(160, 160, 160, 255), "IsDead:");
		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 150, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 360), Vec4(255, 255, 255, 255), std::to_string(FocusedUnit->IsDead()).c_str());

		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 20, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 420), Vec4(255, 128, 0, 255), "Buffs:");
		std::vector<void*> buffs;
		FocusedUnit->GetAllBuffsData(buffs);
		auto height = 20;

		for (auto buff : buffs)
		{
			if (GBuffData->IsValid(buff))
			{
				GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + 20, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 420 + height), Vec4(160, 160, 160, 255), "Name: %s | Caster: %s | Count: %d | RemainingTime: %s", GBuffData->GetBuffName(buff), GBuffData->GetCaster(buff)->GetBaseSkinName(), GBuffData->GetStacks(buff), max(0, GBuffData->GetEndTime(buff) - GGame->Time()) > 1000 ? "Infinite" : std::to_string(max(0, GBuffData->GetEndTime(buff) - GGame->Time())).c_str());
				height += 20;
			}
		}

		GRender->DrawTextW(Vec2(GPlugin->GetMenuOption("Main", "Position.X")->GetInteger() + Background->GetSize().x - 185, GPlugin->GetMenuOption("Main", "Position.Y")->GetInteger() + 675), Vec4(255, 128, 0, 255), "SoNiice's dev helper for L++");
	}

	GRender->DrawCircle(FocusedUnit->GetPosition(), FocusedUnit->BoundingRadius(), Vec4(153, 0, 0, 255));
}