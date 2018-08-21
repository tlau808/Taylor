// Game.cpp
// Taylor Lau: t.lau@wustl.edu
// Game class. Methods to start, stop, and control players in a game.
#pragma once
#include "stdafx.h"
#include "Game.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"

shared_ptr<game> game::poker = 0;

shared_ptr<game> game::instance() {
	if (poker == 0) { throw exception("instance not available"); }
	shared_ptr<game> pokerCopy = poker;
	return pokerCopy;
}

void game::start_game(const string& name) {
	if (poker != 0) { throw exception("game already started"); }
	if (name == "FiveCardDraw") {
		shared_ptr<FiveCardDraw> g = make_shared<FiveCardDraw>();
		poker = g;
	}
	else if (name == "SevenCardStud") {
		shared_ptr<SevenCardStud> g = make_shared<SevenCardStud>();
		poker = g;
	}
	else { throw exception("unknown game"); }
}

void game::stop_game() {
	if (poker == 0) { throw exception("no game in progress"); }
	poker = 0;
}

void game::add_player(const string& p1) {
	shared_ptr<player> taylor = find_player(p1);
	shared_ptr<player> newPlay = make_shared<player>(p1);
	if (taylor != 0) { throw exception("already playing"); }
	else players.push_back(newPlay);
}

shared_ptr<player> game::find_player(const string name) {
	vector<shared_ptr<player>>::iterator iter;
	for (iter = players.begin(); iter != players.end(); ++iter) {
		shared_ptr<player> p1 = *iter;
		player bob = *p1;
		if (bob.name == name) { return p1; }
	}
	shared_ptr<player> noPlay;
	return noPlay;
}

int game::numPlayers() { return players.size(); }

bool game::poker_rank(shared_ptr<player> p1, shared_ptr<player> p2) {
	if (p1 == 0) { return false; }
	if (p2 == 0) { return true; }
	if (card::pokerRank((*p1).hand.cards) < card::pokerRank((*p2).hand.cards)) { return true; }
	return false;
}

bool game::optimal_rank(shared_ptr<player> p1, shared_ptr<player> p2) {
	if (p1 == 0) { return false; }
	if (p2 == 0) { return true; }
	if (card::optimalRank((*p1).hand.cards) < card::optimalRank((*p2).hand.cards)) { return true; }
	return false;
}