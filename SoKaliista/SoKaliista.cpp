#include "SoKaliista.h"
#include "Hero.h"
#include "Extension.h"
#include "Plugin.h"

//- sPrediction
//- Shield logics(need to hardcode them)
//- E Humanizer(Delay)
//- Anti Melee
//- Soulbound CC Saver(Only have huge dmg and death saver)
//- Flee

Vec3 SoKaliista::WallJumpTarget = Vec3(0, 0, 0);
int SoKaliista::WallJumpTime = 0;
bool SoKaliista::WallJumpPossible = false;
IUnit* SoKaliista::Soulbound = nullptr;
std::map<float, float> SoKaliista::SoulboundDamage;

float SoKaliista::GetRendDamage(IUnit* target)
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