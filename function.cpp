#include "function.h"
#include "class.hpp"
#include "hash.h" 

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;


string generateRandomKey() {
	char characters[] = "0123456789ABCDEF";
	string key;
	for (int i = 0; i < 64; i++) {
		key += characters[rand() % 16];
	}
	return key;

}

void generateRandomUsers(vector<user>& randomUsers) {

	for (int i = 0; i < 1000; i++) {

		user tempUser;
		string key = generateRandomKey();

		tempUser.setName("User" + to_string(i));
		tempUser.setPublicKey(key);
		tempUser.setBalance(rand() % (1000000 - 99) + 100);

		randomUsers.push_back(tempUser);
	}
}


void generateRandomTransactions(vector<transaction>& pendingTransactions, vector<user>& updatedUsers) {

	for (int i = 0; i < 10000; i++){

		transaction tempTran;

		int sender = rand() % updatedUsers.size(); // random indeksas
		tempTran.setSender(updatedUsers[sender].getPublicKey());


		int recipient = rand() % updatedUsers.size(); //random indeksas
		while (recipient == sender) {
			recipient = rand() % updatedUsers.size();
		}
		tempTran.setRecipient(updatedUsers[recipient].getPublicKey());


		double amount = 1 + ((double)rand() / RAND_MAX) * (updatedUsers[sender].getBalance() - 1);
		tempTran.setAmount(amount);



		string transactionID = hashfun(updatedUsers[sender].getPublicKey() + updatedUsers[recipient].getPublicKey() + to_string(amount));

		tempTran.setTransactionId(hashfun(transactionID));
		bool verify = transactionVerification(updatedUsers[sender].getPublicKey(), updatedUsers[recipient].getPublicKey(), amount, transactionID, updatedUsers[sender].getBalance());
		if (verify = true) {

			pendingTransactions.push_back(tempTran);

			double oldSenderBalance = updatedUsers[sender].getBalance();
			updatedUsers[sender].setBalance(oldSenderBalance - amount);

			double oldRecipientBalance = updatedUsers[recipient].getBalance();
			updatedUsers[recipient].setBalance(oldRecipientBalance + amount);
		}
	}
}

vector<transaction> selectRandomTransactions(vector<transaction>& allTransactions) {
	vector<transaction> selectedTran;
	if (allTransactions.size() <= 100) {
		selectedTran = allTransactions;
		allTransactions.clear();
	}
	else {
		for (int i = 0; i < 100; i++) {
			int index = rand() % allTransactions.size();
			selectedTran.push_back(allTransactions[index]);
			allTransactions.erase(allTransactions.begin() + index);
		}
	}
	return selectedTran;
}

string calculateBlockHash(string previousBlockHash, time_t timestamp, uint32_t version, string merkleRootHash, uint64_t nonce, uint32_t difficultyTarget) {
	string data = previousBlockHash + to_string(timestamp) + to_string(version) + merkleRootHash + to_string(nonce) + to_string(difficultyTarget);
	return hashfun(data);
}

string mineBlock(string previousBlockHash, time_t timestamp, uint32_t version, string merkleRootHash, uint64_t& nonce, uint32_t difficultyTarget) {
	string blockHash;
	nonce = 0;
	do {
		nonce++;
		blockHash = calculateBlockHash(previousBlockHash, timestamp, version, merkleRootHash, nonce, difficultyTarget);
	} while (blockHash.substr(0, difficultyTarget) != string(difficultyTarget, '0'));
	//cout << "Block mined: " << blockHash << endl;
	return blockHash;
}

void get_block(string blockHash, vector<block>& blockchain) {

		for (int i = 1; i < blockchain.size(); i++) {
			if (blockchain[i].getPBH() == blockHash) {
				blockchain[i-1].printBlock();
				return;
			}
		}

	cout << "Tokio bloko nera" << endl;
}

void get_transaction(string transactionId, vector<block>& blockchain) {
	for (auto& b : blockchain) {
		vector<transaction>& allTransactions = b.getTransactions();
		for (int i = 0; i < allTransactions.size(); i++) {
			if (allTransactions[i].getTransactionId() == transactionId) {
				allTransactions[i].printTransaction();
				return;
			}
		}
	}
	cout << "Tokios transakcijos nera" << endl;
}



bool transactionVerification(string spk, string rpk, double amount, string tranHash, double oldSenderBalance) {
	
	string hash = hashfun(spk + rpk + to_string(amount));

	if (hash != tranHash || oldSenderBalance < amount) {
		return false;
	}

}
