// Hand.cpp
// Taylor Lau: t.lau@wustl.edu
// Hand class. Methods to compare, deal, and print hands.
#pragma once
#include "stdafx.h"
#include "Hand.h"

hand::hand(const hand& hand) { cards = hand.cards; }

int hand::operator= (const hand& hand) {
	if (this != &hand) {
		cards = hand.cards;
	}
	return 0;
}

bool hand::equals(const hand& hand) {
	for (unsigned int i = 0; i < cards.size(); ++i) {
		if (!(cards[i] = hand.cards[i])) { return false; }
	}
	return true;
}

int hand::asString() {
	card::printCards(cards);
	return 0;
}

int hand::size() { return cards.size(); }
bool hand::operator< (const hand& hand2) {
	int min;
	if (cards.size() < hand2.cards.size()) { min = cards.size(); }
	else { min = hand2.cards.size(); }
	for (int i = 0; i < min; ++i) {
		if (cards[i] < hand2.cards[i]) { return true; }
		if (cards[i] > hand2.cards[i]) { return false; }
	}
	if (cards.size() < hand2.cards.size()) { return true; }
	return false;
}

hand operator<< (hand& hand, deck& deck) {
	card last = deck.cards.back();
	deck.cards.pop_back();
	hand.cards.push_back(last);
	sort(hand.cards.begin(), hand.cards.end());
	return hand;
}

int operator<<(ostream& oss, const hand& hand) {
	card::printCards(hand.cards);
	return 0;
}

card hand::operator[] (size_t position) {
	if (position >= cards.size()) { throw exception("invalid position"); }
	return cards[position];
}

int hand::remove_card(size_t position) {
	if (position > cards.size()) { throw exception("invalid position"); }
	cards.erase(cards.begin() + position - 1);
	return 0;
}