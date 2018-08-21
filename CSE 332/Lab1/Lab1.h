// Lab1.h
// Taylor Lau: t.lau@wustl.edu
// Header file for lab 1
#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

// a card has a rank and a suit
struct card {
	int rank;
	int suit;

	// compare two cards by rank, then suit
	bool operator <(const card& C) {
		if (rank < C.rank) { return true; }
		if (rank == C.rank) {
			if (suit < C.suit) { return true; }
		}
		return false;
	}
};