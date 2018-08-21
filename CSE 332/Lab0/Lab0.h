#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <string>
using namespace std;

// A card has a rank and a suit
struct card {
	string rank;
	char suit;
};