// Hand.h
// Taylor Lau: t.lau@wustl.edu
// Header for Hand.cpp
#pragma once
#include "Deck.h"

class hand {
public:
	vector<card> cards;
	hand() {};
	hand(const hand& hand);
	int operator= (const hand& hand);
	bool equals(const hand& hand);
	int asString();
	int size();
	bool operator< (const hand& hand2);
	friend hand operator<< (hand& hand, deck& deck);
	friend int operator<<(ostream& oss, const hand& hand);
	card operator[] (size_t position);
	int remove_card(size_t position);
};