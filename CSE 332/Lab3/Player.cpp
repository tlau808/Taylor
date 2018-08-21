// Player.cpp
// Taylor Lau: t.lau@wustl.edu
// Player struct. Methods to construct and print a player.
#pragma once
#include "stdafx.h"
#include "Player.h"
player::player(string person) {
	name = person;
	wins = 0;
	losses = 0;
	string playerFile = person + ".txt";
	ifstream ifs(playerFile);
	if (ifs.is_open()) {
		ifs >> name;
		ifs >> wins;
		ifs >> losses;
	}
}

 ostream& operator<< (ostream& out, const player& p1) {
	out << p1.name << ": ";
	out << p1.wins << " win(s), ";
	out << p1.losses << " loss(es)";
	return out;
}