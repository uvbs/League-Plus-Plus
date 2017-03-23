#include "SoUltiimate.h"
#include "PluginSDK.h"
#include "Extension.h"
#include "Hero.h"

std::vector<char*> SoUltiimate::Champions = { "Ashe", "Draven", "Ezreal", "Jinx", "Karthus" };
std::map<int, float> SoUltiimate::VisibleTimers;
std::map<int, std::map<eTeleportType, TeleportStatus>> SoUltiimate::TeleportTimers;

void SoUltiimate::Initialize()
{
	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		auto teleportStatus = TeleportStatus();
		teleportStatus.Status = -1;
		teleportStatus.Duration = 0.f;
		teleportStatus.StartTime = 0.f;
		teleportStatus.EndTime = 0.f;
		teleportStatus.UltimateTime = 0.f;

		TeleportTimers[enemy->GetNetworkId()][Teleport_Teleport] = teleportStatus;
		TeleportTimers[enemy->GetNetworkId()][Teleport_Recall] = teleportStatus;
		TeleportTimers[enemy->GetNetworkId()][Teleport_Shen] = teleportStatus;
		TeleportTimers[enemy->GetNetworkId()][Teleport_TwistedFate] = teleportStatus;
	}
}

void SoUltiimate::HandleUltimate(IUnit* hero)
{
	if (find(Champions.begin(), Champions.end(), std::string(GEntityList->Player()->ChampionName())) != Champions.end())
	{
		if (GDamage->GetSpellDamage(GEntityList->Player(), hero, kSlotR) >= hero->GetHealth() + hero->HPRegenRate() * (TeleportTimers[hero->GetNetworkId()][Teleport_Recall].Duration))
		{
			auto myPosition = GEntityList->Player()->GetPosition();
			auto spawnPosition = GExtension->GetSpawnPosition(hero);
			auto distance = GExtension->GetDistance(myPosition, spawnPosition);

			Vec3 collisionPosition;
			int collisionFlags;
			GPrediction->TestLineOfSight(myPosition, spawnPosition, collisionPosition, collisionFlags);
			
			if (!GHero->GetSpell2("R")->GetCollisionFlags() || !(GHero->GetSpell2("R")->GetCollisionFlags() & collisionFlags))
			{
				auto speed = GHero->GetSpell2("R")->Speed();

				if (std::string(GEntityList->Player()->ChampionName()) == "Jinx")
				{
					auto accelerationRate = 0.3f;
					auto accelerationDifference = distance - 1350.f;
					auto difference = distance - 1500.f;

					if (accelerationDifference > 150.f)
						accelerationDifference = 150.f;

					speed = (1350.f * speed + accelerationDifference * (speed + accelerationRate * accelerationDifference) + difference * 2200.f) / distance;
				}

				auto time = TeleportTimers[hero->GetNetworkId()][Teleport_Recall].Duration - (distance / speed + GHero->GetSpell2("R")->GetDelay());

				if (time >= 0)
				{
					auto teleportStatus = TeleportStatus();
					teleportStatus.Status = TeleportTimers[hero->GetNetworkId()][Teleport_Recall].Status;
					teleportStatus.Duration = TeleportTimers[hero->GetNetworkId()][Teleport_Recall].Duration;
					teleportStatus.StartTime = TeleportTimers[hero->GetNetworkId()][Teleport_Recall].StartTime;
					teleportStatus.EndTime = TeleportTimers[hero->GetNetworkId()][Teleport_Recall].EndTime;
					teleportStatus.UltimateTime = teleportStatus.StartTime + time;

					TeleportTimers[hero->GetNetworkId()][Teleport_Recall] = teleportStatus;
				}
			}
		}
	}
}
