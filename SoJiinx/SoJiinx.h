#include "PluginSDK.h"

class SoJiinx
{
public:
	static int GetFishboneRange();
	static bool HasFishbone();

	static std::vector<std::string> SpecialSpells;

	static ITexture* HarassOn;
	static ITexture* HarassOff;

	static void Initialize();
	static bool OnTextureButton();
};

