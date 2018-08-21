// FiveCardDraw.cpp
// Taylor Lau: t.lau@wustl.edu
// FiveCardDraw class. Inherited from game. Methods for turns and rounds for this variant of poker
#pragma once
#include "stdafx.h"
#include "FiveCardDraw.h"

FiveCardDraw::FiveCardDraw() {
	dealer = 0; pot = 0; foldCount = 0;
	for (int i = 2; i <= 14; ++i) {
		for (int j = 1; j <= 4; ++j) { main.add_card(card(i, j)); }
	}
}

void FiveCardDraw::bet() {
	mainBet = 0;
	size_t tempDealer = dealer;
	size_t range = tempDealer + 1 + players.size();
raise:
	for (size_t j = tempDealer + 1; j < range; ++j) {
		player taylor = (*players[j % players.size()]);
		if (taylor.fold || taylor.chips == 0) {continue;}
		cout << taylor.name << ": " << taylor.hand;
		cout << "/ " << taylor.chips << " chips / already bet: " << taylor.myBet;
		cout << endl;

		// there is no current bet
		if (mainBet == 0) {
		betA:
			cout << "Would you like to bet? How much? If not, enter 0 to check" << endl;
			int bet1;
			cin >> bet1;
			if (bet1 > taylor.chips) { goto betA; }
			if (bet1 != 1 && bet1 != 2 && bet1 != 0) { goto betA; }
			(*players[j % players.size()]).chips -= bet1;
			pot += bet1;
			mainBet = bet1;
			(*players[j % players.size()]).myBet += bet1;

			// raise
			if (bet1 > 0) {
				tempDealer = j % players.size();
				range = tempDealer + players.size();
				goto raise;
			}
		}

		// there is a current bet
		else {
		betB:
			cout << "Enter " << mainBet << " to call, 0 to fold, or a larger amount to raise" << endl;
			int bet2;
			cin >> bet2;
			if (bet2 > (*players[j % players.size()]).chips + (*players[j % players.size()]).myBet) { goto betB; }
			if (bet2 > mainBet + 2) { goto betB; }

			// fold
			if (bet2 == 0) {
				(*players[j % players.size()]).fold = true;
				foldCount++;
			}
			else if (bet2 < mainBet) {
				cout << "Not enough to call." << endl;
				goto betB;
			}

			// call
			else if (bet2 == mainBet) {
				(*players[j % players.size()]).chips -= bet2 - (*players[j % players.size()]).myBet;
				pot += bet2 - (*players[j % players.size()]).myBet;
				mainBet = bet2;
				(*players[j % players.size()]).myBet = bet2;
			}

			// reraise
			else {
				(*players[j % players.size()]).chips -= bet2 - (*players[j % players.size()]).myBet;
				pot += bet2 - (*players[j % players.size()]).myBet;
				mainBet = bet2;
				(*players[j % players.size()]).myBet = bet2;
				tempDealer = j % players.size();
				range = tempDealer + players.size();
				goto raise;
			}
		}
	}
}

