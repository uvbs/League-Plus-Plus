#include "SoJiinx.h"
#include "Extension.h"
#include "Plugin.h"

ITexture* SoJiinx::HarassOn;
ITexture* SoJiinx::HarassOff;

std::vector<std::string> SoJiinx::SpecialSpells = {
	"luxlightbinding",
	"katarinar",
	"drain",
	"consume",
	"absolutezero",
	"staticfield",
	"reapthewhirlwind",
	"jinxw",
	"jinxr",
	"shenstandunited",
	"threshe",
	"threshrpenta",
	"threshq",
	"meditate",
	"caitlynpiltoverpeacemaker",
	"volibearqattack",
	"cassiopeiapetrifyinggaze",
	"ezrealtrueshotbarrage",
	"galioidolofdurand",
	"luxmalicecannon",
	"missfortunebullettime",
	"infiniteduress",
	"alzaharnethergrasp",
	"lucianq",
	"velkozr",
	"rocketgrabmissile"
};

int SoJiinx::GetFishboneRange()
{
	int ranges[6] = {0, 75, 100, 125, 150, 175};

	return ranges[GEntityList->Player()->GetSpellBook()->GetLevel(kSlotQ)];
}

bool SoJiinx::HasFishbone()
{
	return GEntityList->Player()->HasBuff("JinxQ");
}

void SoJiinx::Initialize()
{
	HarassOn = GExtension->GetTexture("sojiinx.q.harass.on.png");
	HarassOff = GExtension->GetTexture("sojiinx.q.harass.off.png");

	GPlugin->RegisterGameUpdateEvent([]
		{
			if (GPlugin->GetMenuInteger("Drawings", "Harass.Q") == 1 || GPlugin->GetMenuInteger("Drawings", "Harass.Q") == 3)
			{
				static auto previousState = false;
				auto currentState = GetAsyncKeyState(VK_LBUTTON);

				if (previousState && !currentState && OnTextureButton())
				{
					GPlugin->UpdateInteger("Harass", "Q", !GPlugin->GetMenuBoolean("Harass", "Q"));
				}

				previousState = currentState;

				if (GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_LBUTTON) && OnTextureButton())
				{
					Vec3 worldToScreenMouse;
					GGame->Projection(GGame->CursorPosition(), &worldToScreenMouse);

					GPlugin->UpdateInteger("Drawings", "Harass.Q.Texture.X", worldToScreenMouse.x - (GPlugin->GetMenuBoolean("Harass", "Q") ? HarassOn : HarassOff)->GetSize().x / 2);
					GPlugin->UpdateInteger("Drawings", "Harass.Q.Texture.Y", worldToScreenMouse.y - 10);
				}
			}
		}
	);
}

bool SoJiinx::OnTextureButton()
{
	if (GPlugin->GetMenuInteger("Drawings", "Harass.Q") == 1 || GPlugin->GetMenuInteger("Drawings", "Harass.Q") == 3)
	{
		auto button = GPlugin->GetMenuBoolean("Harass", "Q") ? HarassOn : HarassOff;
		auto buttonPosition = Vec2(GPlugin->GetMenuInteger("Drawings", "Harass.Q.Texture.X"), GPlugin->GetMenuInteger("Drawings", "Harass.Q.Texture.Y"));
		Vec3 worldToScreenMouse;
		GGame->Projection(GGame->CursorPosition(), &worldToScreenMouse);

		return worldToScreenMouse.x >= buttonPosition.x && worldToScreenMouse.x <= buttonPosition.x + button->GetSize().x && worldToScreenMouse.y >= buttonPosition.y && worldToScreenMouse.y <= buttonPosition.y + button->GetSize().y;
	}

	return false;
}
