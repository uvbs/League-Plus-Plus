#include "Modes.h"
#include "Plugin.h"
#include "Hero.h"
#include "TwistedFate.h"

void Modes::Combo()
{
	if (GHero->GetSpell("W")->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, GEntityList->Player()->AttackRange() + 100);

		if (GEntityList->Player()->IsValidTarget(target, GEntityList->Player()->AttackRange() + 100))
		{
			TwistedFate::CardSelector->StartSelecting(TwistedFate::CardSelector->kCardYellow);
		}
	}
}

void Modes::Always()
{
	if (GetAsyncKeyState(GPlugin->GetMenuOption("W", "Key.Yellow")->GetInteger()))
	{
		TwistedFate::SelectCard(TwistedFate::CardSelector->kCardYellow);
	}

	if (GetAsyncKeyState(GPlugin->GetMenuOption("W", "Key.Blue")->GetInteger()))
	{
		TwistedFate::SelectCard(TwistedFate::CardSelector->kCardBlue);
	}

	if (GetAsyncKeyState(GPlugin->GetMenuOption("W", "Key.Red")->GetInteger()))
	{
		TwistedFate::SelectCard(TwistedFate::CardSelector->kCardRed);
	}

	if (GPlugin->GetMenuOption("Q", "Immobile")->Enabled())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			GHero->GetSpell2("Q")->CastOnTarget(enemy, kHitChanceImmobile);
			break;
		}
	}

	if (GPlugin->GetMenuOption("Q", "Dashing")->Enabled())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			GHero->GetSpell2("Q")->CastOnTarget(enemy, kHitChanceDashing);
			break;
		}
	}

	if (GPlugin->GetMenuOption("R", "Ping")->Enabled() && GHero->GetSpell("R")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			auto damage = GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotQ) * 3 + GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotW);

			if (damage > enemy->GetHealth() && !enemy->IsDead())
			{
				if (GGame->TickCount() - TwistedFate::LastPingTick < 30 * 1000)
					return;

				TwistedFate::LastPingTick = GGame->TickCount();

				GGame->ShowPing(kPingOnMyWay, enemy, true);
			}
		}
	}

	if (GetAsyncKeyState(GPlugin->GetMenuOption("Q", "Key")->GetInteger()) && GHero->GetSpell2("Q")->IsReady())
	{
		GHero->GetSpell2("Q")->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("Q")->Range()), kHitChanceMedium);
	}
}