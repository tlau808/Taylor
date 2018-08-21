// Deck.h
// Taylor Lau: t.lau@wustl.edu
// Header for Deck.cpp
#pragma once
#include "Card.h"

class deck {
public:
	vector<card> cards;
	deck() {};
	deck(char * file);
	int load(char* file);
	int shuffle();
	int size() const;
	friend int operator<<(ostream& oss, const deck& deck);
	int add_card(card newCard);
};