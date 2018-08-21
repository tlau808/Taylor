// Card.cpp
// Taylor Lau: t.lau@wustl.edu
// Card struct. Methods to parse, print, and ranks cards
#pragma once
#include "stdafx.h"
#include "Card.h"

card::card(int a, int b) {
	rank = a;
	suit = b;
}
bool card::operator< (const card& C) {
	if (rank < C.rank) { return true; }
	if (rank == C.rank) {
		if (suit < C.suit) { return true; }
	}
	return false;
}
bool card::operator= (const card& C) {
	if (this != &C) {
		rank = C.rank;
		suit = C.suit;
		return false;
	}
	return true;
}
bool card::operator> (const card& C) {
	if (rank > C.rank) { return true; }
	if (rank == C.rank) {
		if (suit > C.suit) { return true; }
	}
	return false;
}
bool card::validCard(string definition) {
	if (definition.length() != 2 && definition.length() != 3) { return false; }
	if (definition.length() == 2) {
		if (definition[0] != '2' && definition[0] != '3' && definition[0] != '4' && definition[0] != '5' && definition[0] != '6' && definition[0] != '7' && definition[0] != '8' && definition[0] != '9' && definition[0] != 'J' && definition[0] != 'Q' && definition[0] != 'K' && definition[0] != 'A') { return false; }
		if (definition[1] != 's' && definition[1] != 'S' && definition[1] != 'H' && definition[1] != 'h' && definition[1] != 'c' && definition[1] != 'C' && definition[1] != 'D' && definition[1] != 'd') { return false; }
	}
	if (definition.length() == 3) {
		if (definition[0] != '1') { return false; }
		if (definition[1] != '0') { return false; }
		if (definition[2] != 's' && definition[2] != 'S' && definition[2] != 'H' && definition[2] != 'h' && definition[2] != 'c' && definition[2] != 'C' && definition[2] != 'D' && definition[2] != 'd') { return false; }
	}
	return true;
}
bool card::isQuads(const vector<card> cards) {
	for (int i = 0; i <= 1; ++i) {
		int quadCandidate = cards[i].rank;
		int count = 0;
		for (int j = i + 1; j <= i + 3; ++j) {
			if (cards[j].rank == quadCandidate) {
				count++;
			}
		}
		if (count == 3) { return true; }
	}
	return false;
}
bool card::isBoat(const vector<card> cards) {
	set<int> boatRanks;
	for (int i = 0; i <= 4; ++i) {
		boatRanks.insert(cards[i].rank);
	}
	if (boatRanks.size() == 2) { return true; }
	return false;
}
bool card::isFlush(const vector<card> cards) {
	int flushCandidate = cards[0].suit;
	for (int i = 1; i <= 4; ++i) {
		if (cards[i].suit != flushCandidate) { return false; }
	}
	return true;
}
bool card::isStraight(const vector<card> cards) {
	for (int i = 0; i <= 3; ++i) {
		if (cards[i].rank + 1 != cards[i + 1].rank) { return false; }
	}
	return true;
}
bool card::isTrips(const vector<card> cards) {
	for (int i = 0; i <= 2; ++i) {
		int quadCandidate = cards[i].rank;
		int count = 0;
		for (int j = i + 1; j <= i + 2; ++j) {
			if (cards[j].rank == quadCandidate) {
				count++;
			}
		}
		if (count == 2) { return true; }
	}
	return false;
}
bool card::isTwoPair(const vector<card> cards) {
	int count = 0;
	for (int i = 0; i <= 3; ++i) {
		if (cards[i].rank == cards[i + 1].rank) { count++; }
	}
	if (count == 2) { return true; }
	return false;
}
bool card::isPair(const vector<card> cards) {
	for (int i = 0; i <= 3; ++i) {
		if (cards[i].rank == cards[i + 1].rank) { return true; }
	}
	return false;
}
bool card::isStraightFlush(const vector<card> cards) {
	if (isFlush(cards) && isStraight(cards)) { return true; }
	return false;
}

