#include "class.hpp"
#include "function.h"
#include <iostream>
#include <cstdlib>

using namespace std;


int main() {

	srand(time(0));

	vector<user> randomUsers;
	generateRandomUsers(randomUsers);

	vector<user> updatedUsers = randomUsers;
	vector<transaction> tran;
	generateRandomTransactions(tran, updatedUsers);
	// genesis
    string genesisPBH = "0000000000000000000000000000000000000000000000000000000000000000";
    uint32_t ver = 1;
    uint32_t diffTarget = 5;

	vector<transaction> genesisBlockTran = selectRandomTransactions(tran);

    block genesisBlock(genesisPBH, ver, diffTarget, genesisBlockTran);

    genesisBlock.mineBlock();

    genesisBlock.printBlock();

	// genesis

	vector<transaction> selectedTran = selectRandomTransactions(tran);


    return 0;
}
