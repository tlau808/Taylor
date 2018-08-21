// Game.h
// Taylor Lau: t.lau@wustl.edu
// Header file for Game.cpp
#pragma once
#include "Deck.h"
#include "Player.h"

class game {
protected:
	static shared_ptr<game> poker;
	deck main;
	vector<shared_ptr<player>> players;

public:
	static shared_ptr<game> instance();
	static void start_game(const string& name);
	static void stop_game();
	void add_player(const string& p1);
	shared_ptr<player> find_player(const string name);
	virtual ~game() {};
	virtual int before_turn(player& p1) = 0;
	virtual int turn(player& p1) = 0;
	virtual int after_turn(player& p1) = 0;
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round() = 0;
	virtual int numPlayers();
};