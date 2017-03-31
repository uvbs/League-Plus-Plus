#include "Plugin.h"
#include "Menu.h"
#include "Extension.h"
#include "SpellDatabase.h"

void Menu::Initialize()
{
	GPlugin->AddMenu("Drawings", "ii | Drawings");
	{
		GPlugin->AddCheckBox("Drawings", "Q", "Draw Q Range", true);
		GPlugin->AddColor("Drawings", "Q.Color", "^-> Q Color", 205, 92, 92, 255);
		GPlugin->AddCheckBox("Drawings", "W", "Draw W Range", false);
		GPlugin->AddColor("Drawings", "W.Color", "^-> W Color", 147, 122, 219, 255);
		GPlugin->AddCheckBox("Drawings", "E", "Draw E Range", true);
		GPlugin->AddColor("Drawings", "E.Color", "^-> E Color", 139, 0, 0, 255);
		GPlugin->AddCheckBox("Drawings", "E.Leaving", "Draw E Range (Leaving)", true);
		GPlugin->AddColor("Drawings", "E.Leaving.Color", "^-> Leaving Color", 139, 0, 0, 255);
		GPlugin->AddCheckBox("Drawings", "E.Stacks", "Draw E Stacks", true);
		GPlugin->AddCheckBox("Drawings", "E.Damage", "Draw E Damage (Percent)", true);
		GPlugin->AddCheckBox("Drawings", "E.Damage.Healthbar", "Draw E Damage (Healthbar)", true);
		GPlugin->AddColor("Drawings", "E.Damage.Healthbar.Color", "^-> Bar Color", 0, 128, 0, 255);
		GPlugin->AddCheckBox("Drawings", "R", "Draw R Range", true);
		GPlugin->AddCheckBox("Drawings", "Ready", "Draw only if spell is ready", true);
	}

	GPlugin->AddMenu("Combo", "ii | Combo Settings");
	{
		GPlugin->AddCheckBox("Combo", "Q", "Use Q", true);
		GPlugin->AddCheckBox("Combo", "Q.Reset", "^-> Use Q to reset AA", true);
		GPlugin->AddInteger("Combo", "Q.Mana", "^-> Minimum Mana", 0, 100, 45);
		GPlugin->AddCheckBox("Combo", "Q.Mana.Ignore", "    ^-> Ignore if killable", true);
		GPlugin->AddCheckBox("Combo", "E", "Use E", true);
		GPlugin->AddCheckBox("Combo", "Minions", "Attacks Minions while chasing", true);
		GPlugin->AddInteger("Combo", "Minions.Range", "^-> while Champions in Range of {x}", 600, 1500, 1000);
	}

	GPlugin->AddMenu("Harass", "ii | Harass Settings");
	{
		GPlugin->AddCheckBox("Harass", "Q", "Use Q", true);
		GPlugin->AddInteger("Harass", "Q.Mana", "^-> Minimum Mana", 0, 100, 45);
		GPlugin->AddCheckBox("Harass", "E", "Use E to kill a Minion and Harass", true);
	}

	GPlugin->AddMenu("Clear", "ii | Clear Settings");
	{
		GPlugin->AddCheckBox("Clear", "Q", "Use Q", false);
		GPlugin->AddInteger("Clear", "Q.Minions", "^-> Minimum kill {x} minions w/ Q", 1, 10, 3); 
		GPlugin->AddInteger("Clear", "Q.Mana", "^-> Minimum Mana", 0, 100, 60);
		GPlugin->AddCheckBox("Clear", "E.Siege", "Always E Siege minions", true);
		GPlugin->AddCheckBox("Clear", "E", "Use E", true);
		GPlugin->AddInteger("Clear", "E.Minions", "^-> Minimum kill {x} minions w/ E", 1, 10, 3);
	}

	GPlugin->AddMenu("Jungle", "ii | Jungle Settings");
	{
		GPlugin->AddCheckBox("Jungle", "E", "Use E to steal", true);
		GPlugin->AddCheckBox("Jungle", "E.Epics", "^-> Steal Epic", true);
		GPlugin->AddCheckBox("Jungle", "E.Big", "^-> Steal Big", true);
		GPlugin->AddCheckBox("Jungle", "E.Small", "^-> Steal Small", false);
	}

	GPlugin->AddMenu("Flee", "ii | Flee Settings (WIP, NOT WORKING)"); // WIP
	{
		GPlugin->AddCheckBox("Flee", "Walljump", "Try to jump over walls", true);
		GPlugin->AddCheckBox("Flee", "Autoattack", "Smart usage of AA", true);
		GPlugin->AddKey("Flee", "Key", "Flee Key", 'G');
	}

	GPlugin->AddMenu("Sentinel", "ii | Sentinel Exploit");
	{
		GPlugin->AddKey("Sentinel", "Dragon", "Sentinel Dragon", 'Y');
		GPlugin->AddKey("Sentinel", "Baron", "Sentinel Baron", 'T');
	}

	GPlugin->AddMenu("Item", "ii | Items");
	{
		GPlugin->AddMenu("Cutlass", "ii | Bilgewater Cutlass", "Item");
		{
			GPlugin->AddCheckBox("Cutlass", "Use.Combo", "Use Bilgewater Cutlassin Combo", true);
			GPlugin->AddCheckBox("Cutlass", "Use.Harass", "Use Bilgewater Cutlass in Harass", true);
			GPlugin->AddCheckBox("Cutlass", "Use.Flee", "Use Bilgewater Cutlass in Flee", true);
			GPlugin->AddInteger("Cutlass", "Health", "^-> Health is below {x}%", 1, 100, 80);
			GPlugin->AddInteger("Cutlass", "Enemy.Health", "^-> Enemy Health is below {x}%", 1, 100, 85);
		}

		GPlugin->AddMenu("BotRK", "ii | Blade of the Ruined King", "Item");
		{
			GPlugin->AddCheckBox("BotRK", "Use.Combo", "Use Blade of the Ruined King in Combo", true);
			GPlugin->AddCheckBox("BotRK", "Use.Harass", "Use Blade of the Ruined King in Harass", true);
			GPlugin->AddCheckBox("BotRK", "Use.Flee", "Use Blade of the Ruined King in Flee", true);
			GPlugin->AddInteger("BotRK", "Health", "^-> Health is below {x}%", 1, 100, 80);
			GPlugin->AddInteger("BotRK", "Enemy.Health", "^-> Enemy Health is below {x}%", 1, 100, 75);
		}

		GPlugin->AddMenu("Ghostblade", "ii | Youmuus Ghostblade", "Item");
		{
			GPlugin->AddCheckBox("Ghostblade", "Use.Combo", "Use Youmuus Ghostblade in Combo", true);
			GPlugin->AddCheckBox("Ghostblade", "Use.Harass", "Use Youmuus Ghostblade in Harass", true);
			GPlugin->AddCheckBox("Ghostblade", "Use.Flee", "Use Youmuus Ghostblade in Flee", true);
			GPlugin->AddInteger("Ghostblade", "Health", "^-> Health is below {x}%", 1, 100, 100);
			GPlugin->AddInteger("Ghostblade", "Enemy.Health", "^-> Enemy Health is below {x}%", 1, 100, 100);
		}
	}

	GPlugin->AddMenu("Soulbound", "ii | Soulbound");
	{
		GPlugin->AddCheckBox("Soulbound", "Save", "Use R to save ally", true);
		GPlugin->AddInteger("Soulbound", "Save.Health", "^-> On {x}% health with enemies around", 0, 100, 5);
		GPlugin->AddCheckBox("Soulbound", "Save.Death", "^-> On damage > health", true);
		GPlugin->AddCheckBox("Soulbound", "Save.SpecialSpells", "^-> On Special Spell Detection", false);

		GPlugin->AddMenu("SpecialSpells", "Special Spell Detection", "Soulbound");
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				auto championName = std::string(const_cast<char*>(enemy->GetBaseSkinName()));

				for (auto champion : SpellDatabase::Champions)
				{
					if (champion.first != championName)
						continue;

					GPlugin->AddMenu(const_cast<char*>(championName.c_str()), const_cast<char*>(GExtension->format(" %s Spells", champion.second.DisplayName).c_str()), "SpecialSpells");
					{
						auto spells = champion.second.Spells;

						for (auto spell : spells)
						{
							GPlugin->AddMenu(spell.Name, const_cast<char*>(GExtension->format("%s (%s)", spell.DisplayName, SpellDatabase::Slots[spell.Slot]).c_str()), const_cast<char*>(championName.c_str()));
							{
								GPlugin->AddCheckBox(spell.Name, "Use", const_cast<char*>(GExtension->format("Use for %s", spell.DisplayName).c_str()), spell.Dangerous);
								GPlugin->AddInteger(spell.Name, "Use.Health", const_cast<char*>(GExtension->format("Use for %s under {x}%% health", spell.DisplayName).c_str()), 0, 100, spell.Health);
							}
						}
					}
				}
			}
		}
	}

	GPlugin->AddMenu("Misc", "ii | Misc");
	{
		GPlugin->AddInteger("Misc", "E.Delay", "E Delay (ms)", 0, 1000, 0);
		GPlugin->AddCheckBox("Misc", "E.Unkillable", "Use E to lasthit unkillable minions", true);
		GPlugin->AddCheckBox("Misc", "E.Killsteal", "Always Killsteal w/ E", true);
		GPlugin->AddInteger("Misc", "E.DamageReduction", "E Damage Reduction", 0, 100, 20);
		GPlugin->AddCheckBox("Misc", "E.Death", "Use E before Death", true);
		GPlugin->AddInteger("Misc", "E.Death.Health", "^-> Use on {x}% health", 1, 30, 12);
		GPlugin->AddInteger("Misc", "E.Death.Heroes", "^-> Minimum Champions w/ Stacks", 1, 5, 1);
		GPlugin->AddInteger("Misc", "E.Death.Stacks", "    ^-> Minimum Stacks on that Champions", 1, 10, 1);
	}
}
