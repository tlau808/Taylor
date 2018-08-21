// FiveCardDraw.cpp
// Taylor Lau: t.lau@wustl.edu
// FiveCardDraw class. Inherited from game. Methods for turns and rounds for this variant of poker
#pragma once
#include "stdafx.h"
#include "FiveCardDraw.h"

bool poker_rank(shared_ptr<player> p1, shared_ptr<player> p2) {
	if (p1 == 0) { return false; }
	if (p2 == 0) { return true; }
	if (card::pokerRank((*p1).hand.cards) < card::pokerRank((*p2).hand.cards)) { return true; }
	return false;
}

FiveCardDraw::FiveCardDraw() {
	dealer = 0;
	for (int i = 2; i <= 14; ++i) {
		for (int j = 1; j <= 4; ++j) { main.add_card(card(i, j)); }
	}
}

int FiveCardDraw::before_turn(player& joe) {
	cout << joe.name << ": " << endl;
	while (true) {
		cout << joe.hand;
		cout << endl;
		cout << "give a position (1-5) to discard. Or '0' to discard nothing" << endl;
		string discard;
		cin >> discard;

		// check whether the position is valid
		if (discard == "0") { break; }
		if (discard != "1" && discard != "2" && discard != "3" && discard != "4" && discard != "5") {
			cout << "invalid position" << endl;
			continue;
		}
		int position = stoi(discard);
		if (position > joe.hand.size()) {
			cout << "invalid position" << endl;
			continue;
		}

		// add to the discard deck, remove from hand
		muck.add_card(joe.hand[position - 1]);
		joe.hand.remove_card(position);
		if (joe.hand.size() == 0) { break; }
	}
	return 0;
}

int FiveCardDraw::turn(player& joe) {
	int makeFive = 5 - joe.hand.size();

	// deal cards to make a five card hand. prioritze the main deck
	for (int i = 1; i <= makeFive; ++i) {
		if (main.size() == 0) {
			muck.shuffle();
			if (muck.size() == 0) { return 3; }
			joe.hand << muck;
		}
		else { joe.hand << main; }
	}
	return 0;
}

int FiveCardDraw::after_turn(player& joe) {
	cout << joe.name << ": " << joe.hand;
	cout << endl;
	return 0;
}

int FiveCardDraw::before_round() {
	main.shuffle();

	// deal cards
	for (int i = 1; i <= 5; ++i) {
		for (size_t j = dealer + 1; j < players.size(); ++j) { (*players[j]).hand << main; }
		for (size_t j = 0; j <= dealer; ++j) { (*players[j]).hand << main; }
	}

	// players act
	for (size_t j = dealer + 1; j < players.size(); ++j) { before_turn(*players[j]); }
	for (size_t j = 0; j <= dealer; ++j) { before_turn(*players[j]); }
	return 0;
}

int FiveCardDraw::round() {
	// fill up hands and print
	for (size_t j = dealer + 1; j < players.size(); ++j) {
		if (turn((*players[j])) != 0) { return turn(*players[j]); }
		turn(*players[j]);
		after_turn(*players[j]);
	}
	for (size_t j = 0; j <= dealer; ++j) {
		if (turn((*players[j])) != 0) { return turn(*players[j]); }
		turn(*players[j]);
		after_turn(*players[j]);
	}
	return 0;
}

int FiveCardDraw::after_round() {
	// print sorted players
	vector<shared_ptr<player>> tempPlayers = players;
	sort(tempPlayers.begin(), tempPlayers.end(), poker_rank);
	reverse(tempPlayers.begin(), tempPlayers.end());
	shared_ptr<player> winner = tempPlayers.front();
	int highestRank = card::pokerRank((*winner).hand.cards);
	vector<shared_ptr<player>>::iterator iter;
	for (iter = tempPlayers.begin(); iter != tempPlayers.end(); ++iter) {
		if (card::pokerRank((**iter).hand.cards) == highestRank) { (**iter).wins++; }
		else (**iter).losses++;
		cout << (**iter) << " / " << (**iter).hand;
		cout << "/ ";
		cout << card::pokerString((**iter).hand.cards);
		cout << endl;
	}

	// reset main deck, discard deck, hands
	main = deck();
	for (int i = 2; i <= 14; ++i) {
		for (int j = 1; j <= 4; ++j) {
			main.add_card(card(i, j));
		}
	}
	muck = deck();
	vector<shared_ptr<player>>::iterator iter2;
	for (iter2 = players.begin(); iter2 != players.end(); ++iter2) { (**iter2).hand = hand(); }

	// remove players
	string quitter;
	while (true) {
		cout << "does anybody want to leave?" << endl;
		cin >> quitter;
		if (quitter == "no") { break; }
		shared_ptr<player> taylor = find_player(quitter);
		if (taylor == 0) {
			cout << "invalid player" << endl;
			continue;
		}
		vector<shared_ptr<player>>::iterator iter3;
		iter3 = find(players.begin(), players.end(), taylor);
		players.erase(iter3);
	}

	// add players
	string joiner;
	while (true) {
		cout << "does anybody want to join?" << endl;
		cin >> joiner;
		if (joiner == "no") { break; }
		shared_ptr<player> taylor = find_player(joiner);
		try { add_player(joiner); }
		catch (exception& e) { cout << e.what() << endl; }
	}

	// increment dealer mod # of players
	dealer++;
	if (dealer == players.size()) { dealer = 0; }
	return 0;
}