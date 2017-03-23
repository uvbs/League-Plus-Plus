#include "SoTriistana.h"

float SoTriistana::GetChargedDamage(IUnit* target)
{
	return target->HasBuff("tristanaecharge") ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE) + GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE) * target->GetBuffCount("tristanaechargesound") * 0.3f : 0.f;
}
