#include "PluginSDK.h"
#include "Aatrox.h"
#include <string>

auto version = 1;

PluginSetup("NiiceAatrox");

IPluginSDK* Aatrox::SDK;
IUnit* Aatrox::Player;
sMenu* Aatrox::Menu;

sExtensions* Aatrox::Extensions = new sExtensions();
sSpells* Aatrox::Spells = new sSpells();
sLogics* Aatrox::Logics = new sLogics();

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (!GUtility->IsLeagueWindowFocused())
		return;

	if (GGame->IsChatOpen())
		return;

	if (GetAsyncKeyState(Aatrox::Menu->MiscFleeKey->GetInteger()))
	{
		Aatrox::SDK->GetGame()->IssueOrder(Aatrox::Player, kMoveTo, Aatrox::SDK->GetGame()->CursorPosition());
	}

	Aatrox::Logics->Q();
	Aatrox::Logics->W();
	Aatrox::Logics->E();
	Aatrox::Logics->R();
}

PLUGIN_EVENT(void) OnRender()
{
	if (Aatrox::Menu->DrawQ->Enabled())
	{
		if (Aatrox::Menu->DrawReady->Enabled() && Aatrox::Spells->Q->IsReady() || !Aatrox::Menu->DrawReady->Enabled())
		{
			Aatrox::SDK->GetRenderer()->DrawOutlinedCircle(Aatrox::Player->GetPosition(), Vec4(255, 255, 0, 255), Aatrox::Spells->Q->Range());
		}
	}

	if (Aatrox::Menu->DrawE->Enabled())
	{
		if (Aatrox::Menu->DrawReady->Enabled() && Aatrox::Spells->E->IsReady() || !Aatrox::Menu->DrawReady->Enabled())
		{
			Aatrox::SDK->GetRenderer()->DrawOutlinedCircle(Aatrox::Player->GetPosition(), Vec4(255, 255, 0, 255), Aatrox::Spells->E->Range());
		}
	}

	if (Aatrox::Menu->DrawR->Enabled())
	{
		if (Aatrox::Menu->DrawReady->Enabled() && Aatrox::Spells->R->IsReady() || !Aatrox::Menu->DrawReady->Enabled())
		{
			Aatrox::SDK->GetRenderer()->DrawOutlinedCircle(Aatrox::Player->GetPosition(), Vec4(255, 255, 0, 255), Aatrox::Spells->R->GetSpellRange());
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

	Aatrox::SDK = PluginSDK;
	Aatrox::Player = Aatrox::SDK->GetEntityList()->Player();

	if (strstr(Aatrox::Player->ChampionName(), "Aatrox") == nullptr)
	{
		Aatrox::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>NiiceAatrox</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">You are not playing <b>Aatrox</b>!</font>");
		return;
	}

	Aatrox::Menu = new sMenu(GPluginSDK->AddMenu("NiiceAatrox"));

	Aatrox::Spells->Create();
	Aatrox::Spells->Initialize();

	Aatrox::SDK->GetEventManager()->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	Aatrox::SDK->GetEventManager()->AddEventHandler(kEventOnRender, OnRender);
	Aatrox::SDK->GetEventManager()->AddEventHandler(kEventOrbwalkBeforeAttack, OrbwalkBeforeAttack);
	Aatrox::SDK->GetEventManager()->AddEventHandler(kEventOrbwalkAfterAttack, OrbwalkAfterAttack);
	Aatrox::SDK->GetEventManager()->AddEventHandler(kEventOnGapCloser, OnGapCloser);
	Aatrox::SDK->GetEventManager()->AddEventHandler(kEventOnSpellCast, OnSpellCast);
	Aatrox::SDK->GetEventManager()->AddEventHandler(kEventOnLevelUp, OnLevelUp);

	Aatrox::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>NiiceAatrox</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">Loaded</font>");
	sExtensions::CheckVersion("NiiceAatrox", version);
}

PLUGIN_API void OnUnload()
{
	if (strstr(Aatrox::Player->ChampionName(), "Aatrox") != nullptr)
	{
		Aatrox::Menu->Main->Remove();
	}

	Aatrox::SDK->GetEventManager()->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	Aatrox::SDK->GetEventManager()->RemoveEventHandler(kEventOnRender, OnRender);
	Aatrox::SDK->GetEventManager()->RemoveEventHandler(kEventOrbwalkBeforeAttack, OrbwalkBeforeAttack);
	Aatrox::SDK->GetEventManager()->RemoveEventHandler(kEventOrbwalkAfterAttack, OrbwalkAfterAttack);
	Aatrox::SDK->GetEventManager()->RemoveEventHandler(kEventOnGapCloser, OnGapCloser);
	Aatrox::SDK->GetEventManager()->RemoveEventHandler(kEventOnSpellCast, OnSpellCast);
	Aatrox::SDK->GetEventManager()->RemoveEventHandler(kEventOnLevelUp, OnLevelUp);

	Aatrox::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>NiiceAatrox</b></font> - <font color=\"#FFFFFF\">Unloaded</font>");
}