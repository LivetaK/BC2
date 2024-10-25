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
	vector<block> blockchain;
	// genesis
    string genesisPBH = "0000000000000000000000000000000000000000000000000000000000000000";
    uint32_t ver = 1;
    uint32_t diffTarget = 5;

	vector<transaction> genesisBlockTran = selectRandomTransactions(tran);

    block genesisBlock(genesisPBH, ver, diffTarget, genesisBlockTran);

    genesisBlock.mineBlock();
	blockchain.push_back(genesisBlock);
    genesisBlock.printBlock();

	// genesis
	while (tran.size() != 0) {
		vector<transaction> selectedTran = selectRandomTransactions(tran);
		block newBlock(blockchain[blockchain.size() - 1].getBlockHash(), ver, diffTarget, selectedTran);
		cout << "-----------------------------------------------------------------------" << endl;
		newBlock.mineBlock();
		blockchain.push_back(newBlock);
		newBlock.printBlock();
	}


    return 0;
}
