#include "Extension.h"
#include "Plugin.h"
#include "Menu.h"
#include "Spells.h"
#include "Events.h"
#include "Hero.h"
#include "SoUltiimate.h"

char* Author = "SoNiice";
char* Plugin = "SoUltiimate";
int Version = 1;

PluginSetup(Plugin);

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	PluginSDKSetup(PluginSDK);

	if (find(SoUltiimate::Champions.begin(), SoUltiimate::Champions.end(), std::string(GEntityList->Player()->ChampionName())) != SoUltiimate::Champions.end())
	{
		GHero = new IHero(const_cast<char*>(GEntityList->Player()->ChampionName()));
	}

	GPlugin = new IPlugin(Author, Plugin, Version);

	SoUltiimate::Initialize();
	Menu::Initialize();
	Spells::Initialize();
	Events::Initialize();

	GGame->PrintChat(GExtension->format("<font color=\"#0095DA\"><b>%s</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>%s</b></font> - <font color=\"#FFFFFF\">Loaded</font>", GPlugin->GetName(), GPlugin->GetAuthor()).c_str());
	GExtension->CheckVersion(GPlugin->GetName(), GPlugin->GetVersion());
}

PLUGIN_API void OnUnload()
{
	GGame->PrintChat(GExtension->format("<font color=\"#0095DA\"><b>%s</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>%s</b></font> - <font color=\"#FFFFFF\">Unloaded</font>", GPlugin->GetName(), GPlugin->GetAuthor()).c_str());

	if (find(SoUltiimate::Champions.begin(), SoUltiimate::Champions.end(), std::string(GEntityList->Player()->ChampionName())) != SoUltiimate::Champions.end())
	{
		delete GHero;
	}

	delete GExtension;
	delete GPlugin;
}