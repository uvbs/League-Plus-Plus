#include "Modes.h"
#include "Plugin.h"
#include "Hero.h"
#include "TwistedFate.h"

void Modes::Combo()
{
	if (GHero->GetSpell("W")->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, GEntityList->Player()->AttackRange() + 100);

		if (target != nullptr && GEntityList->Player()->IsValidTarget(target, GEntityList->Player()->AttackRange() + 100))
		{
			TwistedFate::SelectCard(TwistedFate::CardSelector->kCardYellow);
		}
	}
}

void Modes::Always()
{
	if (GHero->GetSpell("W")->IsReady())
	{
		if (GetAsyncKeyState(GPlugin->GetMenuInteger("W", "Key.Yellow")))
		{
			TwistedFate::SelectCard(TwistedFate::CardSelector->kCardYellow);
		}

		if (GetAsyncKeyState(GPlugin->GetMenuInteger("W", "Key.Blue")))
		{
			TwistedFate::SelectCard(TwistedFate::CardSelector->kCardBlue);
		}

		if (GetAsyncKeyState(GPlugin->GetMenuInteger("W", "Key.Red")))
		{
			TwistedFate::SelectCard(TwistedFate::CardSelector->kCardRed);
		}
	}

	if (GHero->GetSpell2("Q")->IsReady())
	{
		if (GPlugin->GetMenuBoolean("Q", "Immobile"))
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				GHero->GetSpell2("Q")->CastOnTarget(enemy, kHitChanceImmobile);
				break;
			}
		}

		if (GPlugin->GetMenuBoolean("Q", "Dashing"))
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				GHero->GetSpell2("Q")->CastOnTarget(enemy, kHitChanceDashing);
				break;
			}
		}

		if (GetAsyncKeyState(GPlugin->GetMenuInteger("Q", "Key")))
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, GHero->GetSpell2("Q")->Range());

			if (target != nullptr && GEntityList->Player()->IsValidTarget(target, GHero->GetSpell2("Q")->Range()))
			{
				GHero->GetSpell2("Q")->CastOnTarget(target, kHitChanceHigh);
			}
		}
	}

	if (GPlugin->GetMenuBoolean("R", "Ping") && GHero->GetSpell("R")->IsReady())
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
}