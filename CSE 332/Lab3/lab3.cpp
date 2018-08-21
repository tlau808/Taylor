// lab3.cpp
// Taylor Lau: t.lau@wustl.edu
// Main method that starts, deals, and stops a game. Today we will play five card draw.
#pragma once
#include "stdafx.h"
#include "FiveCardDraw.h"

int main(int argc, char * argv[]) {
	// check for reasonable arguments
	if (argc < 4) {
		cout << "Usage: supply a type of game and 2+ players";
		return 1;
	}

	if (argc > 12) {
		cout << "Usage: too many players for a 52 card deck";
		return 2;
	}

	try {
		game::start_game(argv[1]);
		shared_ptr<game> five = game::instance();
		for (int i = 2; i < argc; ++i) { five->add_player(argv[i]); }

		// play rounds while there are two or more players
		while (five->numPlayers() > 1) {
			five->before_round();
			five->round();
			five->after_round();
		}
		game::stop_game();
		return 0;
	}
	catch (const exception& e) {
		cout << "exception: " << e.what();
		return 4;
	}

};
// lab3.exe FiveCardDraw bill kate rick sara matt