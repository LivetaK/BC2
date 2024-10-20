#include "class.hpp"
#include "function.h"
#include "function.cpp"

using namespace std;


int main() {

	srand(time(0));
	vector<user> randomUsers;
	generateRandomUsers(randomUsers);
	vector<user> updatedUsers;
	updatedUsers == randomUsers;
	vector<transaction> tran;
	generateRandomTransactions(tran, updatedUsers);

}
