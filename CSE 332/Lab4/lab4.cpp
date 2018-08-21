// lab4.cpp
// Taylor Lau: t.lau@wustl.edu
// Main method that plays a game of poker until one player remains. Then the user may play another game or discontinue.
#pragma once
#include "stdafx.h"
#include "FiveCardDraw.h"

int main(int argc, char * argv[]) {
	if (argc < 4) {
		cout << "Usage: supply a type of game and 2+ players";
		return 1;
	}

	if (argc > 12) {
		cout << "Usage: too many players for a 52 card deck";
		return 2;
	}

	try {
		string choice = argv[1];
		vector<string> players;
		for (int i = 2; i < argc; ++i) { players.push_back(argv[i]); }
		while (true) {
			game::start_game(choice);
			shared_ptr<game> poker = game::instance();
			for (size_t j = 0; j < players.size(); ++j) { poker->add_player(players[j]); }

			// play rounds while there are two or more players
			while (poker->numPlayers() > 1) {
				poker->before_round();
				poker->round();
				poker->after_round();
			}
			game::stop_game();

			// play a new game or stop
			while (true) {
				cout << "Insufficient players remain. Play a new game? Yes or no:" << endl;
				string yn;
				cin >> yn;
				if (yn == "no") { return 0; }
				if (yn == "yes") { break; }
			}

			// choose a game
			while (true) {
				cout << "Which game? FiveCardDraw or SevenCardStud:" << endl;
				cin >> choice;
				if (choice != "FiveCardDraw" && choice != "SevenCardStud") { continue; }
				break;
			}
			
			// add players
			players.clear();
			while (true) {
				cout << "Add a player to the new game. Enter 'play' when you are done:" << endl;
				string p1;
				cin >> p1;
				if (p1 == "play") { break; }
				players.push_back(p1);
			}
		}
	}
	catch (const exception& e) {
		cout << "exception: " << e.what();
		return 4;
	}
	return 0;
}