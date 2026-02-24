#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>



// --- Read SLL data ---
inline const bool validDataSLLFile(std::ifstream& ifile) {
	if (!ifile.is_open())
		return false; // Can't open file
	
	int num;
	bool read = false;
	while (ifile >> num) {
		read = true; // Successfully read an int
	}

	ifile.clear(); // Cleanup
	ifile.seekg(0, std::ios::beg);
	return read && ifile.eof(); // Valid if reached EOF
}

inline const bool validDataSLLString(std::string& data) {
	std::istringstream iss(data);

	int num;
	bool read = false;
	while (iss >> num) {
		read = true;
	}

	return read && iss.eof();
}

inline const std::vector<int> getDataSLLFile(std::ifstream& ifile) {
	if (!ifile.is_open()) return {};
	if (!validDataSLLFile(ifile)) return {};

	std::vector<int> vec;
	int num;
	while (ifile >> num) {
		vec.push_back(num);
	}

	ifile.clear(); // Cleanup
	ifile.seekg(0, std::ios::beg);
	return vec;
}

inline const std::vector<int> getDataSLLString(std::string& data) {
	if (!validDataSLLString(data)) return {};

	std::istringstream iss(data);
	std::vector<int> vec;
	int num;
	while (iss >> num) {
		vec.push_back(num);
	}

	return vec;
}
