#include "PluginSDK.h";
#include "Jinx.h"
#include <algorithm>
#include <string>

PluginSetup("SoJiinx");

IPluginSDK* Jinx::SDK;
IUnit* Jinx::Player;
sMenu* Jinx::Menu;

sExtensions* Jinx::Extensions = new sExtensions();
sSpells* Jinx::Spells = new sSpells();
sLogics* Jinx::Logics = new sLogics();

std::vector<std::string> Jinx::SpecialSpells = std::vector<std::string>();

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (!GUtility->IsLeagueWindowFocused())
		return;

	if (GGame->IsChatOpen())
		return;

	Jinx::Logics->Q();
	Jinx::Logics->W();
	Jinx::Logics->E();
	Jinx::Logics->R();
}

PLUGIN_EVENT(void) OnRender()
{
	if (Jinx::Menu->DrawW->Enabled())
	{
		if (Jinx::Menu->DrawReady->Enabled() && Jinx::Spells->W->IsReady() || !Jinx::Menu->DrawReady->Enabled())
		{
			Jinx::SDK->GetRenderer()->DrawOutlinedCircle(Jinx::Player->GetPosition(), Vec4(255, 255, 0, 255), Jinx::Spells->W->Range());
		}
	}

	if (Jinx::Menu->DrawE->Enabled())
	{
		if (Jinx::Menu->DrawReady->Enabled() && Jinx::Spells->E->IsReady() || !Jinx::Menu->DrawReady->Enabled())
		{
			Jinx::SDK->GetRenderer()->DrawOutlinedCircle(Jinx::Player->GetPosition(), Vec4(255, 255, 0, 255), Jinx::Spells->E->Range());
		}
	}

	if (Jinx::Menu->DrawR->Enabled())
	{
		if (Jinx::Menu->DrawReady->Enabled() && Jinx::Spells->R->IsReady() || !Jinx::Menu->DrawReady->Enabled())
		{
			Jinx::SDK->GetRenderer()->DrawOutlinedCircle(Jinx::Player->GetPosition(), Vec4(255, 255, 0, 255), Jinx::Spells->R->Range());
		}
	}
}

PLUGIN_EVENT(void) OrbwalkBeforeAttack(IUnit* target)
{
	if (!Jinx::HasFishbone())
		return;

	if (Jinx::Spells->Q->IsReady() && target->IsHero())
	{
		Jinx::FishboneToMinigun(target);
	}

	if (!Jinx::Extensions->IsComboing() && target->IsCreep())
	{
		if (Jinx::Extensions->IsClearing() && Jinx::Player->ManaPercent() > Jinx::Menu->ManaQClear->GetInteger() && Jinx::Extensions->CountMinionsInTargetRange(target, 250) + 1 >= Jinx::Menu->QMinions->GetInteger())
		{

		}
		else if (Jinx::Extensions->GetRealDistance(Jinx::Player, target) < Jinx::GetRealPowPowRange(target))
		{
			Jinx::SDK->GetOrbwalking()->DisableNextAttack();

			if (Jinx::Spells->Q->IsReady())
			{
				Jinx::Spells->Q->CastOnPlayer();
			}
		}
	}
}

PLUGIN_EVENT(void) OnGapCloser(GapCloserSpell const& spell)
{
	if (!Jinx::Spells->E->IsReady())
		return;

	if (!Jinx::Menu->EGapCloser->Enabled())
		return;

	if (Jinx::Player->ManaPercent() < Jinx::Menu->ManaE->GetInteger())
		return;

	if (!Jinx::Player->IsValidTarget(spell.Sender, Jinx::Spells->E->Range()))
		return;

	Jinx::Spells->E->CastOnPosition(spell.EndPosition);
}

PLUGIN_EVENT(void) OnSpellCast(CastedSpell const& spell)
{
	if (!spell.Caster_->IsHero())
		return;

	if (!spell.Caster_->IsEnemy(Jinx::Player))
		return;

	if (!Jinx::Spells->E->IsReady())
		return;

	if (!Jinx::Menu->ESpecialSpell->Enabled())
		return;

	if (Jinx::Player->ManaPercent() < Jinx::Menu->ManaE->GetInteger())
		return;

	if (!Jinx::Player->IsValidTarget(spell.Caster_, Jinx::Spells->E->Range()))
		return;

	auto spellName = std::string(spell.Name_);
	std::transform(spellName.begin(), spellName.end(), spellName.begin(), ::tolower);

	if (find(Jinx::SpecialSpells.begin(), Jinx::SpecialSpells.end(), spellName.c_str()) != Jinx::SpecialSpells.end())
	{
		Jinx::Spells->E->CastOnPosition(spell.Caster_->GetPosition());
	}
}

PLUGIN_EVENT(void) OnLevelUp(IUnit* source, int level)
{
	switch(level) 
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

	Jinx::SDK = PluginSDK;
	Jinx::Player = Jinx::SDK->GetEntityList()->Player();

	if (strstr(Jinx::Player->ChampionName(), "Jinx") == nullptr)
	{
		Jinx::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>SoJiinx</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">You are not playing <b>Jinx</b>!</font>");
		return;
	}

	Jinx::Menu = new sMenu(GPluginSDK->AddMenu("SoJiinx"));

	Jinx::Spells->Create();
	Jinx::Spells->Initialize();

	Jinx::GetSpecialSpells();

	Jinx::SDK->GetEventManager()->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	Jinx::SDK->GetEventManager()->AddEventHandler(kEventOnRender, OnRender);
	Jinx::SDK->GetEventManager()->AddEventHandler(kEventOrbwalkBeforeAttack, OrbwalkBeforeAttack);
	Jinx::SDK->GetEventManager()->AddEventHandler(kEventOnGapCloser, OnGapCloser);
	Jinx::SDK->GetEventManager()->AddEventHandler(kEventOnSpellCast, OnSpellCast);
	Jinx::SDK->GetEventManager()->AddEventHandler(kEventOnLevelUp, OnLevelUp);

	Jinx::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>SoJiinx</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">Loaded</font>");
}

PLUGIN_API void OnUnload()
{
	if (strstr(Jinx::Player->ChampionName(), "Jinx") != nullptr)
	{
		Jinx::Menu->Main->Remove();
	}

	Jinx::SDK->GetEventManager()->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	Jinx::SDK->GetEventManager()->RemoveEventHandler(kEventOnRender, OnRender);
	Jinx::SDK->GetEventManager()->RemoveEventHandler(kEventOrbwalkBeforeAttack, OrbwalkBeforeAttack);
	Jinx::SDK->GetEventManager()->RemoveEventHandler(kEventOnGapCloser, OnGapCloser);
	Jinx::SDK->GetEventManager()->RemoveEventHandler(kEventOnSpellCast, OnSpellCast);
	Jinx::SDK->GetEventManager()->RemoveEventHandler(kEventOnLevelUp, OnLevelUp);

	Jinx::SDK->GetGame()->PrintChat("<font color=\"#0095DA\"><b>SoJiinx</b></font> - <font color=\"#FFFFFF\">Unloaded</font>");
}