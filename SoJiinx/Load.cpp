#include "Extension.h"
#include "Plugin.h"
#include "Menu.h"
#include "Spells.h"
#include "Events.h"
#include "Hero.h"
#include <regex>
#include "SoJiinx.h"

char* Author = "SoNiice";
char* Champion = "Jinx";
char* Plugin = "SoJiinx";
int Version = 20;

PluginSetup(Plugin);

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	PluginSDKSetup(PluginSDK);

	GHero = new IHero(Champion);
	GPlugin = new IPlugin(Author, Plugin, Version);

	if (std::string(GEntityList->Player()->ChampionName()) != std::regex_replace(GHero->GetName(), std::regex("[^0-9a-zA-Z]+"), ""))
	{
		GGame->PrintChat(GExtension->format("<font color=\"#0095DA\"><b>%s</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>%s</b></font> - <font color=\"#FFFFFF\">You are not playing <b>%s</b>!</font>", GPlugin->GetName(), GPlugin->GetAuthor(), GHero->GetName()).c_str());
		return;
	}

	Menu::Initialize();
	Spells::Initialize();
	SoJiinx::Initialize();
	Events::Initialize();

	GGame->PrintChat(GExtension->format("<font color=\"#0095DA\"><b>%s</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>%s</b></font> - <font color=\"#FFFFFF\">Loaded</font>", GPlugin->GetName(), GPlugin->GetAuthor()).c_str());
	GExtension->CheckVersion(GPlugin->GetName(), GPlugin->GetVersion());
}

PLUGIN_API void OnUnload()
{
	GGame->PrintChat(GExtension->format("<font color=\"#0095DA\"><b>%s</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>%s</b></font> - <font color=\"#FFFFFF\">Unloaded</font>", GPlugin->GetName(), GPlugin->GetAuthor()).c_str());

	delete GHero;
	delete GExtension;
	delete GPlugin;
}