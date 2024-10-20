#pragma once

#include "class.hpp"
#include "function.cpp"

using namespace std;


void generateRandomUsers(vector<user>& randomUsers);
string generateRandomKey();
void generateRandomTransactions(vector<transaction>& tran, vector<user>& updatedUsers);