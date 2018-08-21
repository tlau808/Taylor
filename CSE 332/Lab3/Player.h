// Player.h
// Taylor Lau: t.lau@wustl.edu
// Header for Player.cpp
#pragma once
#include "Hand.h"

struct player {
	string name;
	hand hand;
	unsigned int wins;
	unsigned int losses;

	player(string person);
	friend ostream& operator<< (ostream& out, const player& p1);
};