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
	
    // Define genesis block parameters
    std::string genesisPBH = "0000000000000000000000000000000000000000000000000000000000000000";
    uint32_t ver = 1;          // Version number
    uint32_t diffTarget = 4;   // Difficulty target

    // Create genesis block
    block genesisBlock(genesisPBH, ver, diffTarget, tran);

    // Mine the genesis block
    genesisBlock.mineBlock();

    // Print the block details
    genesisBlock.printBlock();

    return 0;

}