// discard
int FiveCardDraw::before_turn(player& joe) {
	cout << joe.name << ": " << endl;
	while (true) {
		cout << joe.hand;
		cout << endl;
		cout << "give a position (1-5) to discard. Or '0' to discard nothing" << endl;
		string discard;
		cin >> discard;
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

// fill up the hand
int FiveCardDraw::turn(player& joe) {
	int makeFive = 5 - joe.hand.size();
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

// prints players, hands
int FiveCardDraw::after_turn(player& joe) {
	cout << joe.name << ": " << joe.hand;
	cout << endl;
	return 0;
}

// deal, ante, initial bet, discard cards
int FiveCardDraw::before_round() {
	main.shuffle();

	// deal cards
	for (int i = 1; i <= 5; ++i) {
		for (size_t j = dealer + 1; j < dealer + 1 + players.size(); ++j) { (*players[j % players.size()]).hand << main; }
	}

	// ante, then a round of betting
	for (size_t j = dealer + 1; j < dealer + 1 + players.size(); ++j) {(*players[j % players.size()]).chips--;}
	pot += players.size();
	FiveCardDraw::bet();

	// players act
	if (foldCount < players.size() - 1) {
		for (size_t j = dealer + 1; j < dealer + 1 + players.size(); ++j) {
			if ((*players[j % players.size()]).fold) { continue; }
			before_turn(*players[j % players.size()]);
		}
	}
	return 0;
}

// replace cards, bet again
int FiveCardDraw::round() {
	// fill up hands and print
	for (size_t j = dealer + 1; j < dealer + 1 + players.size(); ++j) {
		if (turn(*players[j % players.size()]) != 0) { return turn(*players[j % players.size()]); }
		(*players[j % players.size()]);
		//after_turn(*players[j]);
	}
	if (foldCount < players.size() - 1) {FiveCardDraw::bet();}
	return 0;
}

// print, find winner, get ready for next round
int FiveCardDraw::after_round() {
	vector<shared_ptr<player>> tempPlayers = players;
	sort(tempPlayers.begin(), tempPlayers.end(), game::poker_rank);
	reverse(tempPlayers.begin(), tempPlayers.end());

	// players eligible to win pot
	vector<shared_ptr<player>> remainders;
	vector<shared_ptr<player>>::iterator iter4;
	for (iter4 = tempPlayers.begin(); iter4 != tempPlayers.end(); ++iter4) {
		if (!(**iter4).fold) { remainders.push_back(*iter4); }
	}
	shared_ptr<player> winner = remainders.front();
	int highestRank = card::pokerRank((*winner).hand.cards);

	// distribute chips among winners
	while (true) {
		vector<shared_ptr<player>>::iterator iter0;
		for (iter0 = remainders.begin(); iter0 != remainders.end(); ++iter0) {
			if (card::pokerRank((**iter0).hand.cards) == highestRank) {
				(**iter0).chips++;
				pot--;
				if (pot == 0) { goto emptyPot; }
			}
		}
	}
emptyPot:
	// print everyone, everything
	vector<shared_ptr<player>>::iterator iter;
	for (iter = tempPlayers.begin(); iter != tempPlayers.end(); ++iter) {
		if (card::pokerRank((**iter).hand.cards) != highestRank || (**iter).fold) { (**iter).losses++; }
		else (**iter).wins++;
		if ((**iter).fold) { cout << "folded / "; }
		else {
			cout << (**iter).hand;
			cout << ": ";
			cout << card::pokerString((**iter).hand.cards) << " / ";
		}
		cout << (**iter);
		cout << endl;
	}

	// remove players
	string quitter;
	while (true) {
		cout << "does anybody want to leave?" << endl;
		cin >> quitter;
		if (quitter == "no") { break; }
		shared_ptr<player> taylor = game::find_player(quitter);
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
		shared_ptr<player> taylor = game::find_player(joiner);
		try { game::add_player(joiner); }
		catch (exception& e) { cout << e.what() << endl; }
	}

	// remove whoever went bankrupt
	vector<shared_ptr<player>>::iterator iter6;
	for (iter6 = players.begin(); iter6 != players.end(); ++iter6) {
		if ((**iter6).chips == 0) { players.erase(iter6); }
	}

	// reset everything
	main = deck();
	for (int i = 2; i <= 14; ++i) {
		for (int j = 1; j <= 4; ++j) {
			main.add_card(card(i, j));
		}
	}
	muck = deck();
	vector<shared_ptr<player>>::iterator iter2;
	for (iter2 = players.begin(); iter2 != players.end(); ++iter2) {
		(**iter2).hand = hand();
		(**iter2).myBet = 0;
		(**iter2).fold = false;
	}
	dealer++;
	if (dealer == players.size()) { dealer = 0; }
	mainBet = 0; pot = 0; foldCount = 0;
	return 0;
}