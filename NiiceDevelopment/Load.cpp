#include "Extension.h"
#include "Plugin.h"
#include "Menu.h"
#include "Events.h"

char* Author = "SoNiice";
char* Plugin = "NiiceDevelopment";
int Version = 10;

PluginSetup(Plugin);

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	PluginSDKSetup(PluginSDK);

	GPlugin = new IPlugin(Author, Plugin, Version);

	Menu::Initialize();
	Events::Initialize();

	GGame->PrintChat(GExtension->format("<font color=\"#0095DA\"><b>%s</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>%s</b></font> - <font color=\"#FFFFFF\">Loaded</font>", GPlugin->GetName(), GPlugin->GetAuthor()).c_str());
	GExtension->CheckVersion(GPlugin->GetName(), GPlugin->GetVersion());
}

PLUGIN_API void OnUnload()
{
	GGame->PrintChat(GExtension->format("<font color=\"#0095DA\"><b>%s</b></font> <font color=\"#FFFFFF\">by</font> <font color=\"#0095DA\"><b>%s</b></font> - <font color=\"#FFFFFF\">Unloaded</font>", GPlugin->GetName(), GPlugin->GetAuthor()).c_str());

	delete GExtension;
	delete GPlugin;
}