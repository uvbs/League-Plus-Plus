#include "TwistedFate.h"

void sLogics::Q()
{
	for (auto enemy : TwistedFate::SDK->GetEntityList()->GetAllHeros(false, true))
	{
		if (TwistedFate::Menu->QImmobile->Enabled())
		{
			TwistedFate::Spells->Q->CastOnTarget(enemy, kHitChanceImmobile);
		}

		if (TwistedFate::Menu->QDashing->Enabled())
		{
			TwistedFate::Spells->Q->CastOnTarget(enemy, kHitChanceDashing);
		}
	}

	if (GetAsyncKeyState(TwistedFate::Menu->QSemiManual->GetInteger()))
	{
		auto target = TwistedFate::SDK->CreateTargetSelector()->FindTarget(QuickestKill, SpellDamage, TwistedFate::Spells->Q->Range());

		if (TwistedFate::Player->IsValidTarget(target, TwistedFate::Spells->Q->Range()))
		{
			TwistedFate::Spells->Q->CastOnTarget(target, kHitChanceHigh);
		}
	}
}

void sLogics::W()
{
	if (TwistedFate::Extensions->IsComboing())
	{
		auto target = TwistedFate::SDK->CreateTargetSelector()->FindTarget(QuickestKill, SpellDamage, TwistedFate::Player->AttackRange() + 100);

		if (TwistedFate::Player->IsValidTarget(target, TwistedFate::Player->AttackRange() + 100))
		{
			TwistedFate::CardSelector->StartSelecting(sCardSelector::kCardYellow);
		}
	}

	if (GetAsyncKeyState(TwistedFate::Menu->WSelectYellow->GetInteger()))
	{
		TwistedFate::SelectCard(TwistedFate::CardSelector->kCardYellow);
	}

	if (GetAsyncKeyState(TwistedFate::Menu->WSelectBlue->GetInteger()))
	{
		TwistedFate::SelectCard(TwistedFate::CardSelector->kCardBlue);
	}

	if (GetAsyncKeyState(TwistedFate::Menu->WSelectRed->GetInteger()))
	{
		TwistedFate::SelectCard(TwistedFate::CardSelector->kCardRed);
	}
}