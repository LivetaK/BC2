#pragma once

#include <string>
#include <vector>

using namespace std;

class user;
class transaction;

void generateRandomUsers(vector<user>& randomUsers);
string generateRandomKey();
void generateRandomTransactions(vector<transaction>& tran, vector<user>& updatedUsers);

void generateRandomUsers(vector<user>& randomUsers);
string generateRandomKey();
void generateRandomTransactions(vector<transaction>& tran, vector<user>& updatedUsers);
string tikrinimas(string code);
char convertHex(const string& fourBits);
string binaryTohex(string kodas);
string skaiciavimai(string tempDec);
string manipulation(string code);
string hashfun(string input);