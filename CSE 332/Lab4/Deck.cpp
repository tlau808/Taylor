// Deck.cpp
// Taylor Lau: t.lau@wustl.edu
// Deck class. Methods to shuffle, print, and add cards to a deck
#pragma once
#include "stdafx.h"
#include "Deck.h"
vector<card> cards;
deck::deck(char * file) { load(file); }

int deck::load(char* file) {
	card::parseCards(cards, file);
	return 0;
}

int deck::shuffle() {
	random_device rd;
	mt19937 g(rd());
	std::shuffle(cards.begin(), cards.end(), g);
	return 0;
}

int deck::size() const { return cards.size(); }
int operator<<(ostream& oss, const deck& deck) {
	card::printCards(deck.cards);
	return 0;
}

int deck::add_card(card newCard) {
	cards.push_back(newCard);
	return 0;
}