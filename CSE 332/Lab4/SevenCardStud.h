// SevenCardStud.h
// Taylor Lau: t.lau@wustl.edu
// Header for SevenCardStud.cpp
#pragma once
#include "Game.h"

class SevenCardStud : public game {
protected:
	deck muck;

public:
	SevenCardStud();
	void bet();
	virtual int before_turn(player& joe);
	virtual int turn(player& joe);
	virtual int after_turn(player& joe);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
};