// FiveCardDraw.h
// Taylor Lau: t.lau@wustl.edu
// Header for FiveCardDraw.cpp
#pragma once
#include "Game.h"

class FiveCardDraw : public game {
protected:
	size_t dealer;
	deck muck;

public:
	FiveCardDraw();
	virtual int before_turn(player& joe);
	virtual int turn(player& joe);
	virtual int after_turn(player& joe);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
};