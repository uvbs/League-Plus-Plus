#include "Plugin.h"
#include "Menu.h"

void Menu::Initialize()
{
	GPlugin->AddMenu("Drawings", "ii | Drawings");
	{
		GPlugin->AddCheckBox("Drawings", "Q", "Draw Q Range", true);
		GPlugin->AddColor("Drawings", "W.Color", "^-> Q Color", 122, 219, 140, 255);
		GPlugin->AddCheckBox("Drawings", "W", "Draw W Range", true);
		GPlugin->AddColor("Drawings", "W.Color", "^-> W Color", 147, 122, 219, 255);
		GPlugin->AddCheckBox("Drawings", "E", "Draw E Range", false);
		GPlugin->AddColor("Drawings", "E.Color", "^-> E Color", 205, 92, 92, 255);
		GPlugin->AddCheckBox("Drawings", "R.Minimum", "Draw minimum R Range", true);
		GPlugin->AddColor("Drawings", "R.Minimum.Color", "^-> Minimum R Color", 139, 0, 0, 255);
		GPlugin->AddCheckBox("Drawings", "R.Maximum", "Draw maximum R Range", true);
		GPlugin->AddColor("Drawings", "R.Maximum.Color", "^-> Maximum R Color", 139, 0, 0, 255);
		GPlugin->AddSelection("Drawings", "Harass.Q", "Draws Q Harass Mode", 3, { "Disabled", "Texture", "Text", "Both" });
		GPlugin->AddInteger("Drawings", "Harass.Q.Texture.X", "Harass Texture X", 0, GRender->ScreenSize().x, GRender->ScreenSize().x / 2 - 72);
		GPlugin->AddInteger("Drawings", "Harass.Q.Texture.Y", "Harass Texture Y", 0, GRender->ScreenSize().y, 0);
		GPlugin->AddCheckBox("Drawings", "Ready", "Draw only if spell is ready", true);
	}

	GPlugin->AddMenu("Combo", "ii | Combo Settings");
	{
		GPlugin->AddCheckBox("Combo", "Q", "Use Q", true);
		GPlugin->AddInteger("Combo", "Q.Enemies", "^-> Force Fishbone if can hit {x} champions", 2, 5, 2);
		GPlugin->AddCheckBox("Combo", "Q.Enemies.Range", "    ^-> Only use out of minigun range", true);
		GPlugin->AddInteger("Combo", "Q.Mana", "^-> Minimum Mana for Q", 0, 100, 20);
		GPlugin->AddInteger("Combo", "Q.Mana.Ignore", "^-> Ignore mana if can kill in {x} autoattacks", 3, 10, 4); 
		GPlugin->AddCheckBox("Combo", "W", "Use W", true);
		GPlugin->AddInteger("Combo", "W.Range", "^-> Minimum Range for W", 0, 1400, 750);
		GPlugin->AddSelection("Combo", "W.Mode", "^-> Target Selection", 1, { "QuickestKill", "ClosestPriority", "ClosestToCursorPriority", "LowestHealthPriority", "MostStacks", "MostAD", "MostAP", "LeastAttacks", "LeastCasts" });
		GPlugin->AddInteger("Combo", "W.Mana", "^-> Minimum Mana for W", 0, 100, 20);
		GPlugin->AddCheckBox("Combo", "E", "Use E (BUGGY AF)", false);
		GPlugin->AddInteger("Combo", "E.Mana", "^-> Minimum Mana for E", 0, 100, 20);
	}

	GPlugin->AddMenu("Harass", "ii | Harass Settings");
	{
		GPlugin->AddToggle("Harass", "Q", "Use Q", false, 'Y');
		GPlugin->AddCheckBox("Harass", "Q.Minions", "^-> Use Q to harass enemies w/ area damage while lasthitting", true);
		GPlugin->AddInteger("Harass", "Q.Mana", "^-> Minimum Mana for Q", 0, 100, 40);
		GPlugin->AddCheckBox("Harass", "W", "Use W", true);
		GPlugin->AddInteger("Harass", "W.Mana", "^-> Minimum Mana for W", 0, 100, 40);
	}

	GPlugin->AddMenu("Clear", "ii | Clear Settings");
	{
		GPlugin->AddCheckBox("Clear", "Q", "Use Q", true);
		GPlugin->AddCheckBox("Clear", "Q.Lasthit", "^-> Use Fishbone to lasthit out of range minions", false);
		GPlugin->AddInteger("Clear", "Q.Enemies", "^-> Force Fishbone if can hit {x} minions", 2, 10, 3);
		GPlugin->AddInteger("Clear", "Q.Mana", "^-> Minimum Mana for Q", 0, 100, 65);
	}

	GPlugin->AddMenu("KillSteal", "ii | KillSteal Settings");
	{
		GPlugin->AddCheckBox("KillSteal", "W", "Use W", true);
		GPlugin->AddInteger("KillSteal", "W.Range", "^-> Minimum Range for W", 0, 1400, 750);
		GPlugin->AddCheckBox("KillSteal", "R", "Use R", true);
		GPlugin->AddCheckBox("KillSteal", "R.Overkill", "^-> Dont use if W is enough", true);
		GPlugin->AddInteger("KillSteal", "R.Allies", "^-> Dont steal if allies near target in {x} range", 0, 1000, 500);
	}

	GPlugin->AddMenu("W.Auto", "ii | Auto W");
	{
		GPlugin->AddCheckBox("W.Auto", "OnCC", "Use on hard CC", false);
		GPlugin->AddCheckBox("W.Auto", "OnSlow", "Use on slow", false);
		GPlugin->AddCheckBox("W.Auto", "OnDash", "Use on dash", false);
		GPlugin->AddCheckBox("W.Auto", "OnSpecialSpell", "Use on special spell detection", false);
		GPlugin->AddInteger("W.Auto", "Mana", "^-> Minimum Mana for W", 0, 100, 65);
	}

	GPlugin->AddMenu("E.Auto", "ii | Auto E");
	{
		GPlugin->AddCheckBox("E.Auto", "OnTeleport", "Use on enemy teleport", true);
		GPlugin->AddCheckBox("E.Auto", "OnCC", "Use on hard CC", true);
		GPlugin->AddCheckBox("E.Auto", "OnSlow", "Use on slow", false);
		GPlugin->AddCheckBox("E.Auto", "OnDash", "Use on dash", true);
		GPlugin->AddCheckBox("E.Auto", "OnGapCloser", "Use on gapclosers", true);
		GPlugin->AddCheckBox("E.Auto", "OnSpecialSpell", "Use on special spell detection", false);
		GPlugin->AddCheckBox("E.Auto", "OnArea", "Use if can hit multiple champions", false);
		GPlugin->AddInteger("E.Auto", "OnArea.Enemies", "^-> if can hit {x} champions", 2, 5, 3);
		GPlugin->AddInteger("E.Auto", "Mana", "^-> Minimum Mana for E", 0, 100, 50);
	}

	GPlugin->AddMenu("Misc", "ii | Misc");
	{
		GPlugin->AddKey("Misc", "W.Key", "Semi manual cast W", 'X'); 
		GPlugin->AddSelection("Misc", "W.Hitchance", "W Hitchance", 3, { "Low", "Medium", "High", "Very High" }); 
		GPlugin->AddKey("Misc", "R.Key", "Semi manual cast R", 'T');
		GPlugin->AddSelection("Misc", "R.Key.Mode", "^-> Mode", 0, { "low HP", "AoE" });
		GPlugin->AddInteger("Misc", "R.Range.Minimum", "R minimum range", 0, 5000, 800);
		GPlugin->AddInteger("Misc", "R.Range.Maximum", "R maximum range", 0, 10000, 3000);
	}
}
