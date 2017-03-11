#include "PluginSDK.h"
#include "TwistedFate.h"

void sSpells::Create()
{
	Q = TwistedFate::SDK->CreateSpell2(kSlotQ, kLineCast, true, true, kCollidesWithYasuoWall);
	W = TwistedFate::SDK->CreateSpell(kSlotW);
	R = TwistedFate::SDK->CreateSpell(kSlotR, 5500);
}

void sSpells::Initialize() const
{
	Q->SetSkillshot(0.25f, 40.f, 1000.f, 1450.f);
}
