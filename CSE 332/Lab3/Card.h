// Card.h
// Taylor Lau: t.lau@wustl.edu
// Header for Card.cpp
#pragma once
#include <vector>
#include <string>
#include <set>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <random>
#include <memory>
using namespace std;

struct card {
	int rank;
	int suit;
	card() {};
	card(int a, int b);

	bool operator< (const card& C);

	bool operator= (const card& C);

	bool operator> (const card& C);

	static bool validCard(string definition);

	static bool isQuads(const vector<card> cards);

	static bool isBoat(const vector<card> cards);

	static bool isFlush(const vector<card> cards);

	static bool isStraight(const vector<card> cards);

	static bool isTrips(const vector<card> cards);

	static bool isTwoPair(const vector<card> cards);

	static bool isPair(const vector<card> cards);

	static bool isStraightFlush(const vector<card> cards);

	static string pokerString(const vector<card> & cards);

	static int pokerRank(const vector<card> & cards);

	static int parseCards(vector<card> & cards, char * name);

	static int printCards(const vector<card> & cards);
};