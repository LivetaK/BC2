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
    uint32_t diffTarget = 5;

	vector<transaction> genesisBlockTran = selectRandomTransactions(tran);

    block genesisBlock(genesisPBH, diffTarget, genesisBlockTran);

	blockchain.push_back(genesisBlock);
    genesisBlock.printBlock();

	// genesis end
	while (tran.size() != 0) {
		block lastBlock = blockchain.back();
		uint64_t nonce = 0;
		string PBhash = mineBlock(lastBlock.getPBH(), lastBlock.getTimestamp(), lastBlock.getVersion(), lastBlock.getMerkleRootHash(), nonce, lastBlock.getDifficultyTarget());
		vector<transaction> selectedTran = selectRandomTransactions(tran);
		block newBlock(PBhash, diffTarget, selectedTran);
		newBlock.setNonce(nonce);
		blockchain.push_back(newBlock);
		newBlock.printBlock();
	}
	//blockchain[0].printBlock();
	//blockchain[1].printBlock();
	//blockchain[2].printBlock();



    return 0;
}
