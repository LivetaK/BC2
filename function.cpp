#include "function.h"
#include "class.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <bitset>
#include <random>

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

	for (int i = 0; i < 1000; i++) {

		user tempUser;
		string key = generateRandomKey();

		tempUser.setName("User" + to_string(i));
		tempUser.setPublicKey(key);
		tempUser.setBalance(rand() % (1000000 - 99) + 100);

		randomUsers.push_back(tempUser);
	}
}


void generateRandomTransactions(vector<transaction>& tran, vector<user>& updatedUsers) {

	for (int i = 0; i < 10000; i++){

		transaction tempTran;

		int sender = rand() % updatedUsers.size(); // random indeksas
		tempTran.setSender(updatedUsers[sender].getPublicKey());


		int recipient = rand() % updatedUsers.size(); //random indeksas
		while (recipient == sender) {
			recipient = rand() % updatedUsers.size();
		}
		tempTran.setRecipient(updatedUsers[recipient].getPublicKey());


		double amount = 1 + ((double)rand() / RAND_MAX) * (updatedUsers[sender].getBalance() - 1);
		tempTran.setAmount(amount);

		//double oldSenderBalance = updatedUsers[sender].getBalance();
		//updatedUsers[sender].setBalance(oldSenderBalance - amount);

		//double oldRecipientBalance = updatedUsers[recipient].getBalance();
		//updatedUsers[recipient].setBalance(oldRecipientBalance + amount);

		string transactionID = updatedUsers[sender].getPublicKey() + updatedUsers[recipient].getPublicKey() + to_string(amount);
		tempTran.setTransactionId(hashfun(transactionID));

		tran.push_back(tempTran);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////// hashinimo funkcija
string tikrinimas(string code) {
	if (code.length() > 256) {
		string result = code.substr(0, 256);
		string remaining = code.substr(256);
		int j = 0;
		while (j < remaining.length()) {
			for (int i = 0; i < 256; i++) {
				if (j >= remaining.length()) {
					break;
				}
				result[i] = (result[i] == remaining[j]) ? '0' : '1';
				j++;
			}
		}
		return result;


	}
	else if (code.length() == 0) {
		code.resize(256, '0');
		return code;

	}
	else { // (code.length() < 256)
		char bi = code[0];
		code.resize(50, bi);
		bi = code[7];
		code.resize(100, bi);
		bi = code[4];
		code.resize(150, bi);
		bi = code[2];
		code.resize(200, bi);
		bi = code[3];
		code.resize(256, bi);
		return code;
	}
}

char convertHex(const string& fourBits) {
	int decimalValue = stoi(fourBits, nullptr, 2);
	switch (decimalValue) {
	case 0: return '0';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	case 10: return 'a';
	case 11: return 'b';
	case 12: return 'c';
	case 13: return 'd';
	case 14: return 'e';
	case 15: return 'f';
	}
}

string binaryTohex(string kodas) {
	string hex;
	for (int i = 0; i < 256; i += 4) {
		string fourBits = kodas.substr(i, 4);
		hex += convertHex(fourBits);
	}
	return hex;
}


string skaiciavimai(string tempDec) { //128 max
	int n = tempDec.length();
	int y = n / 9;
	int x = n % 9;
	vector <string> chunk;
	int j = 0;
	for (int i = 0; i < y; i++) {
		chunk.push_back(tempDec.substr(j, 9));;
		j += 9;
	}
	if (x > 0) {
		chunk.push_back(tempDec.substr(j, x));
	}

	vector <int> chunkInt;
	for (string part : chunk) {
		chunkInt.push_back(stoi(part));
	}
	int numChunks = chunkInt.size();

	string mainString;
	int half = numChunks / 2;
	unsigned long long result = 0;
	for (int i = 0; i < half; i++) {
		result = chunkInt[i] * chunkInt[i + half];
		mainString += to_string(result);
		result = 0;
	}
	if (numChunks % 2 == 1) {
		result = chunkInt[0] * chunkInt[numChunks - 1];
		mainString += to_string(result);
		result = 0;
	}

	return mainString;
}

string manipulation(string code) {
	reverse(code.begin(), code.end());
	string kodas = tikrinimas(code);
	string ran1 = "1100110011001100110011110";
	string ran2 = "01010101010101010101010101010101010";
	string ran3 = "100011010111010001010100011010110111100";
	string ran4 = "011010010101101010100110111010101010001011101000111";
	string ran5 = "1110001110001110";
	string ran6 = "01010001110101000101110101011110101010010001011100100";
	string ran7 = "10100110101101010101000010101010111101010111000000101011";



	for (int i = 0; i < 25; i++) {
		kodas[i] = (kodas[i] == ran1[i]) ? '0' : '1';
	}
	for (int i = 25; i < 60; i++) {
		kodas[i] = (kodas[i] == ran2[i - 25]) ? '1' : '0';
	}
	for (int i = 60; i < 99; i++) {
		kodas[i] = (kodas[i] == ran3[i - 60]) ? '0' : '1';
	}
	for (int i = 99; i < 150; i++) {
		kodas[i] = (kodas[i] == ran4[i - 99]) ? '1' : '0';
	}
	for (int i = 150; i < 166; i++) {
		kodas[i] = (kodas[i] == ran5[i - 150]) ? '0' : '1';
	}
	for (int i = 166; i < 222; i++) {
		kodas[i] = (kodas[i] == ran6[i - 166]) ? '1' : '0';
	}
	for (int i = 222; i < 256; i++) {
		kodas[i] = (kodas[i] == ran7[i - 222]) ? '0' : '1';
	}

	string tempHex = binaryTohex(kodas);
	string tempDec;


	//cout << kodas << endl;
	//cout << tempHex << endl;


	for (char number : tempHex) {
		if (number >= '0' && number <= '9') {
			tempDec += number;
		}
		else {
			int decimalValue = number - 'a' + 10;
			tempDec += to_string(decimalValue);
		}
	}
	//cout << tempDec << endl;

	kodas.clear();
	kodas = skaiciavimai(tempDec);

	//cout << "kodas" << kodas << endl;
	vector<char> inputVector(kodas.begin(), kodas.end());
	string kodass;
	for (char c : inputVector) {
		bitset<8> binary(c);
		kodass += binary.to_string();
	}
	string Code = tikrinimas(kodass);
	string manCode;

	string codeOne = Code.substr(0, 17);
	string codeTwo = Code.substr(17, 17);
	string codeThree = Code.substr(34, 17);
	string codeFour = Code.substr(51, 17);
	string codeFive = Code.substr(68, 17);
	string codeSix = Code.substr(85, 17);
	string codeSeven = Code.substr(102, 17);
	string codeEight = Code.substr(119, 17);
	string codeNine = Code.substr(136, 17);
	string codeTen = Code.substr(153, 17);
	string codeEleven = Code.substr(170, 17);
	string codeTwelve = Code.substr(187, 17);
	string codeThirteen = Code.substr(204, 17);
	string codeFourteen = Code.substr(221, 17);
	string codeFifteen = Code.substr(238, 17);
	string codeSixteen = Code.substr(255, 1);

	for (int i = 0; i < 17; ++i) {
		swap(codeOne[i], codeEleven[i]);
		swap(codeTwo[i], codeNine[i]);
		swap(codeThree[i], codeTwelve[i]);
		swap(codeFour[i], codeFourteen[i]);
		swap(codeFive[i], codeFifteen[i]);
		swap(codeSix[i], codeThirteen[i]);
		swap(codeSeven[i], codeOne[i]);
		swap(codeEight[i], codeTwo[i]);
		swap(codeNine[i], codeSix[i]);
		swap(codeTen[i], codeThirteen[i]);
	}

	reverse(codeOne.begin(), codeOne.end());
	reverse(codeTwo.begin(), codeTwo.end());
	rotate(codeThree.begin(), codeThree.begin() + 5, codeThree.end());
	rotate(codeFour.begin(), codeFour.begin() + 7, codeFour.end());
	reverse(codeFive.begin(), codeFive.end());
	reverse(codeSix.begin(), codeSix.end());
	rotate(codeSeven.begin(), codeSeven.begin() + 3, codeSeven.end());
	reverse(codeEight.begin(), codeEight.end());
	rotate(codeNine.begin(), codeNine.begin() + 4, codeNine.end());
	reverse(codeTen.begin(), codeTen.end());
	reverse(codeEleven.begin(), codeEleven.end());
	rotate(codeTwelve.begin(), codeTwelve.begin() + 6, codeTwelve.end());
	reverse(codeThirteen.begin(), codeThirteen.end());
	rotate(codeFourteen.begin(), codeFourteen.begin() + 5, codeFourteen.end());
	reverse(codeFifteen.begin(), codeFifteen.end());

	manCode += codeOne;
	manCode += codeTwo;
	manCode += codeThree;
	manCode += codeFour;
	manCode += codeFive;
	manCode += codeSix;
	manCode += codeSixteen;
	manCode += codeSeven;
	manCode += codeEight;
	manCode += codeNine;
	manCode += codeTen;
	manCode += codeEleven;
	manCode += codeTwelve;
	manCode += codeThirteen;
	manCode += codeFourteen;
	manCode += codeFifteen;


	// paskutinis vertimas
	string hex = binaryTohex(manCode);
	return hex;
}

string hashfun(string input) {
	vector<char> inputVector(input.begin(), input.end());
	string code;
	for (char c : inputVector) {
		//int a = convert(c);
		bitset<8> binary(c);
		code += binary.to_string();
	}
	string hash = manipulation(code);
	return hash;
	hash.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////// hashinimo funkcija baigesi


//vector<transaction> selectRandomTransactions(vector<transaction>& allTransactions) {
//	const int numToSelect = 100;
//	vector<transaction> selectedTransactions;
//
//	if (allTransactions.size() <= numToSelect) {
//		selectedTransactions = allTransactions;
//	}
//	else {
//		vector<size_t> indices(allTransactions.size());
//		for (size_t i = 0; i < indices.size(); ++i) {
//			indices[i] = i;
//		}
//
//		// Random number generator
//		random_device rd;
//		mt19937 gen(rd());
//
//		// Shuffle the indices randomly
//		shuffle(indices.begin(), indices.end(), gen);
//
//		// Select the first 100 transactions based on shuffled indices
//		for (int i = 0; i < numToSelect; ++i) {
//			selectedTransactions.push_back(allTransactions[indices[i]]);
//		}
//	}
//
//	return selectedTransactions;
//}

vector<transaction> selectRandomTransactions(vector<transaction>& allTransactions) {
	vector<transaction> selectedTran;
	if (allTransactions.size() <= 100) {
		selectedTran = allTransactions;
		allTransactions.clear();
	}
	else {
		for (int i = 0; i < 100; i++) {
			int index = rand() % allTransactions.size();
			selectedTran.push_back(allTransactions[index]);
			allTransactions.erase(allTransactions.begin() + index);
		}
	}
	return selectedTran;
}