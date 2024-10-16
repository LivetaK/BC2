#pragma once

#include <string>

using namespace std;



class user {
private:
	string name = " ";
	string public_key = " ";
	double balance = 0.0;
public:
	void setname(string Name) {
		name = Name;
	};

	string getname() {
		return name;
	}

	void setpublic_key(string publicKey) {
		public_key = publicKey;
	}

	string getPublicKey() {
		return public_key;
	}

	void setbalance(double Balance) {
		balance = Balance;
	}

	double getbalance() {
		return balance;
	}


};