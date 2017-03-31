#include "SoKaliista.h"
#include "Hero.h"
#include "Extension.h"
#include "Plugin.h"

//- Shield logics(need to hardcode them)
//- Anti Melee
//- Soulbound CC Saver(Only have huge dmg and death saver)
//- Flee

Vec3 SoKaliista::WallJumpTarget = Vec3(0, 0, 0);
int SoKaliista::WallJumpTime = 0;
bool SoKaliista::WallJumpPossible = false;
IUnit* SoKaliista::Soulbound = nullptr;
std::map<float, float> SoKaliista::SoulboundDamage;

double SoKaliista::GetRendDamage(IUnit* target)
{
	auto damage = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE);

	if (target->HasBuff("FerociousHowl"))
		damage *= 1.f - std::vector<float>{ .5f, .6f, .7f }[target->GetSpellLevel(kSlotR) - 1];

	if (target->HasBuff("meditate"))
		damage *= 1.f - std::vector<float>{ .5f, .55f, .6f, .65f, .7f }[target->GetSpellLevel(kSlotW) - 1];

	if (target->HasBuff("Tantrum"))
		damage -= std::vector<float>{ 2, 4, 6, 8, 10}[target->GetSpellLevel(kSlotE) - 1];

	if (GEntityList->Player()->HasBuff("summonerexhaust"))
		damage *= 0.6f;

	if (std::string(target->GetBaseSkinName()) == "SRU_Baron" && GEntityList->Player()->HasBuff("barontarget"))
		damage *= 0.5f;

	if (target->HasBuff("MoltenShield"))
		damage *= std::vector<float>{ 16.f, 22.f, 28.f, 34.f, 40.f }[target->GetSpellBook()->GetLevel(kSlotE) - 1];

	if (target->HasBuff("braumeshieldbuff"))
		damage *= 1.f - (0.275f + 0.025f * target->GetSpellLevel(kSlotE));

	if (target->HasBuff("BraumShieldRaise"))
		damage *= std::vector<float>{ .3f, .325f, .35f, .375f, .4f }[target->GetSpellBook()->GetLevel(kSlotE) - 1];

	if (target->HasBuff("GarenW"))
		damage *= 0.7f;

	if (target->HasBuff("MaokaiUlt"))
		damage *= 0.8f;

	if (target->HasBuff("GragasWSelf"))
		damage *= 1.f - (0.08f + 0.02f * target->GetSpellLevel(kSlotW));

	if (target->HasBuff("urgotswapdef"))
		damage *= 1.f - (0.2f + 0.1f * target->GetSpellLevel(kSlotR));

	if (GEntityList->Player()->HasBuff("urgotentropypassive"))
		damage *= 0.85;

	if (GEntityList->Player()->HasBuff("itemphantomdancerdebuff") && target->HasItemId(3046))
		damage *= 0.88f;

	if (target->HasBuff("Mastery6263"))
		damage *= 0.96f;

	if (target->HasBuff("MasteryWardenOfTheDawn"))
		damage *= 1.f - 0.06f * target->GetBuffCount("MasteryWardenOfTheDawn");

	damage -= GPlugin->GetMenuInteger("Misc", "E.DamageReduction");

	return damage;
}

Vec3 SoKaliista::GetFirstWallPoint(Vec3 from, Vec3 to, int step)
{
	auto direction = (to - from).VectorNormalize();

	for (auto i = 0; i < GExtension->GetDistance(from, to); i += step)
	{
		auto testPoint = from + i * direction;
		auto flags = GNavMesh->GetCollisionFlagsForPoint(testPoint);

		if (flags & kWallMesh)
		{
			return from + (i - step) * direction;
		}
	}

	return Vec3(0, 0, 0);
}