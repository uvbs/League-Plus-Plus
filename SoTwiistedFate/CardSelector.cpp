#include "TwistedFate.h"
#include "Hero.h"
#include "Plugin.h"

int CardSelector::Select = kCardNone;
int CardSelector::Status = kReady;

void CardSelector::StartSelecting(int card)
{
	if (strstr(GEntityList->Player()->GetSpellBook()->GetName(kSlotW), "PickACard") != nullptr && Status == kReady)
	{
		Select = card;

		if (GGame->TickCount() - TwistedFate::CardPickTick > 100 + GGame->Latency() / 2)
		{
			GHero->GetSpell("W")->CastOnPlayer();
			TwistedFate::CardPickTick = GGame->TickCount();
		}
	}
}

void CardSelector::OnGameUpdate()
{
	if (GEntityList->Player()->GetSpellBook()->GetSpellState(kSlotW) == Ready && strstr(GEntityList->Player()->GetSpellBook()->GetName(kSlotW), "PickACard") != nullptr && (Status != kSelecting || GGame->TickCount() - TwistedFate::CardPickTick > 500) || GEntityList->Player()->IsDead())
	{
		Status = kReady;
	}
	else if (GEntityList->Player()->GetSpellBook()->GetSpellState(kSlotW) == Cooldown && strstr(GEntityList->Player()->GetSpellBook()->GetName(kSlotW), "PickACard") != nullptr)
	{
		Select = kCardNone;
		Status = kCooldown;
	}
	else if ((GEntityList->Player()->GetSpellBook()->GetSpellState(kSlotW) == DisabledOne || GEntityList->Player()->GetSpellBook()->GetSpellState(kSlotW) == DisabledTwo) && !GEntityList->Player()->IsDead())
	{
		Status = kSelected;
	}

	if (Select == kCardYellow && strstr(GEntityList->Player()->GetSpellBook()->GetName(kSlotW), "GoldCardLock") != nullptr)
	{
		GHero->GetSpell("W")->CastOnPlayer();
	}
	else if (Select == kCardBlue && strstr(GEntityList->Player()->GetSpellBook()->GetName(kSlotW), "BlueCardLock") != nullptr)
	{
		GHero->GetSpell("W")->CastOnPlayer();
	}
	else if (Select == kCardRed && strstr(GEntityList->Player()->GetSpellBook()->GetName(kSlotW), "RedCardLock") != nullptr)
	{
		GHero->GetSpell("W")->CastOnPlayer();
	}
}

void CardSelector::OnSpellCast(CastedSpell const& spell)
{
	if (std::string(spell.Name_) == "PickACard")
	{
		Status = kSelecting;

		if (GPlugin->GetMenuBoolean("W", "AutoAttack"))
		{
			GOrbwalking->SetAttacksAllowed(false);
		}
	}

	if (std::string(spell.Name_) == "GoldCardLock" || std::string(spell.Name_) == "BlueCardLock" || std::string(spell.Name_) == "RedCardLock")
	{
		Status = kSelected;

		if (GPlugin->GetMenuBoolean("W", "AutoAttack"))
		{
			GOrbwalking->SetAttacksAllowed(true);
		}
	}
}