#include "SpellDatabase.h"

std::map<eSpellSlot, char*> SpellDatabase::Slots{
	{ kSlotQ, "Q" },
	{ kSlotW, "W" },
	{ kSlotE, "E" },
	{ kSlotR, "R" }
};


// eSpellSlot, char* Name, char* DisplayName, int Health, bool Dangerous, int Delay, int Radius, int Speed, int Range, bool Missile, bool AoE, eSpellType SpellType, eCollisionFlags Collisions 
std::map<char*, SpellDatabase::Champion> SpellDatabase::Champions{
	{ "Aatrox",{
		"Aatrox",{
			{ kSlotQ, "AatroxQ", "Dark Flight", 0, false, 600, 285, 3050, 650, false, true, kCircleCast, kCollidesWithNothing }
		}
	}
	},
	{ "Ahri",{
		"Ahri",{
			{ kSlotE, "AhriSeduce", "Charm", 0, false, 0, 60, 1550, 1000, true, false, kLineCast, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall) }
		}
	}
	},
	{ "Alistar",{
		"Alistar",{
			{ kSlotQ, "Pulverize", "Pulverize", 0, false, 0, 365, 0, 0, false, true, kCircleCast, kCollidesWithNothing }
		}
	}
	},
	{ "Amumu",{
		"Amumu",{
			{ kSlotQ, "BandageToss", "Bandage Toss", 0, false, 0, 80, 2000, 1100, true, false, kLineCast, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall) },
			{ kSlotR, "CurseoftheSadMummy", "Curse of the Sad Mummy", 0, true, 0, 550, 0, 0, false, true, kCircleCast, kCollidesWithNothing }
		}
	}
	},
	{ "Annie",{
		"Annie",{
			{ kSlotR, "InfernalGuardian", "Summoner: Tibbers", 0, true, 0, 250, 0, 600, false, true, kCircleCast, kCollidesWithNothing },
		}
	}
	},
	{ "Ashe",{
		"Ashe",{
			{ kSlotW, "Volley", "Volley", 0, false, 0, 20, 1500, 1150, true, true, kConeCast, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall) },
			{ kSlotR, "EnchantedCrystalArrow", "Enchanted Crystal Arrow", 0, true, 0, 130, 1600, 25000, true, false, kLineCast,  static_cast<eCollisionFlags>(kCollidesWithHeroes | kCollidesWithYasuoWall) }
		}
	}
	},
	{ "AurelionSol",{
		"Aurelion Sol",{
			{ kSlotQ, "AurelionSolQ", "Starsurge", 0, false, 0, 210, 850, 550, true, true, kLineCast, kCollidesWithYasuoWall },
			{ kSlotR, "AurelionSolR", "Voice of Light", 0, false, 350, 120, 4500, 1500, true, true, kLineCast, kCollidesWithNothing }
		}
	}
	},
	{ "Azir",{
		"Azir",{
			{ kSlotR, "AzirR", "Emperors Divide", 0, false, 0, 150, 1400, 750, false, true, kLineCast, kCollidesWithNothing }
		}
	}
	},
	{ "Bard",{
		"Bard",{
			{ kSlotQ, "BardQ", "Cosmic Binding", 0, false, 0, 60, 1500, 950, true, false, kLineCast, static_cast<eCollisionFlags>(kCollidesWithHeroes | kCollidesWithMinions | kCollidesWithYasuoWall) },
			{ kSlotR, "BardR", "Tempered Fate", 0, false, 500, 350, 500, 3400, true, true, kCircleCast, kCollidesWithNothing }
		}
	}
	},
	{ "Blitzcrank",{
		"Blitzcrank",{
			{ kSlotQ, "RocketGrab", "Rocket Grab", 0, true, 0, 85, 1800, 1050, true, false, kLineCast, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall) }
		}
	}
	},
	{ "Brand",{
		"Brand",{
			{ kSlotQ, "BrandQ", "Sear", 0, false, 0, 60, 1600, 1100, true, false, kLineCast, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall) },
			{ kSlotR, "BrandR", "Pyroclasm", 0, true, 90, 1600, 0, 750, false, true, kTargetCast, kCollidesWithNothing }
		}
	}
	},
	{ "Braum",{
		"Braum",{
			{ kSlotQ, "BraumQ", "Winters Bite", 0, false, 0, 60, 1700, 1050, true, false, kLineCast, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall) },
			{ kSlotR, "BraumRWrapper", "Glacial Fissure", 0, true, 550, 115, 1400, 1200, true, true, kLineCast, kCollidesWithYasuoWall }
		}
	}
	},
	{ "Caitlyn",{
		"Caitlyn",{
			{ kSlotR, "CaitlynAceintheHole", "Ace in the Hole", 0, true, 1000, 70, 3200, 3000, true, false, kTargetCast, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall) }
		}
	}
	},
	{ "Camille",{
		"Camille",{
			{ kSlotE, "CamilleEDash2", "Hookshot", 0, false, 250, 80, 2500, 800, false, false, kLineCast, kCollidesWithHeroes }
		}
	}
	},
	{ "Cassiopeia",{
		"Cassiopeia",{
			{ kSlotR, "CassiopeiaR", "Petrifying Gaze", 0, true, 500, 80, 0, 790, false, true, kConeCast, kCollidesWithNothing }
		}
	}
	},
	{ "Chogath",{
		"ChoGath",{
			{ kSlotQ, "Rupture", "Rupture", 0, false, 1200, 250, 0, 950, false, true, kCircleCast, kCollidesWithNothing },
			{ kSlotR, "Feast", "Feast", 0, true, 50, 0, 0, 175, false, false, kTargetCast, kCollidesWithNothing }
		}
	}
	},
	{ "Darius",{
		"Darius",{
			{ kSlotE, "DariusAxeGrabCone", "Apprehend", 0, false, 0, 50, 0, 510, false, true, kConeCast,  kCollidesWithNothing },
			{ kSlotR, "DariusExecute", "Noxian Guillotine", 0, true, 500, 0, 20, 460, false, false, kTargetCast, kCollidesWithNothing }
		}
	}
	},
	{ "Diana",{
		"Diana",{
			{ kSlotE, "DianaVortex", "Moonfall", 0, false, 0, 450, 0, 0, false, false, kCircleCast, kCollidesWithNothing }
		}
	}
	},
	{ "Draven",{
		"Draven",{
			{ kSlotE, "DravenDoubleShot", "Stand Aside", 0, false, 0, 130, 1400, 1100, true, true, kLineCast, kCollidesWithYasuoWall },
			{ kSlotR, "DravenRCast", "Whirling Death", 0, true, 525, 160, 2000, 50000, true, true, kLineCast, kCollidesWithYasuoWall }
		}
	}
	},
	{ "Ekko",{
		"Ekko",{
			{ kSlotR, "EkkoR", "Chronobreak", 0, true, 0, 375, 1650, 20000, true, true, kLineCast, kCollidesWithNothing }
		}
	}
	},
	{ "Elise",{
		"Elise",{
			{ kSlotE, "EliseHumanE", "Cocoon", 0, false, 0, 55, 1600, 1100, true, false, kLineCast, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall) }
		}
	}
	},
	{ "Evelynn",{
		"Evelynn",{
			{ kSlotR, "EvelynnR", "Agonys Embrace", 0, true, 0, 350, 0, 650, false, true, kCircleCast, kCollidesWithNothing }
		}
	}
	},
	{ "Ezreal",{
		"Ezreal",{
			{ kSlotR, "EzrealTrueshotBarrage", "Trueshot Barrage", 0, true, 1000, 160, 2000, 50000, true, true, kLineCast, kCollidesWithYasuoWall }
		}
	}
	},
	{ "Fizz",{
		"Fizz",{
			{ kSlotQ, "FizzQ", "Urchin Strike", 0, false, 250, 60, 3000, 550, false, false, kTargetCast, kCollidesWithNothing },
			{ kSlotR, "FizzR", "Chum the Waters", 0, true, 250, 110, 1300, 1275, true, false, kLineCast, static_cast<eCollisionFlags>(kCollidesWithHeroes | kCollidesWithYasuoWall) }
		}
	}
	},
	{ "Gnar",{
		"Gnar",{
			{ kSlotW, "GnarBigW", "Wallop", 0, false, 600, 110, 0, 600, false, true, kCircleCast, kCollidesWithNothing },
			{ kSlotR, "GnarR", "GNAR!", 0, true, 275, 500, 0, 0, false, true, kCircleCast, kCollidesWithNothing }
		}
	}
	},
	{ "Gragas",{
		"Gragas",{
			{ kSlotE, "GragasE", "Body Slam", 0, false, 0, 200, 900, 600, true, true, kLineCast, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes) },
			{ kSlotR, "GragasR", "Explosive Cask", 0, true, 0, 350, 1800, 1050, true, true, kCircleCast, kCollidesWithYasuoWall }
		}
	}
	},
	{ "Graves",{
		"Graves",{
			{ kSlotQ, "GravesQLineSpell", "End of the Line", 0, false, 0, 40, 3000, 808, true, true, kLineCast, static_cast<eCollisionFlags>(kCollidesWithWalls | kCollidesWithYasuoWall) },
			{ kSlotR, "GravesChargeShot", "Collateral Damage", 0, true, 0, 100, 2100, 1000, true, true, kLineCast, kCollidesWithYasuoWall }
		}
	}
	},
	{ "Hecarim",{
		"Hecarim",{
			{ kSlotR, "HecarimUlt", "Onslaught of Shadows", 0, true, 0, 240, 1100, 1000, false, true, kCircleCast, kCollidesWithNothing }
		}
	}
	},
	{ "Illaoi",{
		"Illaoi",{
			{ kSlotR, "IllaoiR", "Leap of Faith", 0, true, 500, 450, 0, 0, false, true, kCircleCast, kCollidesWithNothing }
		}
	}
	},
	{ "Irelia",{
		"Irelia",{
			{ kSlotE, "IreliaEquilibriumStrike", "Equilibrium Strike", 0, true, 500, 0, 0, 325, false, false, kTargetCast, kCollidesWithNothing }
		}
	}
	},
	{ "Ivern",{
		"Ivern",{
			{ kSlotQ, "IvernQ", "Rootcaller", 0, false, 0, 65, 1300, 1100, true, false, kLineCast, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall) }
		}
	}
	},
	{ "JarvanIV",{
		"Jarvan IV",{
			{ kSlotE, "JarvanIVQE", "Demacian Standard (QE)", 0, true, 450, 120, 2600, 910, false, true, kCircleCast, kCollidesWithNothing },
			{ kSlotR, "JarvanIVCataclysm", "Cataclysm", 0, true, 0, 340, 1850, 650, kCollidesWithNothing }
		}
	}
	},
	{ "Jayce",{
		"Jayce",{
			{ kSlotQ, "JayceQAccel", "Shock Blast (EQ)", 0, true, 0, 70, 2350, 2000, true, true, kLineCast, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall) }
		}
	}
	},
	{ "Jhin",{
		"Jhin",{
			{ kSlotW, "JhinW", "Deadly Flourish", 0, false, 750, 40, 0, 2550, true, false, kLineCast, static_cast<eCollisionFlags>(kCollidesWithHeroes | kCollidesWithYasuoWall) },
			{ kSlotR, "JhinRShot", "Curtain Call", 0, true, 190, 80, 5000, 3500, true, false, kLineCast, static_cast<eCollisionFlags>(kCollidesWithHeroes | kCollidesWithYasuoWall) }
		}
	}
	},
	{ "Jinx",{
		"Jinx",{
			{ kSlotW, "JinxWMissile", "Zap!", 0, false, 600, 60, 3300, 1500, true, false, kLineCast, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall) },
			{ kSlotR, "JinxR", "Super Mega Death Rocket!", 0, true, 600, 140, 1700, 50000, true, true, kLineCast, static_cast<eCollisionFlags>(kCollidesWithHeroes | kCollidesWithYasuoWall) }
		}
	}
	},
	{ "Karma",{
		"Karma",{
			{ kSlotQ, "KarmaQMantra", "Inner Flame (RQ)", 0, false, 0, 80, 1700, 950, true, true, kLineCast, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall) }
		}
	}
	},
	{ "Karthus",{
		"Karthus",{
			{ kSlotR, "FallenOne", "Requiem", 0, true, 3125, 0, 0, 50000, true, false, kTargetCast, kCollidesWithNothing }
		}
	}
	},
	{ "LeeSin",{
		"Lee Sin",{
			{ kSlotR, "BlindMonkRKick", "Dragons Rage", 0, true, 500, 0, 1500, 375, false, false, kTargetCast, kCollidesWithNothing }
		}
	}
	},
	{ "Leona",{
		"Leona",{
			{ kSlotE, "LeonaZenithBlade", "Zenith Blade", 0, false, 0, 70, 2000, 900, true, false, kLineCast, static_cast<eCollisionFlags>(kCollidesWithHeroes | kCollidesWithYasuoWall) },
			{ kSlotR, "LeonaSolarFlare", "Solar Flare", 0, true, 930, 300, 0, 1200, false, true, kCircleCast, kCollidesWithNothing },
		}
	}
	},
	{ "Lissandra",{
		"Lissandra",{
			{ kSlotR, "LissandraR", "Frozen Tomb", 0, true, 0, 0, 0, 550, false, true, kTargetCast, kCollidesWithNothing }
		}
	}
	},
	{ "Lux",{
		"Lux",{
			{ kSlotR, "LuxMaliceCannon", "Final Spark", 0, true, 1000, 150, 0, 3300, false, true, kLineCast, kCollidesWithNothing }
		}
	}
	},
	{ "Malphite",{
		"Malphite",{
			{ kSlotR, "UFSlash", "Unstoppable Force", 0, true, 0, 270, 1600, 1000, false, true, kCircleCast, kCollidesWithNothing }
		}
	}
	},
	{ "Nami",{
		"Nami",{
			{ kSlotQ, "NamiQ", "Aqua Prison", 0, false, 700, 200, 2500, 850, true, true, kCircleCast, kCollidesWithYasuoWall },
			{ kSlotR, "NamiRMissile", "Tidal Wave", 0, true, 500, 250, 850, 2750, true, true, kLineCast, kCollidesWithYasuoWall }
		}
	}
	},
	{ "Nautilus",{
		"Nautilus",{
			{ kSlotQ, "NautilusAnchorDragMissile", "Dredge Line", 0, false, 0, 90, 2000, 1150, true, false, kLineCast, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall) },
			{ kSlotR, "NautilusGandLine", "Depth Charge", 0, false, 500, 60, 1400, 1500, false, true, kTargetCast, kCollidesWithNothing }
		}
	}
	}
};

