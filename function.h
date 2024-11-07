#pragma once

#include <string>
#include <vector>

using namespace std;

class user;
class transaction;
class block;

void generateRandomUsers(vector<user>& randomUsers);
string generateRandomKey();
void generateRandomTransactions(vector<transaction>& pendingTransactions, vector<user>& updatedUsers);

vector<transaction> selectRandomTransactions(vector<transaction>& allTransactions);
string calculateBlockHash(string previousBlockHash, time_t timestamp, uint32_t version, string merkleRootHash, uint64_t nonce, uint32_t difficultyTarget);
string mineBlock(string previousBlockHash, time_t timestamp, uint32_t version, string merkleRootHash, uint64_t& nonce, uint32_t difficultyTarget);
