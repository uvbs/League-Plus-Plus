#include "PluginSDK.h"
#include "Riven.h"
#include <string>

auto version = 1;

PluginSetup("SoRiiven");

IPluginSDK* Riven::SDK;
IUnit* Riven::Player;
sMenu* Riven::Menu;

sExtensions* Riven::Extensions = new sExtensions();
sSpells* Riven::Spells = new sSpells();
sLogics* Riven::Logics = new sLogics();

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (!GUtility->IsLeagueWindowFocused())
		return;

	if (GGame->IsChatOpen())
		return;

	Riven::Logics->Q();
	Riven::Logics->W();
	Riven::Logics->E();
	Riven::Logics->R();
}

PLUGIN_EVENT(void) OnRender()
{
	
}

PLUGIN_EVENT(void) OrbwalkBeforeAttack(IUnit* target)
{

}

PLUGIN_EVENT(void) OrbwalkAfterAttack(IUnit* target)
{

}


PLUGIN_EVENT(void) OrbwalkNonKillableMinion(IUnit* minion)
{
	if (Riven::Menu->WUnkillable->Enabled())
	{
		if (Riven::Player->IsValidTarget(minion, Riven::Spells->W->GetSpellRange()))
		{
			if (Riven::SDK->GetDamage()->GetSpellDamage(Riven::Player, minion, kSlotW) > minion->GetHealth())
			{
				Riven::Spells->W->CastOnPlayer();
			}
		}
	}
}

PLUGIN_EVENT(void) OnInterruptible(InterruptibleSpell const& spell)
{
	if (Riven::Menu->WInterrupt->Enabled())
	{
		if (Riven::Player->IsValidTarget(spell.Target, Riven::Spells->W->GetSpellRange()))
		{
			Riven::Spells->W->CastOnPlayer();
		}
	}
}

PLUGIN_EVENT(void) OnGapCloser(GapCloserSpell const& spell)
{
	if (Riven::Menu->WGapCloser->Enabled())
	{
		if (Riven::Player->IsValidTarget(spell.Sender, Riven::Spells->W->GetSpellRange()))
		{
			Riven::Spells->W->CastOnPlayer();
		}
	}
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

	Riven::SDK = PluginSDK;
	Riven::Player = Riven::SDK->GetEntityList()->Player();

	if (strstr(Riven::Player->ChampionName(), "Riven") == nullptr)
	{
		Riven::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>SoRiiven</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">You are not playing <b>Riven</b>!</font>");
		return;
	}

	Riven::Menu = new sMenu(GPluginSDK->AddMenu("SoRiiven"));

	Riven::Spells->Create();
	Riven::Spells->Initialize();

	Riven::SDK->GetEventManager()->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	Riven::SDK->GetEventManager()->AddEventHandler(kEventOnRender, OnRender);
	Riven::SDK->GetEventManager()->AddEventHandler(kEventOrbwalkBeforeAttack, OrbwalkBeforeAttack);
	Riven::SDK->GetEventManager()->AddEventHandler(kEventOrbwalkAfterAttack, OrbwalkAfterAttack);
	Riven::SDK->GetEventManager()->AddEventHandler(kEventOrbwalkNonKillableMinion, OrbwalkNonKillableMinion);
	Riven::SDK->GetEventManager()->AddEventHandler(kEventOnInterruptible, OnInterruptible);
	Riven::SDK->GetEventManager()->AddEventHandler(kEventOnGapCloser, OnGapCloser);
	Riven::SDK->GetEventManager()->AddEventHandler(kEventOnSpellCast, OnSpellCast);
	Riven::SDK->GetEventManager()->AddEventHandler(kEventOnLevelUp, OnLevelUp);

	Riven::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>SoRiiven</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">Loaded</font>");
	sExtensions::CheckVersion("SoRiiven", version);
}

PLUGIN_API void OnUnload()
{
	if (strstr(Riven::Player->ChampionName(), "Riven") != nullptr)
	{
		Riven::Menu->Main->Remove();
	}

	Riven::SDK->GetEventManager()->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	Riven::SDK->GetEventManager()->RemoveEventHandler(kEventOnRender, OnRender);
	Riven::SDK->GetEventManager()->RemoveEventHandler(kEventOrbwalkBeforeAttack, OrbwalkBeforeAttack);
	Riven::SDK->GetEventManager()->RemoveEventHandler(kEventOrbwalkAfterAttack, OrbwalkAfterAttack);
	Riven::SDK->GetEventManager()->RemoveEventHandler(kEventOrbwalkNonKillableMinion, OrbwalkNonKillableMinion);
	Riven::SDK->GetEventManager()->RemoveEventHandler(kEventOnInterruptible, OnInterruptible);
	Riven::SDK->GetEventManager()->RemoveEventHandler(kEventOnGapCloser, OnGapCloser);
	Riven::SDK->GetEventManager()->RemoveEventHandler(kEventOnSpellCast, OnSpellCast);
	Riven::SDK->GetEventManager()->RemoveEventHandler(kEventOnLevelUp, OnLevelUp);

	Riven::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>SoRiiven</b></font> - <font color=\"#FFFFFF\">Unloaded</font>");
}