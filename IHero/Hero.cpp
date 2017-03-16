#include "Hero.h"

IHero* GHero;
char* IHero::Name;
std::map<char*, void*> IHero::Spells;

IHero::IHero(char* name)
{
	Name = name;
}

char* IHero::GetName()
{
	return Name;
}

void IHero::AddSpell(char* name, void* spell)
{
	Spells[name] = spell;
}

ISpell* IHero::GetSpell(char* name)
{
	return static_cast<ISpell*>(Spells[name]);
}

ISpell2* IHero::GetSpell2(char* name)
{
	return static_cast<ISpell2*>(Spells[name]);
}
