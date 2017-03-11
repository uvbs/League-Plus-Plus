#include "PluginSDK.h"
#include "Aatrox.h"

void sSpells::Create()
{
	Q = Aatrox::SDK->CreateSpell2(kSlotQ, kCircleCast, false, true, kCollidesWithNothing);
	W = Aatrox::SDK->CreateSpell(kSlotW);
	E = Aatrox::SDK->CreateSpell2(kSlotE, kLineCast, false, true, kCollidesWithNothing);
	R = Aatrox::SDK->CreateSpell(kSlotR, 550.f);
}

void sSpells::Initialize() const
{
	Q->SetSkillshot(0.6f, 250.f, 2000.f, 650.f);
	E->SetSkillshot(0.25f, 35.f, 1250.f, 1075.f);
}
