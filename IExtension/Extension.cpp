#include "Extension.h"
#include <string>
#include <fstream>
#include <regex>
#include <iostream>

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

ITexture* IExtension::GetTexture(char* name)
{
	if (TextureExists(name))
		return GRender->CreateTextureFromFile(name);

	std::string texture;

	if (GPluginSDK->ReadFileFromURL(format("https://raw.githubusercontent.com/SoNiice/League-Plus-Plus/master/Textures/%s", name), texture))
		return GRender->CreateTextureFromMemory((uint8_t*)texture.data(), texture.length(), name);

	return nullptr;
}

bool IExtension::TextureExists(char* name)
{
	std::string baseDirectory;
	GPluginSDK->GetBaseDirectory(baseDirectory);

	auto file = baseDirectory + "/Textures/" + std::string(name);
	auto hFile = CreateFileA(file.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		return true;
	}

	return false;
}

int IExtension::GetDangerLevel(IUnit* hero)
{

	std::string baseDirectory;
	GPluginSDK->GetBaseDirectory(baseDirectory);

	auto file = baseDirectory + "/Configs/Target Selector.ini";
	auto hFile = CreateFileA(file.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);

		std::ifstream fileStream(file.c_str());
		std::string line;

		while (fileStream && getline(fileStream, line)) {
			if (line.length() == 0)
				continue;

			std::smatch matches;

			if (regex_match(line, matches, std::regex("Danger Level - ([a-zA-Z]+)=([1-5])")))
			{
				if (std::string(matches[1]) == hero->ChampionName())
				{
					return stoi(std::string(matches[2]));
				}
			}
		}
	}

	return 1;
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
	return (sender->GetPosition() - target->GetPosition()).Length2D();
}

float IExtension::GetDistance(Vec3 senderPosition, Vec3 targetPosition)
{
	return (senderPosition - targetPosition).Length2D();
}

float IExtension::GetRealDistance(IUnit* sender, IUnit* target)
{
	return (sender->ServerPosition() - target->ServerPosition()).Length2D() + sender->BoundingRadius() + target->BoundingRadius();
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

eMinionType IExtension::GetMinionType(IUnit* minion)
{
	static std::vector<std::string> normalMinions = { 
		"sru_chaosminionmelee", "sru_chaosminionranged",
		"sru_orderminionmelee", "sru_orderminionranged",
		"ha_chaosminionmelee", "ha_chaosminionranged",
		"ha_orderminionmelee", "ha_orderminionranged"
	};

	static std::vector<std::string> siegeMinions = { 
		"sru_chaosminionsiege", "sru_orderminionsiege",
		"ha_chaosminionsiege", "ha_orderminionsiege"
	};

	static std::vector<std::string> superMinions = {
		"sru_chaosminionsuper", "sru_orderminionsuper",
		"ha_chaosminionsuper", "ha_orderminionsuper"
	};

	static std::vector<std::string> smallJungleCreeps = {
		"sru_razorbeakmini", "sru_murkwolfmini",
		"sru_krugmini", "sru_krugminimini"
	};

	static std::vector<std::string> bigJungleCreeps = {
		"sru_razorbeak", "sru_murkwolf", "sru_gromp",
		"sru_krug", "sru_red", "sru_blue", "sru_crab"
	};

	static std::vector<std::string> epicJungleCreeps = {
		"sru_dragon_air", "sru_dragon_earth", "sru_dragon_fire",
		"sru_dragon_water", "sru_dragon_elder", "sru_riftherald",
		"sru_baron"
	};

	if (minion == nullptr)
		return kMinionUnknown;

	auto baseSkinName = std::string(minion->GetBaseSkinName());
	transform(baseSkinName.begin(), baseSkinName.end(), baseSkinName.begin(), ::tolower);

	if (std::string(baseSkinName).find("ward") != std::string::npos || std::string(baseSkinName).find("trinket") != std::string::npos)
		return kMinionWard;

	if (find(normalMinions.begin(), normalMinions.end(), baseSkinName) != normalMinions.end())
		return kMinionNormal;

	if (find(siegeMinions.begin(), siegeMinions.end(), baseSkinName) != siegeMinions.end())
		return kMinionSiege;

	if (find(superMinions.begin(), superMinions.end(), baseSkinName) != superMinions.end())
		return kMinionSuper;

	if (find(smallJungleCreeps.begin(), smallJungleCreeps.end(), baseSkinName) != smallJungleCreeps.end())
		return kMinionJungleSmall;

	if (find(bigJungleCreeps.begin(), bigJungleCreeps.end(), baseSkinName) != bigJungleCreeps.end())
		return kMinionJungleBig;

	if (find(epicJungleCreeps.begin(), epicJungleCreeps.end(), baseSkinName) != epicJungleCreeps.end())
		return kMinionJungleEpic;

	return kMinionUnknown;
}
