#include "Events.h"
#include "Plugin.h"
#include "SoUltiimate.h"

void Events::Initialize()
{
	GPlugin->RegisterGameUpdateEvent(OnGameUpdate);
	GPlugin->RegisterTeleportEvent(OnTeleport);
	GPlugin->RegisterRenderEvent(OnRender);
}

bool showRecall = false;

void Events::OnGameUpdate()
{
	if (!GUtility->IsLeagueWindowFocused())
		return;

	if (GGame->IsChatOpen())
		return;

	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (!enemy->IsDead() && enemy->IsVisible())
		{
			SoUltiimate::VisibleTimers[enemy->GetNetworkId()] = GGame->Time();
		}
	}
}

void Events::OnRender()
{
	auto paddingY = 0;

	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		auto teleportStatus = SoUltiimate::TeleportTimers[enemy->GetNetworkId()][Teleport_Recall];

		auto barX = GRender->ScreenSize().x * 0.425f;
		auto barY = GRender->ScreenSize().y * 0.8f;
		auto barWidth = GRender->ScreenSize().x - 2 * barX;
		auto barHeight = 7;
		auto color = Vec4(0, 0, 0, 0);
		auto width = 0.f;

		switch (teleportStatus.Status)
		{
		case Teleport_Start:
			width = (barWidth - 3) / teleportStatus.Duration * (teleportStatus.EndTime - GGame->Time());
			color = Vec4(255, 128, 0, 255);
			break;
		case Teleport_Abort:
			width = (barWidth - 3) - (barWidth - 3) / teleportStatus.Duration * (teleportStatus.EndTime - teleportStatus.StartTime);
			color = Vec4(255, 0, 0, 255);
			break;
		case Teleport_Finish:
			color = Vec4(0, 255, 0, 255);
			width = barWidth - 3;
			break;
		default:
			break;
		}

		if (GGame->Time() < teleportStatus.EndTime + 1)
		{
			GRender->DrawOutinedBox(Vec2(barX, barY + paddingY), Vec2(barWidth, barHeight), 1.f, Vec4(255, 255, 255, 255));
			GRender->DrawFilledBox(Vec2(barX + 2, barY + 2 + paddingY), Vec2(width, barHeight - 3), color);
			GRender->DrawTextW(Vec2(barX + 2 + width, barY + barHeight + 5 + paddingY), color, enemy->ChampionName());

			if (teleportStatus.Status == Teleport_Start && teleportStatus.UltimateTime >= 0.f)
				GRender->DrawLine(Vec2(barX + (barWidth) / teleportStatus.Duration * (teleportStatus.EndTime - teleportStatus.UltimateTime), barY + paddingY), Vec2(1 + barX + (barWidth) / teleportStatus.Duration * (teleportStatus.EndTime - teleportStatus.UltimateTime), 1 + barY + paddingY + barHeight), Vec4(255, 0, 0, 255));
			
			if (teleportStatus.Status == Teleport_Start)
				GRender->DrawTextW(Vec2(barX + barWidth + 4, barY + paddingY - 3), Vec4(255, 255, 255, 255), "%.1f", teleportStatus.EndTime - GGame->Time());

			paddingY -= 30;
		}
	}
}

void Events::OnTeleport(OnTeleportArgs* args)
{
	if (args->Source->IsEnemy(GEntityList->Player()) && args->Source->IsHero())
	{
		if (args->Type != Teleport_Unknown)
		{
			std::string type = "";
			std::string status = "";
			auto color = Vec4(255, 255, 255, 255);

			switch (args->Type)
			{
			case Teleport_Teleport:
				status = "Teleport";
				break;
			case Teleport_Recall:
				status = "Recall";
				break;
			case Teleport_Shen:
				status = "Shen (R)";
				break;
			case Teleport_TwistedFate:
				status = "Twisted Fate (R)S";
				break;
			default:
				break;
			}

			switch (args->Status)
			{
			case Teleport_Start:
				type = "Start";
				color = Vec4(255, 255, 255, 255);
				break;
			case Teleport_Abort:
				type = "Abort";
				color = Vec4(255, 0, 0, 255);
				break;
			case Teleport_Finish:
				type = "Finish";
				color = Vec4(0, 255, 0, 255);
				break;
			default:
				break;
			}

			GRender->NotificationEx(color, 2, false, true, "%s %s %s", args->Source->GetBaseSkinName(), type.c_str(), status.c_str());

			if (args->Status == Teleport_Start)
			{
				auto teleportStatus = TeleportStatus();
				teleportStatus.Status = args->Status;
				teleportStatus.Duration = args->Duration / 1000;
				teleportStatus.StartTime = GGame->Time();
				teleportStatus.EndTime = GGame->Time() + args->Duration / 1000;
				teleportStatus.UltimateTime = 0.f;

				SoUltiimate::TeleportTimers[args->Source->GetNetworkId()][static_cast<eTeleportType>(args->Type)] = teleportStatus;
				
				if (args->Type == Teleport_Recall)
					SoUltiimate::HandleUltimate(args->Source, teleportStatus.Duration);
			}
			else if (args->Status == Teleport_Abort)
			{
				auto teleportStatus = TeleportStatus();
				teleportStatus.Status = args->Status;
				teleportStatus.Duration = SoUltiimate::TeleportTimers[args->Source->GetNetworkId()][static_cast<eTeleportType>(args->Type)].Duration;
				teleportStatus.StartTime = SoUltiimate::TeleportTimers[args->Source->GetNetworkId()][static_cast<eTeleportType>(args->Type)].StartTime;
				teleportStatus.EndTime = GGame->Time();
				teleportStatus.UltimateTime = 0.f;

				SoUltiimate::TeleportTimers[args->Source->GetNetworkId()][static_cast<eTeleportType>(args->Type)] = teleportStatus;
			}
			else
			{
				auto teleportStatus = TeleportStatus();
				teleportStatus.Status = args->Status;
				teleportStatus.Duration = 0.f;
				teleportStatus.StartTime = 0.f;
				teleportStatus.EndTime = GGame->Time();
				teleportStatus.UltimateTime = 0.f;

				SoUltiimate::TeleportTimers[args->Source->GetNetworkId()][static_cast<eTeleportType>(args->Type)] = teleportStatus;
			}
		}
	}
}
