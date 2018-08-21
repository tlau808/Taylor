// Taylor Lau: t.lau@wustl.edu
// Lab 2
// Hand class with methods to print, compare, deal hands
#pragma once
class hand {
public:
	vector<card> cards;
	hand() {}
	hand(const hand& hand) {
		cards = hand.cards;
	}

	int operator= (const hand& hand) {
		if (this != &hand) {
			cards = hand.cards;
		}
		return 0;
	}

	bool equals(const hand& hand) {
		for (unsigned int i = 0; i < cards.size(); ++i) {
			if (!(cards[i] = hand.cards[i])) { return false; }
		}
		return true;
	}

	int asString() {
		printCards(cards);
		return 0;
	}

	int size() { return cards.size(); }
	bool operator< (const hand& hand2) {
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

	// transfers a card from the deck to a hand
	friend hand operator<< (hand& hand, deck& deck) {
		card last = deck.cards.back();
		deck.cards.pop_back();
		hand.cards.push_back(last);
		sort(hand.cards.begin(), hand.cards.end());
		return hand;
	}
};