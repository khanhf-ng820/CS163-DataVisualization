#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "utils/utils.h"
#include "Trie/const.h"



// --- Read Trie data ---
inline const bool validDataTrieFile(std::ifstream& ifile) {
	if (!ifile.is_open()) {
		std::cerr << "-- Could not open file for Trie!" << std::endl;
		return false; // Can't open file
	}

	std::string wordInput;
	bool read = false, isValid = true;
	int inputCount = 0;
	while (ifile >> wordInput) {
		read = true; // Successfully read a word std::string / "NONE"
		inputCount++; // Increase counter
		if (inputCount > TRIE_INIT_MAX_SIZE) {
			isValid = false;
			break;
		}
		if (!isValidTrieString(wordInput)) {
			isValid = false;
		}
	}
	isValid &= read && ifile.eof();

	ifile.clear(); // Cleanup
	ifile.seekg(0, std::ios::beg);
	return isValid; // Valid if reached EOF
}


inline const bool validDataTrieString(std::string& data) {
	std::string trimmedData = trim(data);
	std::istringstream iss(trimmedData);

	std::string wordInput;
	bool read = false;
	int inputCount = 0;
	while (iss >> wordInput) {
		read = true;
		inputCount++; // Increase counter
		if (inputCount > TRIE_INIT_MAX_SIZE) {
			return false;
		}
		if (!isValidTrieString(wordInput)) {
			return false;
		}
	}

	return read && iss.eof();
}


inline const std::vector<std::string> getDataTrieFile(std::ifstream& ifile) {
	if (!ifile.is_open()) return {};
	if (!validDataTrieFile(ifile)) return {};

	std::vector<std::string> vec;
	std::string wordInput;
	while (ifile >> wordInput) {
		vec.push_back(std::string(wordInput));
	}

	ifile.clear(); // Cleanup
	ifile.seekg(0, std::ios::beg);
	return vec;
}


inline const std::vector<std::string> getDataTrieString(std::string& data) {
	if (!validDataTrieString(data)) return {};

	std::string trimmedData = trim(data);
	std::istringstream iss(trimmedData);
	std::vector<std::string> vec;
	std::string wordInput;
	while (iss >> wordInput) {
		vec.push_back(std::string(wordInput));
	}

	return vec;
}
