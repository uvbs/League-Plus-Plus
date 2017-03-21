#include "Extension.h"

IExtension* GExtension = new IExtension();

std::string IExtension::format(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	auto size = _vscprintf(format, args);
	std::string result(++size, 0);
	vsnprintf_s(const_cast<char*>(result.data()), size, _TRUNCATE, format, args);
	va_end(args);

	return result;
}

void IExtension::CheckVersion(char* name, int version)
{
	GGame->PrintChat(format("<font color=\"#0095DA\"><b>%s</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">Checking for updates..</font>", name).c_str());
	
	std::string newestVersion;

	if (GPluginSDK->ReadFileFromURL(format("https://raw.githubusercontent.com/SoNiice/League-Plus-Plus/master/%s/version.txt", name), newestVersion))
	{
		if (version < atoi(newestVersion.c_str()))
		{
			GGame->PrintChat(format("<font color=\"#0095DA\"><b>%s</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">There's a newer version!</font>", name).c_str());
			return;
		}
	}

	GGame->PrintChat(format("<font color=\"#0095DA\"><b>%s</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>SoNiice</b></font> - <font color=\"#FFFFFF\">You got the newest version!</font>", name).c_str());
}

bool IExtension::IsComboing()
{
	return GOrbwalking->GetOrbwalkingMode() == kModeCombo;
}

bool IExtension::IsHarassing()
{
	return GOrbwalking->GetOrbwalkingMode() == kModeMixed;
}

bool IExtension::IsClearing()
{
	return GOrbwalking->GetOrbwalkingMode() == kModeLaneClear;
}

bool IExtension::IsLasthitting()
{
	return GOrbwalking->GetOrbwalkingMode() == kModeLastHit;
}

bool IExtension::IsFarming()
{
	return GOrbwalking->GetOrbwalkingMode() == kModeLaneClear || GOrbwalking->GetOrbwalkingMode() == kModeLastHit || GOrbwalking->GetOrbwalkingMode() == kModeMixed || GOrbwalking->GetOrbwalkingMode() == kModeFreeze;
}

float IExtension::GetDistance(IUnit* sender, IUnit* target)
{
	return (sender->GetPosition() - target->GetPosition()).Length();
}

float IExtension::GetDistance(Vec3 senderPosition, Vec3 targetPosition)
{
	return (senderPosition - targetPosition).Length();
}

float IExtension::GetRealDistance(IUnit* sender, IUnit* target)
{
	return (sender->ServerPosition() - target->ServerPosition()).Length() + sender->BoundingRadius() + target->BoundingRadius();
}

int IExtension::CountAliesInRange(float range)
{
	auto allies = 0;

	for (auto ally : GEntityList->GetAllHeros(true, false))
	{
		if (ally != nullptr && ally != GEntityList->Player() && GetDistance(GEntityList->Player(), ally) <= range)
		{
			allies++;
		}
	}

	return allies;
}

int IExtension::CountEnemiesInRange(float range)
{
	auto enemies = 0;

	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy != nullptr && GetDistance(GEntityList->Player(), enemy) <= range)
		{
			enemies++;
		}
	}

	return enemies;
}

int IExtension::CountAlliesInPositionRange(Vec3 position, float range)
{
	auto allies = 0;

	for (auto ally : GEntityList->GetAllHeros(true, false))
	{
		if (ally != nullptr && GetDistance(position, ally->GetPosition()) <= range)
		{
			allies++;
		}
	}

	return allies;
}

int IExtension::CountAlliesInTargetRange(IUnit* target, float range)
{
	auto allies = 0;

	for (auto ally : GEntityList->GetAllHeros(true, false))
	{
		if (ally != nullptr && GetDistance(target, ally) <= range)
		{
			allies++;
		}
	}

	return allies;
}

int IExtension::CountEnemiesInPositionRange(Vec3 position, float range)
{
	auto enemies = 0;

	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy != nullptr && GetDistance(position, enemy->GetPosition()) <= range)
		{
			if (enemy->GetPosition() != position)
			{
				enemies++;
			}
		}
	}

	return enemies;
}

int IExtension::CountEnemiesInTargetRange(IUnit* target, float range)
{
	auto enemies = 0;

	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy != nullptr && GetDistance(target, enemy) <= range)
		{
			if (enemy != target)
			{
				enemies++;
			}
		}
	}

	return enemies;
}

int IExtension::CountMinionsInPositionRange(Vec3 position, float range)
{
	auto minions = 0;

	for (auto minion : GEntityList->GetAllMinions(false, true, false))
	{
		if (minion != nullptr && GetDistance(position, minion->GetPosition()) <= range)
		{
			if (minion->GetPosition() != position && !minion->IsDead())
			{
				minions++;
			}
		}
	}

	return minions;
}

int IExtension::CountMinionsInTargetRange(IUnit* target, float range)
{
	auto minions = 0;

	for (auto minion : GEntityList->GetAllMinions(false, true, false))
	{
		if (minion != nullptr && GetDistance(target, minion) <= range)
		{
			if (minion != target && !minion->IsDead())
			{
				minions++;
			}
		}
	}

	return minions;
}

Vec3 IExtension::GetSpawnPosition(IUnit* hero)
{
	switch (GGame->GetMapId())
	{
	case kMapSummonersRift:
		switch (hero->GetTeam())
		{
		case kTeam1:
			return Vec3(414.f, 183.f, 420.f);
		case kTeam2:
			return Vec3(14306.f, 171.f, 14375.f);
		default:
			return Vec3(0, 0, 0);
		}
	default:
		return Vec3(0, 0, 0);
	}
}
