#include "PluginSDK.h"
#include "Kalista.h"
#include <string>
#include <array>

PluginSetup("SoKaliista");

IPluginSDK* Kalista::SDK;
IUnit* Kalista::Player;
sMenu* Kalista::Menu;

sExtensions* Kalista::Extensions = new sExtensions();
sSpells* Kalista::Spells = new sSpells();
sLogics* Kalista::Logics = new sLogics();

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (!GUtility->IsLeagueWindowFocused())
		return;

	if (GGame->IsChatOpen())
		return;

	Kalista::Logics->Q();
	Kalista::Logics->W();
	Kalista::Logics->E();
	Kalista::Logics->R();
}

PLUGIN_EVENT(void) OnRender()
{
	if (Kalista::Menu->DrawQ->Enabled())
	{
		if (Kalista::Menu->DrawReady->Enabled() && Kalista::Spells->Q->IsReady() || !Kalista::Menu->DrawReady->Enabled())
		{
			Kalista::SDK->GetRenderer()->DrawOutlinedCircle(Kalista::Player->GetPosition(), Vec4(255, 255, 0, 255), Kalista::Spells->Q->Range());
		}
	}

	if (Kalista::Menu->DrawW->Enabled())
	{
		if (Kalista::Menu->DrawReady->Enabled() && Kalista::Spells->W->IsReady() || !Kalista::Menu->DrawReady->Enabled())
		{
			Kalista::SDK->GetRenderer()->DrawOutlinedCircle(Kalista::Player->GetPosition(), Vec4(255, 255, 0, 255), Kalista::Spells->W->GetSpellRange());
		}
	}

	if (Kalista::Menu->DrawE->Enabled())
	{
		if (Kalista::Menu->DrawReady->Enabled() && Kalista::Spells->E->IsReady() || !Kalista::Menu->DrawReady->Enabled())
		{
			Kalista::SDK->GetRenderer()->DrawOutlinedCircle(Kalista::Player->GetPosition(), Vec4(255, 255, 0, 255), Kalista::Spells->E->GetSpellRange());
		}
	}

	if (Kalista::Menu->DrawEDamage->Enabled())
	{
		if (Kalista::Menu->DrawReady->Enabled() && Kalista::Spells->E->IsReady() || !Kalista::Menu->DrawReady->Enabled())
		{
			for (auto enemy : Kalista::SDK->GetEntityList()->GetAllHeros(false, true))
			{
				if (Kalista::Extensions->GetDistance(Kalista::Player, enemy) <= Kalista::Spells->E->GetSpellRange())
				{
					if (enemy->HasBuff("kalistaexpungemarker") && !enemy->IsDead())
					{
						Vec3 worldToScreen;
						Kalista::SDK->GetGame()->Projection(enemy->GetPosition(), &worldToScreen);
						
						auto eDamage = Kalista::SDK->GetDamage()->GetSpellDamage(Kalista::Player, enemy, kSlotE);
						auto eDamageText = "E Damage: " + std::to_string(eDamage);
						auto barPosition = Vec2();
												
						Kalista::SDK->GetRenderer()->DrawTextW(Vec2(worldToScreen.x - 45, worldToScreen.y + 45), Vec4(255, 255, 255, 255), eDamageText.c_str());

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
								Kalista::SDK->GetRenderer()->DrawLine(Vec2(pos1 + i, yPos), Vec2(pos1 + i, yPos + 8), Vec4(105, 198, 5, 255));
							}

							if (eDamage > enemy->GetHealth())
							{
								Kalista::SDK->GetRenderer()->DrawTextW(Vec2(barPosition.x + 10, barPosition.y + 7), Vec4(255, 255, 255, 255), "Killable");
							}
						}
					}
				}
			}
		}
	}

	if (Kalista::Menu->DrawR->Enabled())
	{
		if (Kalista::Menu->DrawReady->Enabled() && Kalista::Spells->R->IsReady() || !Kalista::Menu->DrawReady->Enabled())
		{
			Kalista::SDK->GetRenderer()->DrawOutlinedCircle(Kalista::Player->GetPosition(), Vec4(255, 255, 0, 255), Kalista::Spells->R->GetSpellRange());
		}
	}
}

PLUGIN_EVENT(void) OrbwalkNonKillableMinion(IUnit* minion)
{
	if (Kalista::Menu->ELastHitUnkillable->Enabled())
	{
		if (minion->IsValidTarget())
		{
			if (minion->HasBuff("kalistaexpungemarker"))
			{
				if (Kalista::SDK->GetDamage()->GetSpellDamage(Kalista::Player, minion, kSlotE) > minion->GetHealth())
				{
					Kalista::Spells->E->CastOnPlayer();
				}
			}
		}
	}
}

PLUGIN_EVENT(void) OnLevelUp(IUnit* source, int level)
{
	switch (level)
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

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	PluginSDKSetup(PluginSDK);

	Kalista::SDK = PluginSDK;
	Kalista::Player = Kalista::SDK->GetEntityList()->Player();

	if (strstr(Kalista::Player->ChampionName(), "Kalista") == nullptr)
	{
		Kalista::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>SoKaliista</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">You are not playing <b>Kalista</b>!</font>");
		return;
	}
	Kalista::Menu = new sMenu(GPluginSDK->AddMenu("SoKaliista"));

	Kalista::Spells->Create();
	Kalista::Spells->Initialize();

	Kalista::SDK->GetEventManager()->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	Kalista::SDK->GetEventManager()->AddEventHandler(kEventOnRender, OnRender);
	Kalista::SDK->GetEventManager()->AddEventHandler(kEventOrbwalkNonKillableMinion, OrbwalkNonKillableMinion);
	Kalista::SDK->GetEventManager()->AddEventHandler(kEventOnLevelUp, OnLevelUp);

	Kalista::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>SoKaliista</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">Loaded</font>");
}

PLUGIN_API void OnUnload()
{
	if (strstr(Kalista::Player->ChampionName(), "Kalista") != nullptr)
	{
		Kalista::Menu->Main->Remove();
	}

	Kalista::SDK->GetEventManager()->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	Kalista::SDK->GetEventManager()->RemoveEventHandler(kEventOnRender, OnRender);
	Kalista::SDK->GetEventManager()->RemoveEventHandler(kEventOrbwalkNonKillableMinion, OrbwalkNonKillableMinion);
	Kalista::SDK->GetEventManager()->RemoveEventHandler(kEventOnLevelUp, OnLevelUp);

	Kalista::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>SoKaliista</b></font> - <font color=\"#FFFFFF\">Unloaded</font>");
}