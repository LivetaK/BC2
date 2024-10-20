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

};