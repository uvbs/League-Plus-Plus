#include "PluginSDK.h"
#include <map>

class IHero
{
public:
	explicit IHero(char* name);
	static char* GetName();
	static void AddSpell(char* name, void* spell);
	static ISpell* GetSpell(char* name);
	static ISpell2* GetSpell2(char* name);

private:
	static char* Name;
	static std::map<char*, void*> Spells;
};

extern IHero* GHero;
