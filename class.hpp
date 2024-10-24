#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <stdexcept>
#include "function.h"
#include <iostream>
#include <algorithm> 
#include <iomanip> 

using namespace std;



class user {

	private:
		string name = " ";
		string public_key = " ";
		double balance = 0.0;
	public:
		void setName(string Name) {
			name = Name;
		};

		string getName() {
			return name;
		}

		void setPublicKey(string publicKey) {
			public_key = publicKey;
		}

		string getPublicKey() {
			return public_key;
		}

		void setBalance(double Balance) {
			balance = Balance;
		}

		double getBalance() {
			return balance;
		}
	user() = default;

};

class transaction {

	private:
		string transaction_id = " ";
		string sender = " "; // sintejo viesasis raktas
		string recipient = " "; // gavejo viesasis raktas
		double amount = 0.0;
	public:
		void setTransactionId(string tran) {
			transaction_id = tran;
		};

		string getTransactionId() {
			return transaction_id;
		}

		void setSender(string Sender) {
			sender = Sender;
		}

		string getSender() {
			return sender;
		}

		void setRecipient(string Recipient) {
			recipient = Recipient;
		}

		string getRecipient() {
			return recipient;
		}

		void setAmount(double Amount) {
			amount = Amount;
		}

		double getAmount() {
			return amount;
		}
		transaction() = default;

		void printTransaction() const {
			cout << "Transaction ID: " << transaction_id << endl;
			cout << "Sender: " << sender << endl;
			cout << "Recipient: " << recipient << endl;
			cout << "Amount: " << amount << endl;
		}
};



class block {
	private: 
		string previousBlockHash;
		time_t timestamp;
		uint32_t version;
		string merkleRootHash;
		uint64_t nonce;
		uint32_t difficultyTarget;
		vector<transaction> Transactions;
		string blockHash;

	public: 

		block(string PBH, uint32_t ver, uint32_t diffTarget, vector<transaction> tran) {
			previousBlockHash = PBH;
			timestamp = time(0);
			version = ver;
			difficultyTarget = diffTarget;
			nonce = 0;
			Transactions = tran;
			merkleRootHash = calculateMerkleRootHash();
			blockHash = calculateBlockHash();
		}


		void setPBH(string PBH) {
			previousBlockHash = PBH;
		}
		string getPBH() {
			return previousBlockHash;
		}



		void setTimestamp(time_t time) {
			timestamp = time;
		}
		time_t getTimestamp() {
			return timestamp;
		}



		void setTransactions(vector<transaction> tran) { // visas vektorius
			Transactions = tran;
			merkleRootHash = calculateMerkleRootHash();
			blockHash = calculateBlockHash();

		}
		vector<transaction> getTransactions() {
			return Transactions;
		}



		void addTransaction(transaction tran) {
			Transactions.push_back(tran);
			merkleRootHash = calculateMerkleRootHash();
			blockHash = calculateBlockHash();
		}
		transaction getTransaction(int i) const {
			if (i >= 0 && i < Transactions.size()) {
				return Transactions[i];
			}
			else {
				throw out_of_range("Index out of range");
			}
		}


		string calculateBlockHash() {
			string data = previousBlockHash + to_string(timestamp) + to_string(version) + merkleRootHash + to_string(nonce) + to_string(difficultyTarget);
			return hashfun(data);
		}

		string calculateMerkleRootHash() {
					string combinedTransactionHashes;
					for (auto& tx : Transactions) {
						combinedTransactionHashes += tx.getTransactionId();
					}
					return hashfun(combinedTransactionHashes);
				}

		string getBlockHash() const{
			return blockHash;
		}
		uint32_t getVersion() const {
			return version;
		}

		uint64_t getNonce() const {
			return nonce;
		}

		uint32_t getDifficultyTarget() const {
			return difficultyTarget;
		}

		string getMerkleRootHash() const {
			return merkleRootHash;
		}

		void setNonce(uint64_t n) {
			nonce = n;
			blockHash = calculateBlockHash();
		}

		void mineBlock() {
			// Simple mining process
			do {
				nonce++;
				blockHash = calculateBlockHash();
			} while (blockHash.substr(0, difficultyTarget) != string(difficultyTarget, '0'));
			cout << "Block mined: " << blockHash << endl;
		}
		void printBlock() const {
			cout << "----------------------------------------" << endl;
			cout << "Block Hash: " << blockHash << endl;
			cout << "Previous Block Hash: " << previousBlockHash << endl;
			struct tm tm_local;
			errno_t err = localtime_s(&tm_local, &timestamp);
			if (err == 0) {
				cout << "Timestamp: " << std::put_time(&tm_local, "%Y-%m-%d %H:%M:%S") << endl;
			}
			else {
				cerr << "Failed to convert time for timestamp." << endl;
			}
			cout << "Version: " << version << endl;
			cout << "Merkle Root Hash: " << merkleRootHash << endl;
			cout << "Nonce: " << nonce << endl;
			cout << "Difficulty Target: " << difficultyTarget << endl;
			cout << "Transactions:" << endl;
			for (const auto& tx : Transactions) {
				tx.printTransaction();
			}
			cout << "----------------------------------------" << endl;
		}
};
