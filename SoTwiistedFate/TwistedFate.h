#pragma once

class TwistedFate
{
public:
	enum Card {
		kCardYellow,
		kCardBlue,
		kCardRed,
		kCardNone
	};

	static int LastPingTick;
	static Card SelectedCard;
};

