#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <bitset>
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
};



class block {
	private: 
		string previousBlockHash = " ";
		time_t timestamp = time(0);
		vector<transaction> Transactions;
		string blockHash;
	public: 


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
		}
		vector<transaction> getTransactions() {
			return Transactions;
		}



		void addTransaction(transaction tran) {
			Transactions.push_back(tran);
		}
		transaction getTransaction(int i) {
			return Transactions[i];
		}


		string calculateBlockHash() {
			string data = previousBlockHash + to_string(timestamp);
			for (int i = 0; i < Transactions.size(); i++) {
				data += Transactions[i].getTransactionId();
			}
			return hashfun(data);
		}

		string getBlockHash() {
			return blockHash;
		}

		block(string PBH) {
			previousBlockHash = PBH;
			timestamp = time(0);
			blockHash = calculateBlockHash();
		}
};
