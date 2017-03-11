#include "PluginSDK.h"
#include "TwistedFate.h"
#include <string>

PluginSetup("SoTwiistedFate");

IPluginSDK* TwistedFate::SDK;
IUnit* TwistedFate::Player;
sMenu* TwistedFate::Menu;

int TwistedFate::LastPingTick;
int TwistedFate::CardPickTick;

sExtensions* TwistedFate::Extensions = new sExtensions();
sSpells* TwistedFate::Spells = new sSpells();
sLogics* TwistedFate::Logics = new sLogics();
sCardSelector* TwistedFate::CardSelector = new sCardSelector();

int sCardSelector::Select = kCardNone;
int sCardSelector::Status = kReady;

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (!GUtility->IsLeagueWindowFocused())
		return;

	if (GGame->IsChatOpen())
		return;

	TwistedFate::CardSelector->OnGameUpdate();

	TwistedFate::Logics->Q();
	TwistedFate::Logics->W();

	if (TwistedFate::Menu->RPing->Enabled() && TwistedFate::Spells->R->IsReady() && TwistedFate::Player->GetLevel() >= 6)
	{
		for (auto enemy : TwistedFate::SDK->GetEntityList()->GetAllHeros(false, true))
		{
			auto damage = TwistedFate::SDK->GetDamage()->GetSpellDamage(TwistedFate::Player, enemy, kSlotQ) * 3 + TwistedFate::SDK->GetDamage()->GetSpellDamage(TwistedFate::Player, enemy, kSlotW);

			if (damage > enemy->GetHealth() && !enemy->IsDead())
			{
				if (TwistedFate::SDK->GetGame()->TickCount() - TwistedFate::LastPingTick < 30 * 1000)
					return;

				TwistedFate::LastPingTick = TwistedFate::SDK->GetGame()->TickCount();

				TwistedFate::SDK->GetGame()->ShowPing(kPingOnMyWay, enemy, true);
			}
		}
	}
}

PLUGIN_EVENT(void) OnRender()
{
	if (TwistedFate::Menu->DrawQ->Enabled())
	{
		if (TwistedFate::Menu->DrawReady->Enabled() && TwistedFate::Spells->Q->IsReady() || !TwistedFate::Menu->DrawReady->Enabled())
		{
			TwistedFate::SDK->GetRenderer()->DrawOutlinedCircle(TwistedFate::Player->GetPosition(), Vec4(255, 255, 0, 255), TwistedFate::Spells->Q->Range());
		}
	}


	if (TwistedFate::Menu->DrawR->Enabled())
	{
		if (TwistedFate::Menu->DrawReady->Enabled() && TwistedFate::Spells->R->IsReady() || !TwistedFate::Menu->DrawReady->Enabled())
		{
			TwistedFate::SDK->GetRenderer()->DrawOutlinedCircle(TwistedFate::Player->GetPosition(), Vec4(255, 255, 0, 255), TwistedFate::Spells->R->GetSpellRange());
		}
	}
}

PLUGIN_EVENT(void) OrbwalkBeforeAttack(IUnit* target)
{
	
}

PLUGIN_EVENT(void) OrbwalkAfterAttack(IUnit* target)
{

}

PLUGIN_EVENT(void) OnGapCloser(GapCloserSpell const& spell)
{

}

PLUGIN_EVENT(void) OnSpellCast(CastedSpell const& spell)
{
	if (spell.Caster_ != TwistedFate::Player)
		return;

	TwistedFate::CardSelector->OnSpellCast(spell);

	if (strstr(spell.Name_, "Gate") != nullptr && TwistedFate::Menu->WAutoYellowR->Enabled())
	{
		TwistedFate::CardSelector->StartSelecting(sCardSelector::kCardYellow);
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

	TwistedFate::SDK = PluginSDK;
	TwistedFate::Player = TwistedFate::SDK->GetEntityList()->Player();

	if (strstr(TwistedFate::Player->ChampionName(), "TwistedFate") == nullptr)
	{
		TwistedFate::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>SoTwiistedFate</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">You are not playing <b>TwistedFate</b>!</font>");
		return;
	}
	
	TwistedFate::LastPingTick = 0;
	TwistedFate::CardPickTick = 0;

	TwistedFate::Menu = new sMenu(GPluginSDK->AddMenu("SoTwiistedFate"));

	TwistedFate::Spells->Create();
	TwistedFate::Spells->Initialize();

	TwistedFate::SDK->GetEventManager()->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	TwistedFate::SDK->GetEventManager()->AddEventHandler(kEventOnRender, OnRender);
	TwistedFate::SDK->GetEventManager()->AddEventHandler(kEventOrbwalkBeforeAttack, OrbwalkBeforeAttack);
	TwistedFate::SDK->GetEventManager()->AddEventHandler(kEventOrbwalkAfterAttack, OrbwalkAfterAttack);
	TwistedFate::SDK->GetEventManager()->AddEventHandler(kEventOnGapCloser, OnGapCloser);
	TwistedFate::SDK->GetEventManager()->AddEventHandler(kEventOnSpellCast, OnSpellCast);
	TwistedFate::SDK->GetEventManager()->AddEventHandler(kEventOnLevelUp, OnLevelUp);

	TwistedFate::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>SoTwiistedFate</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">Loaded</font>");
}

PLUGIN_API void OnUnload()
{
	if (strstr(TwistedFate::Player->ChampionName(), "TwistedFate") != nullptr)
	{
		TwistedFate::Menu->Main->Remove();
	}

	TwistedFate::SDK->GetEventManager()->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	TwistedFate::SDK->GetEventManager()->RemoveEventHandler(kEventOnRender, OnRender);
	TwistedFate::SDK->GetEventManager()->RemoveEventHandler(kEventOrbwalkBeforeAttack, OrbwalkBeforeAttack);
	TwistedFate::SDK->GetEventManager()->RemoveEventHandler(kEventOrbwalkAfterAttack, OrbwalkAfterAttack);
	TwistedFate::SDK->GetEventManager()->RemoveEventHandler(kEventOnGapCloser, OnGapCloser);
	TwistedFate::SDK->GetEventManager()->RemoveEventHandler(kEventOnSpellCast, OnSpellCast);
	TwistedFate::SDK->GetEventManager()->RemoveEventHandler(kEventOnLevelUp, OnLevelUp);

	TwistedFate::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>SoTwiistedFate</b></font> - <font color=\"#FFFFFF\">Unloaded</font>");
}