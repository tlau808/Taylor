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
	int chips;
	int myBet; // total number of chips committed during a round
	bool fold; // true if folded
	player(string person);
	friend ostream& operator<< (ostream& out, const player& p1);
};