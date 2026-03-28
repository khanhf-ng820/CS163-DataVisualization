#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "utils/utils.h"

static constexpr unsigned int MAX_HASH_TABLE_SIZE = 128;

// --- Class for representation of a slot in text file, for init HashTable ---
inline const bool validSlotInput(std::string input) {
	if (input == "n" || input == "N") return true;
	try {
		int convertedInput = std::stoi(input);
		return true;
	} catch (const std::invalid_argument& e) {
		std::cerr << "-- An error occured: " << e.what() << std::endl;
	}
	return false;
}
class TableSlotInput {
public:
	TableSlotInput() {}
	TableSlotInput(int keyVal) : key(keyVal), empty(false) {}
	TableSlotInput(std::string keyInput)
		: TableSlotInput((!validSlotInput(keyInput) || keyInput == "n" || keyInput == "N") ? -1 : std::stoi(keyInput)) {
		if (key == -1) empty = true;
	}

	int key = -1;
	bool empty = true;
};




// --- Read HashTable data ---
inline const bool validDataHashTableFile(std::ifstream& ifile) {
	if (!ifile.is_open()) {
		std::cerr << "-- Could not open file for Hash Table!" << std::endl;
		return false; // Can't open file
	}

	std::string keyInput;
	bool read = false, isValid = true;
	int inputCount = 0;
	while (ifile >> keyInput) {
		read = true; // Successfully read an int key / "NONE"
		inputCount++; // Increase counter
		if (inputCount > MAX_HASH_TABLE_SIZE) {
			isValid = false;
			break;
		}
		if (!validSlotInput(keyInput)) {
			isValid = false;
		}
	}
	isValid &= read && ifile.eof() && (inputCount > 1);

	ifile.clear(); // Cleanup
	ifile.seekg(0, std::ios::beg);
	return isValid; // Valid if reached EOF
}


inline const bool validDataHashTableString(std::string& data) {
	std::string trimmedData = trim(data);
	std::istringstream iss(trimmedData);

	std::string keyInput;
	bool read = false;
	int inputCount = 0;
	while (iss >> keyInput) {
		read = true;
		inputCount++; // Increase counter
		if (inputCount > MAX_HASH_TABLE_SIZE) {
			return false;
		}
		if (!validSlotInput(keyInput)) {
			return false;
		}
	}

	return read && iss.eof() && (inputCount > 1);
}


inline const std::vector<TableSlotInput> getDataHashTableFile(std::ifstream& ifile) {
	if (!ifile.is_open()) return {};
	if (!validDataHashTableFile(ifile)) return {};

	std::vector<TableSlotInput> vec;
	std::string keyInput;
	while (ifile >> keyInput) {
		vec.push_back(TableSlotInput(keyInput));
	}

	ifile.clear(); // Cleanup
	ifile.seekg(0, std::ios::beg);
	return vec;
}


inline const std::vector<TableSlotInput> getDataHashTableString(std::string& data) {
	if (!validDataHashTableString(data)) return {};

	std::string trimmedData = trim(data);
	std::istringstream iss(trimmedData);
	std::vector<TableSlotInput> vec;
	std::string keyInput;
	while (iss >> keyInput) {
		vec.push_back(TableSlotInput(keyInput));
	}

	return vec;
}
