#include "Events.h"
#include "Plugin.h"
#include "Hero.h"
#include "Modes.h"
#include "Extension.h"
#include <string>

void Events::Initialize()
{
	GPlugin->RegisterGameUpdateEvent(OnGameUpdate);
	GPlugin->RegisterRenderEvent(OnRender);
	GPlugin->RegisterOrbwalkNonKillableMinionEvent(OnOrbwalkNonKillableMinion);
	GPlugin->RegisterLevelUpEvent(OnLevelUp);
}

void Events::OnGameUpdate()
{
	if (!GUtility->IsLeagueWindowFocused())
		return;

	if (GGame->IsChatOpen())
		return;

	if (GExtension->IsComboing())
	{
		Modes::Combo();
	}

	if (GExtension->IsHarassing())
	{
		Modes::Harass();
	}

	if (GExtension->IsClearing())
	{
		Modes::Clear();
		Modes::Jungle();
	}

	Modes::Always();
	Modes::KillSteal();
}

void Events::OnRender()
{
	if (GPlugin->GetMenuOption("Drawings", "Q")->Enabled() && GHero->GetSpell2("Q")->IsReady() || !GPlugin->GetMenuOption("Drawings", "Ready")->Enabled())
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), GHero->GetSpell2("Q")->Range());
	}

	if (GPlugin->GetMenuOption("Drawings", "W")->Enabled() && GHero->GetSpell("W")->IsReady() || !GPlugin->GetMenuOption("Drawings", "Ready")->Enabled())
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), GHero->GetSpell("W")->GetSpellRange());
	}

	if (GPlugin->GetMenuOption("Drawings", "E")->Enabled() && GHero->GetSpell("E")->IsReady() || !GPlugin->GetMenuOption("Drawings", "Ready")->Enabled())
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), GHero->GetSpell("E")->GetSpellRange());
	}

	if (GPlugin->GetMenuOption("Drawings", "E.Damage")->Enabled() && GHero->GetSpell("E")->IsReady() || !GPlugin->GetMenuOption("Drawings", "Ready")->Enabled())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (GExtension->GetDistance(GEntityList->Player(), enemy) <= GHero->GetSpell("E")->GetSpellRange() && enemy->HasBuff("kalistaexpungemarker") && !enemy->IsDead())
			{
				Vec3 worldToScreen;
				GGame->Projection(enemy->GetPosition(), &worldToScreen);

				auto eDamage = GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotE);
				auto eDamagePercent = eDamage / enemy->GetHealth() * 100;
				auto barPosition = Vec2();

				GRender->DrawTextW(Vec2(worldToScreen.x - 45, worldToScreen.y + 45), Vec4(255, 255, 255, 255), "E Damage: %f (%f%%)", eDamage, eDamagePercent);

				if (enemy->GetHPBarPosition(barPosition))
				{
					auto healthPercent = max(0, enemy->GetHealth() - eDamage) / enemy->GetMaxHealth();
					auto yPos = barPosition.y + 10;
					auto xPosDamage = barPosition.x + 10 + 103 * healthPercent;
					auto xPosCurrentHp = barPosition.x + 10 + 103 * enemy->GetHealth() / enemy->GetMaxHealth();

					float differenceInHP = xPosCurrentHp - xPosDamage;
					float pos1 = barPosition.x + 9 + (107 * healthPercent);

					for (auto i = 0; i < differenceInHP; i++)
					{
						GRender->DrawLine(Vec2(pos1 + i, yPos), Vec2(pos1 + i, yPos + 8), Vec4(105, 198, 5, 255));
					}

					if (eDamage > enemy->GetHealth())
					{
						GRender->DrawTextW(Vec2(barPosition.x + 10, barPosition.y + 7), Vec4(255, 255, 255, 255), "Killable");
					}
				}
			}
		}
	}

	if (GPlugin->GetMenuOption("Drawings", "R")->Enabled() && GHero->GetSpell("R")->IsReady() || !GPlugin->GetMenuOption("Drawings", "Ready")->Enabled())
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), GHero->GetSpell("R")->GetSpellRange());
	}
}

void Events::OnOrbwalkNonKillableMinion(IUnit* minion)
{
	if (GPlugin->GetMenuOption("E", "Lasthit.Unkillable")->Enabled() && GHero->GetSpell("E")->IsReady() && GEntityList->Player()->IsValidTarget(minion, GHero->GetSpell("E")->GetSpellRange()) && minion->HasBuff("kalistaexpungemarker") && GDamage->GetSpellDamage(GEntityList->Player(), minion, kSlotE) > minion->GetHealth())
	{
		GHero->GetSpell("E")->CastOnPlayer();
	}
}

void Events::OnLevelUp(IUnit* source, int newLevel)
{
	switch (newLevel)
	{
	case 6:
	case 11:
	case 16:
		source->LevelUpSpell(kSlotR);
		break;
	default:
		break;
	}
}
