#include "TwistedFate.h"

void sCardSelector::StartSelecting(int card)
{
	if (strstr(TwistedFate::Player->GetSpellBook()->GetName(kSlotW), "PickACard") != nullptr && Status == kReady)
	{
		Select = card;

		if (TwistedFate::SDK->GetGame()->TickCount() - TwistedFate::CardPickTick > 100 + TwistedFate::SDK->GetGame()->Latency() / 2)
		{
			TwistedFate::Spells->W->CastOnPlayer();
			TwistedFate::CardPickTick = TwistedFate::SDK->GetGame()->TickCount();
		}
	}
}

void sCardSelector::OnGameUpdate()
{
	if (TwistedFate::Player->GetSpellBook()->GetSpellState(kSlotW) == Ready && strstr(TwistedFate::Player->GetSpellBook()->GetName(kSlotW), "PickACard") != nullptr && (Status != kSelecting || TwistedFate::SDK->GetGame()->TickCount() - TwistedFate::CardPickTick > 500) || TwistedFate::Player->IsDead())
	{
		Status = kReady;
	}
	else if (TwistedFate::Player->GetSpellBook()->GetSpellState(kSlotW) == Cooldown && strstr(TwistedFate::Player->GetSpellBook()->GetName(kSlotW), "PickACard") != nullptr)
	{
		Select = kCardNone;
		Status = kCooldown;
	}
	else if ((TwistedFate::Player->GetSpellBook()->GetSpellState(kSlotW) == DisabledOne || TwistedFate::Player->GetSpellBook()->GetSpellState(kSlotW) == DisabledTwo) && !TwistedFate::Player->IsDead())
	{
		Status = kSelected;
	}

	if (Select == kCardYellow && strstr(TwistedFate::Player->GetSpellBook()->GetName(kSlotW), "GoldCardLock") != nullptr)
	{
		TwistedFate::Spells->W->CastOnPlayer();
	}
	else if (Select == kCardBlue && strstr(TwistedFate::Player->GetSpellBook()->GetName(kSlotW), "BlueCardLock") != nullptr)
	{
		TwistedFate::Spells->W->CastOnPlayer();
	}
	else if (Select == kCardRed && strstr(TwistedFate::Player->GetSpellBook()->GetName(kSlotW), "RedCardLock") != nullptr)
	{
		TwistedFate::Spells->W->CastOnPlayer();
	}
}

void sCardSelector::OnSpellCast(CastedSpell const& spell)
{
	if (spell.Name_ == "PickACard")
	{
		Status = kSelecting;
	}

	if (spell.Name_ == "GoldCardLock" || spell.Name_ == "BlueCardLock" || spell.Name_ == "RedCardLock")
	{
		Status = kSelected;
	}
}