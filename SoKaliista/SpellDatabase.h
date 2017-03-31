#include "PluginSDK.h"
#include <map>

class SpellDatabase
{
public:
	struct Spell
	{
		eSpellSlot Slot;
		char* Name;
		char* DisplayName;
		int Health;
		bool Dangerous;
		int Delay;
		int Radius;
		int Speed;
		int Range;
		bool Missile;
		bool AoE;
		eSpellType SpellType;
		eCollisionFlags Collisions;
	};

	struct Champion
	{
		char* DisplayName;
		std::vector<Spell> Spells;
	};

	static std::map<eSpellSlot, char*> Slots;
	static std::map<char*, Champion> Champions;
};

