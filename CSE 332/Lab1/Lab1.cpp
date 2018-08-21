// Lab1.cpp
// Taylor Lau: t.lau@wustl.edu
// Modified lab 0, added functions for lab 1 
#include "stdafx.h"
#include "Lab1.h"

// determine whether a card definition is valid
bool validCard(string definition) {
	if (definition.length() != 2 && definition.length() != 3) { return false; }
	if (definition.length() == 2) {
		if (definition[0] != '2' && definition[0] != '3' && definition[0] != '4' && definition[0] != '5' && definition[0] != '6' && definition[0] != '7' && definition[0] != '8' && definition[0] != '9' && definition[0] != 'J' && definition[0] != 'Q' && definition[0] != 'K' && definition[0] != 'A') { return false; }
		if (definition[1] != 's' && definition[1] != 'H' && definition[1] != 'c' && definition[1] != 'D') { return false; }
	}
	if (definition.length() == 3) {
		if (definition[0] != '1') { return false; }
		if (definition[1] != '0') { return false; }
		if (definition[2] != 's' && definition[2] != 'H' && definition[2] != 'c' && definition[2] != 'D') { return false; }
	}
	return true;
}
bool isQuads(const vector<card> cards) {
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
bool isBoat(const vector<card> cards) {
	set<int> boatRanks;
	for (int i = 0; i <= 4; ++i) {
		boatRanks.insert(cards[i].rank);
	}
	if (boatRanks.size() == 2) { return true; }
	return false;
}
bool isFlush(const vector<card> cards) {
	int flushCandidate = cards[0].suit;
	for (int i = 1; i <= 4; ++i) {
		if (cards[i].suit != flushCandidate) { return false; }
	}
	return true;
}
bool isStraight(const vector<card> cards) {
	for (int i = 0; i <= 3; ++i) {
		if (cards[i].rank + 1 != cards[i + 1].rank) { return false; }
	}
	return true;
}
bool isTrips(const vector<card> cards) {
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
bool isTwoPair(const vector<card> cards) {
	int count = 0;
	for (int i = 0; i <= 3; ++i) {
		if (cards[i].rank == cards[i + 1].rank) { count++; }
	}
	if (count == 2) { return true; }
	return false;
}
bool isPair(const vector<card> cards) {
	for (int i = 0; i <= 3; ++i) {
		if (cards[i].rank == cards[i + 1].rank) { return true; }
	}
	return false;
}
bool isStraightFlush(const vector<card> cards) {
	if (isFlush(cards) && isStraight(cards)) { return true; }
	return false;
}

// check above booleans, starting from the highest rank
int pokerRank(const vector<card> & cards) {
	if (isStraightFlush(cards)) { cout << "straight flush"; }
	else if (isQuads(cards)) { cout << "four of a kind"; }
	else if (isBoat(cards)) { cout << "full house"; }
	else if (isFlush(cards)) { cout << "flush"; }
	else if (isStraight(cards)) { cout << "straight"; }
	else if (isTrips(cards)) { cout << "three of a kind"; }
	else if (isTwoPair(cards)) { cout << "two pair"; }
	else if (isPair(cards)) { cout << "one pair"; }
	else cout << "High card";
	return 0;
}

// converts from card definition strings to a card vector
int parseCards(vector<card> & cards, char * name) {

	// make sure it opens properly
	ifstream ifs(name);
	if (!ifs.is_open()) {
		cout << "Invalid file name. Input a valid text file";
		return 1;
	}

	// keep track of any errors
	int sizeError = 0;
	int stringError = 0;

	// extract lines from the text file to stream
	string line;
	while (getline(ifs, line)) {
		istringstream iss(line);
		string word;
		vector<card> candidates;

		// pass words from stream to string
		while (iss >> word) {
			if (validCard(word)) {
				card newCard;
				if (word.length() == 3) {
					newCard.rank = 10;
					if (word[2] == 'c') { newCard.suit = 1; }
					if (word[2] == 'D') { newCard.suit = 2; }
					if (word[2] == 'H') { newCard.suit = 3; }
					if (word[2] == 's') { newCard.suit = 4; }
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
					if (word[1] == 'c') { newCard.suit = 1; }
					if (word[1] == 'D') { newCard.suit = 2; }
					if (word[1] == 'H') { newCard.suit = 3; }
					if (word[1] == 's') { newCard.suit = 4; }
				}

				// push back to candidate vector
				candidates.push_back(newCard);
			}
			else stringError++;
		}

		// if the candidates are good, push back to real vector
		if (candidates.size() == 5) {
			for (int i = 0; i <= 4; ++i) { cards.push_back(candidates[i]); }
		}
		if (candidates.size() != 5) {
			sizeError++;
		}
	}
	if (sizeError > 0) { cout << "One or more lines had less or more than five cards and were not printed" << endl; }
	if (stringError > 0) { cout << "One or more card definitions were invalid and were not printed" << endl; }
	return 0;
}

// prints a card vector, five definitions + poker rank per line
int printCards(const vector<card> & cards) {
	if (cards.size() == 0) {
		cout << "There are no valid hands to print";
		return 2;
	}
	int index = 0;
	while (index < cards.size()) {

		// use a temporary vector for each line
		vector<card> tempCard;
		for (int j = index; j <= index + 4; ++j) {
			card temp = cards[j];
			tempCard.push_back(temp);
		}

		// sort cards
		sort(tempCard.begin(), tempCard.end());

		// print five card definitions
		for (int i = 0; i <= 4; ++i) {
			string suit;
			if (tempCard[i].suit == 1) { suit = 'c'; }
			if (tempCard[i].suit == 2) { suit = 'D'; }
			if (tempCard[i].suit == 3) { suit = 'H'; }
			if (tempCard[i].suit == 4) { suit = 's'; }
			if (tempCard[i].rank <= 10) { cout << tempCard[i].rank << suit << " "; }
			if (tempCard[i].rank == 11) { cout << "J" << suit << " "; }
			if (tempCard[i].rank == 12) { cout << "Q" << suit << " "; }
			if (tempCard[i].rank == 13) { cout << "K" << suit << " "; }
			if (tempCard[i].rank == 14) { cout << "A" << suit << " "; }
		}

		// print poker rank
		cout << "Hand rank: ";
		pokerRank(tempCard);
		cout << "\n";

		// move to next hand
		index += 5;
	}
	return 0;
}

int usage() {
	cout << "Input a single file name that contains a five card poker hand on each line" << endl;
	return 3;
}

int main(int argc, char * argv[]) {
	if (argc != 2) { return usage(); }
	vector<card> v;
	parseCards(v, argv[1]);
	printCards(v);
	return 0;
}