#include "class.hpp"
#include "function.h"


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

	srand(time(0));

	string names[] = { "Liveta", "Roberta", "Paulina", "Ugne", "Gabriele", "Kamile", "Marija", "Rugile", "Jovita", "Adriana" };

	for (int i = 0; i < 1000; i++) {

		user tempUser;
		string key = generateRandomKey();

		tempUser.setName(names[rand() % (sizeof(names) / sizeof(names[0]))]);
		tempUser.setPublicKey(key);
		tempUser.setBalance(100 + (rand() % 1000000));

		randomUsers.push_back(tempUser);
	}
}


void generateRandomTransactions(vector<transaction>& tran) {

	srand(time(0));

}
