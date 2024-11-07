#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <iostream>
#include <algorithm> 
#include <iomanip> 

using namespace std;

string hashfun(string input);

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
			cout << "Transaction ID:_________" << transaction_id << endl;
			cout << "Sender:_________________" << sender << endl;
			cout << "Recipient:______________" << recipient << endl;
			cout << "Amount:_________________" << amount << endl;
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
	public: 

		block(string PBH, uint32_t diffTarget, vector<transaction> tran) {
			previousBlockHash = PBH;
			timestamp = time(0);
			version = 1;
			difficultyTarget = diffTarget;
			nonce = 0;
			Transactions = tran;
			merkleRootHash = calculateMerkleRootHash();
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
		}
		vector<transaction> getTransactions() {
			return Transactions;
		}



		void addTransaction(transaction tran) {
			Transactions.push_back(tran);
			merkleRootHash = calculateMerkleRootHash();
		}
		transaction getTransaction(int i) const {
			if (i >= 0 && i < Transactions.size()) {
				return Transactions[i];
			}
			else {
				throw out_of_range("Index out of range");
			}
		}


		string calculateMerkleRootHash() {
			vector<string> hashedTransactions;
				for (auto& tx : Transactions) {
					string tran = tx.getTransactionId() + tx.getSender() + tx.getRecipient() + to_string(tx.getAmount());
					hashedTransactions.push_back(hashfun(tran));
				}
				while (hashedTransactions.size() > 1) {
					vector<string> newTransactionVector;

					if (hashedTransactions.size() % 2 != 0) {
						hashedTransactions.push_back(hashedTransactions.back());
					}

					for (int i = 0; i < hashedTransactions.size(); i += 2) {
						string twoTransactions;
						string hash = hashfun(hashedTransactions[i] + hashedTransactions[i + 1]);
						newTransactionVector.push_back(hash);
					}
					hashedTransactions = newTransactionVector;

				}
				return hashfun(hashedTransactions[0]);
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
		}


		void printBlock() const {

			cout << "******************************************************************************************" << endl;
			cout << "Previous Block Hash:    " << previousBlockHash << endl;
			struct tm tm_local;
			errno_t err = localtime_s(&tm_local, &timestamp);
			if (err == 0) {
				cout << "Timestamp:              " << put_time(&tm_local, "%Y-%m-%d %H:%M:%S") << endl;
			}
			else {
				cerr << "Failed to convert time for timestamp." << endl;
			}		
			cout << "Version:                " << version << endl;
			cout << "Merkle Root Hash:       " << merkleRootHash << endl;
			cout << "Nonce:                  " << nonce << endl;
			cout << "Difficulty Target:      " << difficultyTarget << endl;
			cout << "------------------------------------------------------------------------------------------" << endl;
			cout << "                                      TRANSACTIONS                                        " << endl;
			cout << "------------------------------------------------------------------------------------------" << endl;
			for (const auto& tx : Transactions) {
				tx.printTransaction();
			}
			cout << endl;
			cout << endl;
		}
};
