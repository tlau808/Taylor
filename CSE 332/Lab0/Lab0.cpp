#include "stdafx.h"
#include "Lab0.h"

// Determines whether a card definition is valid
bool validCard(string definition) {
	if (definition.length() != 2 && definition.length() != 3) { return false; }
	if (definition.length() == 2) {
		if (definition[0] != '2' && definition[0] != '3' && definition[0] != '4' && definition[0] != '5' && definition[0] != '6' && definition[0] != '7' && definition[0] != '8' && definition[0] != '9' && definition[0] != 'J' && definition[0] != 'Q' && definition[0] != 'K' && definition[0] != 'A') { return false; }
		if (definition[1] != 's' && definition[1] != 'h' && definition[1] != 'c' && definition[1] != 'd') { return false; }
	}
	if (definition.length() == 3) {
		if (definition[0] != '1') { return false; }
		if (definition[1] != '0') { return false; }
		if (definition[2] != 's' && definition[2] != 'h' && definition[2] != 'c' && definition[2] != 'd') { return false; }
	}
	return true;
}

// Input: Empty vector of cards, name of text file
// Converts from card definition strings to a card vector
int parseCards(vector<card> & cards, char * name) {

	// Make sure it opens properly
	ifstream ifs(name);
	if (!ifs.is_open()) {
		cout << "Invalid file name. Input a valid text file";
		return 1;
	}

	// Pass words from the text file to the vector
	while (!ifs.eof()) {
		string word;
		ifs >> word;

		// Skip words that are not card definitions
		if (validCard(word)) {
			card newCard;
			if (word.length() == 3) {
				newCard.rank = "10";
				newCard.suit = word[2];
			}
			if (word.length() == 2) {
				newCard.rank = word[0];
				newCard.suit = word[1];
			}
			cards.push_back(newCard);
		}
	}
	return 0;
}

// Input: Vector of cards
// Prints card values
int printCards(const vector<card> & cards) {
	if (cards.size() == 0) {
		cout << "There are no valid cards to print";
		return 2;
	}
	for (int i = 0; i < (int)cards.size(); ++i) {
		cout << cards[i].rank << cards[i].suit << endl;
	}
	return 0;
}

// How to use this program
int usage() {
	cout << "Input a single file name that contains card definition strings" << endl;
	return 3;
}
int main(int argc, char * argv[]) {

	// Make sure exactly one string has been inputted
	if (argc != 2) {
		return usage();
	}
	vector<card> v;
	parseCards(v, argv[1]);
	return printCards(v);
}