#pragma once

#include <string>
#include <vector>
#include "class.hpp"

using namespace std;

class user;
class transaction;
class block;

void generateRandomUsers(vector<user>& randomUsers);
string generateRandomKey();
void generateRandomTransactions(vector<transaction>& tran, vector<user>& updatedUsers);
string tikrinimas(string code);
char convertHex(const string& fourBits);
string binaryTohex(string kodas);
string skaiciavimai(string tempDec);
string manipulation(string code);
string hashfun(string input);
vector<transaction> selectRandomTransactions(const vector<transaction>& allTransactions);