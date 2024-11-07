#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

#include "class.hpp"
#include "function.h"

using namespace std;


int main() {

	srand(time(0));

	vector<user> randomUsers;
	generateRandomUsers(randomUsers);
	vector<transaction> tran;
	generateRandomTransactions(tran, randomUsers);
	vector<block> blockchain;
	// genesis
    string genesisPBH = "0000000000000000000000000000000000000000000000000000000000000000";
    uint32_t diffTarget = 5;

	vector<transaction> genesisBlockTran = selectRandomTransactions(tran);

    block genesisBlock(genesisPBH, diffTarget, genesisBlockTran);

	blockchain.push_back(genesisBlock);
    //genesisBlock.printBlock();

	// genesis end
	while (tran.size() != 0) {
		block lastBlock = blockchain.back();
		uint64_t nonce = 0;
		string PBhash = mineBlock(lastBlock.getPBH(), lastBlock.getTimestamp(), lastBlock.getVersion(), lastBlock.getMerkleRootHash(), nonce, lastBlock.getDifficultyTarget());
		vector<transaction> selectedTran = selectRandomTransactions(tran);
		block newBlock(PBhash, diffTarget, selectedTran);
		newBlock.setNonce(nonce);
		blockchain.push_back(newBlock);
		//newBlock.printBlock();
	}
	cout << "Transakcijos sugeneruotos" << endl;
	cout << endl;

	cout << "Jei norite pamatyti tam tikra transakcija, iveskite 'outTransaction transactionID'," << endl;
	cout << "transactionID pakeisdami realiu transakcijos ID" << endl;
	cout << endl;
	cout << "Jei norite pamatyti tam tikra bloka, iveskite 'outBlock blockHash'," << endl;
	cout << "blockHash pakeisdami realia bloko maisos reiksme" << endl;
	cout << endl;
	cout << "Noredami iseiti is programos, iveskite 'end'" << endl;

	string input;

	while (true) {
		cout << "Iveskite komanda: ";
		getline(cin, input);
		if (input == "end") {
			break;
		}
		istringstream input_stream(input);
		string command, argument;
		input_stream >> command >> argument;

		if (command == "outTransaction") {
			if (!argument.empty()) {
				get_transaction(argument, blockchain);
			}
			else {
				cout << "Nenurodytas transakcijos ID." << std::endl;
			}
		}
		else if (command == "outBlock") {
			if (!argument.empty()) {
				get_block(argument, blockchain);
			}
			else {
				cout << "Nenurodyta bloko maisos funkcija." << std::endl;
			}
		}
		else {
			cout << "Neteisinga ivestis." << std::endl;
		}
	}


    return 0;
}
