#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <chrono>


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
	int choice;
	cout << "1 - generuoti bloku grandine is visu transakciju" << endl;
	cout << "2 - sudaryti 5 blokus kandidatus" << endl;
	while (!(cin >> choice) || (choice != 1 && choice != 2)) {
		cout << "Neteisingas pasirinkimas. Bandykite dar karta" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	switch (choice) {
		case 1: {
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
						cout << "Nenurodytas transakcijos ID." << endl;
					}
				}
				else if (command == "outBlock") {
					if (!argument.empty()) {
						get_block(argument, blockchain);
					}
					else {
						cout << "Nenurodyta bloko maisos funkcija." << endl;
					}
				}
				else {
					cout << "Neteisinga ivestis." << endl;
				}
			}
			break;
		}
		case 2: {
				block lastBlock = blockchain.back();
				uint64_t nonce = 0;
				string PBhash = mineBlock(lastBlock.getPBH(), lastBlock.getTimestamp(), lastBlock.getVersion(), lastBlock.getMerkleRootHash(), nonce, lastBlock.getDifficultyTarget());
				vector<block> candidates;

			for (int i = 0; i < 5; i++) {
				vector<transaction> selectedTran = selectRandomTransactions(tran);
				block newBlock(PBhash, diffTarget, selectedTran);
				newBlock.setNonce(nonce);
				candidates.push_back(newBlock);
				newBlock.printBlock();
				cout << i << " blokas sugeneruotas" << endl;
			}

			string candidateMining = "";
			bool blockMined = false;

			for (int i = 0; i < 5; i++) {
				auto start = chrono::steady_clock::now();
				auto end = start + chrono::seconds(5);
				candidateMining = mineBlock(candidates[i].getPBH(), candidates[i].getTimestamp(), candidates[i].getVersion(), candidates[i].getMerkleRootHash(), nonce, candidates[i].getDifficultyTarget(), end);
			
				if (!candidateMining.empty()) {
					cout << "Blokas iskastas - " << candidateMining << endl;
					cout << "Is " << i +1 << " bandymo" << endl;
					blockMined = true;
					break;
				}
				if (chrono::steady_clock::now() >= end) {
					cout << "Laiko limitas pasiektas. Stabdomas " << i+1 << " bloko kasimas." << endl;
				}
			}
			if (!blockMined) {
				cout << "Nei vienas is 5 bloku nebuvo iskastas" << endl;;
			}
		}
	}


    return 0;
}
