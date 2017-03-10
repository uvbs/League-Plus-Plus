#include "PluginSDK.h"
#include "LeeSin.h"
#include <string>

PluginSetup("SoLeeSiin");

IPluginSDK* LeeSin::SDK;
IUnit* LeeSin::Player;
sMenu* LeeSin::Menu;

sExtensions* LeeSin::Extensions = new sExtensions();
sSpells* LeeSin::Spells = new sSpells();
sLogics* LeeSin::Logics = new sLogics();

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (!GUtility->IsLeagueWindowFocused())
		return;

	if (GGame->IsChatOpen())
		return;

	LeeSin::Logics->Q();
	LeeSin::Logics->W();
	LeeSin::Logics->E();
	LeeSin::Logics->R();
}

PLUGIN_EVENT(void) OnRender()
{
	if (LeeSin::Menu->DrawQ->Enabled())
	{
		if (LeeSin::Menu->DrawReady->Enabled() && LeeSin::Spells->Q->IsReady() || !LeeSin::Menu->DrawReady->Enabled())
		{
			LeeSin::SDK->GetRenderer()->DrawOutlinedCircle(LeeSin::Player->GetPosition(), Vec4(255, 255, 0, 255), LeeSin::Spells->Q->Range());
		}
	}

	if (LeeSin::Menu->DrawW->Enabled())
	{
		if (LeeSin::Menu->DrawReady->Enabled() && LeeSin::Spells->W->IsReady() || !LeeSin::Menu->DrawReady->Enabled())
		{
			LeeSin::SDK->GetRenderer()->DrawOutlinedCircle(LeeSin::Player->GetPosition(), Vec4(255, 255, 0, 255), LeeSin::Spells->W->GetSpellRange());
		}
	}

	if (LeeSin::Menu->DrawE->Enabled())
	{
		if (LeeSin::Menu->DrawReady->Enabled() && LeeSin::Spells->E->IsReady() || !LeeSin::Menu->DrawReady->Enabled())
		{
			LeeSin::SDK->GetRenderer()->DrawOutlinedCircle(LeeSin::Player->GetPosition(), Vec4(255, 255, 0, 255), LeeSin::Spells->E->GetSpellRange());
		}
	}

	if (LeeSin::Menu->DrawR->Enabled())
	{
		if (LeeSin::Menu->DrawReady->Enabled() && LeeSin::Spells->R->IsReady() || !LeeSin::Menu->DrawReady->Enabled())
		{
			LeeSin::SDK->GetRenderer()->DrawOutlinedCircle(LeeSin::Player->GetPosition(), Vec4(255, 255, 0, 255), LeeSin::Spells->R->GetSpellRange());
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

	LeeSin::SDK = PluginSDK;
	LeeSin::Player = LeeSin::SDK->GetEntityList()->Player();

	if (strstr(LeeSin::Player->ChampionName(), "LeeSin") == nullptr)
	{
		LeeSin::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>SoLeeSiin</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">You are not playing <b>LeeSin</b>!</font>");
		return;
	}

	LeeSin::Menu = new sMenu(GPluginSDK->AddMenu("SoLeeSiin"));

	LeeSin::Spells->Create();
	LeeSin::Spells->Initialize();

	LeeSin::SDK->GetEventManager()->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	LeeSin::SDK->GetEventManager()->AddEventHandler(kEventOnRender, OnRender);
	LeeSin::SDK->GetEventManager()->AddEventHandler(kEventOrbwalkBeforeAttack, OrbwalkBeforeAttack);
	LeeSin::SDK->GetEventManager()->AddEventHandler(kEventOrbwalkAfterAttack, OrbwalkAfterAttack);
	LeeSin::SDK->GetEventManager()->AddEventHandler(kEventOnGapCloser, OnGapCloser);
	LeeSin::SDK->GetEventManager()->AddEventHandler(kEventOnLevelUp, OnLevelUp);

	LeeSin::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>SoLeeSiin</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">Loaded</font>");
}

PLUGIN_API void OnUnload()
{
	if (strstr(LeeSin::Player->ChampionName(), "LeeSin") != nullptr)
	{
		LeeSin::Menu->Main->Remove();
	}

	LeeSin::SDK->GetEventManager()->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	LeeSin::SDK->GetEventManager()->RemoveEventHandler(kEventOnRender, OnRender);
	LeeSin::SDK->GetEventManager()->RemoveEventHandler(kEventOrbwalkBeforeAttack, OrbwalkBeforeAttack);
	LeeSin::SDK->GetEventManager()->RemoveEventHandler(kEventOrbwalkAfterAttack, OrbwalkAfterAttack);
	LeeSin::SDK->GetEventManager()->RemoveEventHandler(kEventOnGapCloser, OnGapCloser);
	LeeSin::SDK->GetEventManager()->RemoveEventHandler(kEventOnLevelUp, OnLevelUp);

	LeeSin::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>SoLeeSiin</b></font> - <font color=\"#FFFFFF\">Unloaded</font>");
}