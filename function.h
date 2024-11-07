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
void generateRandomTransactions(vector<transaction>& pendingTransactions, vector<user>& updatedUsers);
string tikrinimas(string code);
char convertHex(const string& fourBits);
string binaryTohex(string kodas);
string skaiciavimai(string tempDec);
string manipulation(string code);
string hashfun(string input);
vector<transaction> selectRandomTransactions(vector<transaction>& allTransactions);
string calculateBlockHash(string previousBlockHash, time_t timestamp, uint32_t version, string merkleRootHash, uint64_t nonce, uint32_t difficultyTarget);
string mineBlock(string previousBlockHash, time_t timestamp, uint32_t version, string merkleRootHash, uint64_t& nonce, uint32_t difficultyTarget);
