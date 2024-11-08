#pragma once

#include <string>
#include <vector>
#include <chrono>
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
string mineBlock(string previousBlockHash, time_t timestamp, uint32_t version, string merkleRootHash, uint64_t& nonce, uint32_t difficultyTarget, chrono::steady_clock::time_point endTime);
void get_transaction(string transactionId, vector<block>& blockchain);
void get_block(string blockHash, vector<block>& blockchain);
bool transactionVerification(string spk, string rpk, double amount, string tranHash, double oldSenderBalance);