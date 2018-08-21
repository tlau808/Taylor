// Taylor Lau: t.lau@wustl.edu
// Lab 2
// Main function deals the game of poker
#include "stdafx.h"
#include "Deck.h"
#include "Hand.h"

bool poker_rank(const hand player1, const hand player2) {
	if (pokerRank(player1.cards) > pokerRank(player2.cards)) { return true; }
	return false;
}

int main(int argc, char* argv[]) {
	deck bicycle;

	// make sure the input is appropriate
	try {
		if (argc == 1) {throw 1;}
	}
	catch (int i) {
		cout << "Exception " << i << ": Provide a deck and perhaps '-shuffle'";
		return i;
	}

	string arg1 = argv[1];
	try {
		if (argc == 2) {
			if (arg1 == "-shuffle") {throw 2;}
			bicycle = deck(argv[1]);
		}
	}
	catch (int i) {
		cout << "Exception " << i << ": You can't shuffle without a deck";
		return i;
	}

	try {
		if (argc == 3) {
			string arg2 = argv[2];
			if (arg1 == "-shuffle") {
				bicycle = deck(argv[2]);
				bicycle.shuffle();
			}
			else if (arg2 == "-shuffle") {
				bicycle = deck(argv[1]);
				bicycle.shuffle();
			}
			else { throw 3; }
		}
	}
	catch (int i) {
		cout << "Exception " << i << ": If you provide two arguments, one must be '-shuffle' and the other a deck";
		return i;
	}

	try {
		if (argc > 3) {throw 4;}
	}
	catch (int i) {
		cout << "Exception " << i << ": Delete extraneous arguments";
		return i;
	}

	int deckSize = bicycle.size();

	// create empty hands
	vector<hand> players;
	for (int i = 0; i <= 8; ++i) { players.push_back(hand()); }

	// deal cards
	for (int i = 1; i <= 5; ++i) {
		for (int j = 0; j <= 8; ++j) {
			if (bicycle.size() == 0) { break; }
			players[j] << bicycle;
		}
	}

	// PRINT 1: unordered hands and deck
	cout << "Here are the hands everybody was dealt:" << endl;
	for (int i = 0; i <= 8; ++i) {
		players[i].asString();
		cout << endl;
	}
	cout << "The rest of the deck:" << endl << bicycle;
	cout << endl << endl;

	// PRINT 2: hands in lexical order
	sort(players.begin(), players.end());
	cout << "Here are the hands in ascending lexical order:" << endl;
	for (int i = 0; i <= 8; ++i) {
		players[i].asString();
		cout << endl;
	}
	cout << endl;

	// PRINT 3: hands in poker rank order
	try {
		if (deckSize < 45) { throw 5; }
	}
	catch (int i) {
		cout << "Not all players had five card hands. Poker ranks do not apply";
		return i;
	}
	sort(players.begin(), players.end(), poker_rank);
	cout << "Here are the hands in descending poker rank order:" << endl;
	for (int i = 0; i <= 8; ++i) {
		players[i].asString();
		pokerString(players[i].cards);
		cout << endl;
	}
	return 0;
}