string card::pokerString(const vector<card> & cards) {
	if (isStraightFlush(cards)) { return "straight flush"; }
	else if (isQuads(cards)) { return "four of a kind"; }
	else if (isBoat(cards)) { return "full house"; }
	else if (isFlush(cards)) { return "flush"; }
	else if (isStraight(cards)) { return "straight"; }
	else if (isTrips(cards)) { return "three of a kind"; }
	else if (isTwoPair(cards)) { return "two pair"; }
	else if (isPair(cards)) { return "one pair"; }
	else return "high card";
}
int card::pokerRank(const vector<card> & cards) {
	if (isStraightFlush(cards)) { return 8; }
	else if (isQuads(cards)) { return 7; }
	else if (isBoat(cards)) { return 6; }
	else if (isFlush(cards)) { return 5; }
	else if (isStraight(cards)) { return 4; }
	else if (isTrips(cards)) { return 3; }
	else if (isTwoPair(cards)) { return 2; }
	else if (isPair(cards)) { return 1; }
	else return 0;
}
int card::parseCards(vector<card> & cards, char * name) {
	ifstream ifs(name);
	if (!ifs.is_open()) {
		cout << "Invalid file name. Input a valid text file";
		return 1;
	}
	string word;
	while (ifs >> word) {
		if (card::validCard(word)) {
			card newCard;
			if (word.length() == 3) {
				newCard.rank = 10;
				if (word[2] == 'c' || word[2] == 'C') { newCard.suit = 1; }
				if (word[2] == 'D' || word[2] == 'd') { newCard.suit = 2; }
				if (word[2] == 'H' || word[2] == 'h') { newCard.suit = 3; }
				if (word[2] == 's' || word[2] == 'S') { newCard.suit = 4; }
			}
			if (word.length() == 2) {
				if (word[0] == '2') { newCard.rank = 2; }
				if (word[0] == '3') { newCard.rank = 3; }
				if (word[0] == '4') { newCard.rank = 4; }
				if (word[0] == '5') { newCard.rank = 5; }
				if (word[0] == '6') { newCard.rank = 6; }
				if (word[0] == '7') { newCard.rank = 7; }
				if (word[0] == '8') { newCard.rank = 8; }
				if (word[0] == '9') { newCard.rank = 9; }
				if (word[0] == 'J') { newCard.rank = 11; }
				if (word[0] == 'Q') { newCard.rank = 12; }
				if (word[0] == 'K') { newCard.rank = 13; }
				if (word[0] == 'A') { newCard.rank = 14; }
				if (word[1] == 'c' || word[1] == 'C') { newCard.suit = 1; }
				if (word[1] == 'D' || word[1] == 'd') { newCard.suit = 2; }
				if (word[1] == 'H' || word[1] == 'h') { newCard.suit = 3; }
				if (word[1] == 's' || word[1] == 'S') { newCard.suit = 4; }
			}
			cards.push_back(newCard);
		}
	}
	return 0;
}

int card::printCards(const vector<card> & cards) {
	if (cards.size() == 0) {
		cout << "There are no valid cards to print";
		return 2;
	}
	for (unsigned int i = 0; i < cards.size(); ++i) {
		string suit;
		if (cards[i].suit == 1) { suit = 'c'; }
		if (cards[i].suit == 2) { suit = 'D'; }
		if (cards[i].suit == 3) { suit = 'H'; }
		if (cards[i].suit == 4) { suit = 's'; }
		if (cards[i].rank <= 10) { cout << cards[i].rank << suit << " "; }
		if (cards[i].rank == 11) { cout << "J" << suit << " "; }
		if (cards[i].rank == 12) { cout << "Q" << suit << " "; }
		if (cards[i].rank == 13) { cout << "K" << suit << " "; }
		if (cards[i].rank == 14) { cout << "A" << suit << " "; }
	}
	return 0;
}