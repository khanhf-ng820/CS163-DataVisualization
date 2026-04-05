#include "InitData.h"



// --- Open data structure .txt files
void Program::createAndOpen(const fs::path dataFilePath) {
	fs::create_directories(dataFilePath.parent_path());
	std::ifstream dataFile = std::ifstream(dataFilePath);
	if (!dataFile) {
		std::ofstream createFile(dataFilePath);
		createFile.close();
		std::cout << "-- Created file" << dataFilePath << std::endl; // DEBUG
		// dataFile.open(dataFilePath, std::ios::in | std::ios::out);
	} else {
		std::cout << "-- " << dataFilePath << " file exists" << std::endl; // DEBUG
	}
	dataFile.close();
}





// --- Initialize data structures ---
///// SINGLY LINKED LIST /////
bool Program::initSLL(const int dataInitOption) {
	bool validData; // Whether data from file/string is valid
	std::string dataString; // String of data
	std::vector<int> SLLData; // Data to be initialized into SLL

	switch (dataInitOption) {
	case DATA_INIT_CUSTOM: // Custom data as string
		dataString = std::string(customDataSLLbuf);
		validData = validDataSLLString(dataString);

		if (!validData) {
			// THIS BRANCH SHOULD NOT RUN IN PRACTICE
			std::cout << "Invalid data string. Something went wrong!!"<<std::endl; // Invalid data
			visEngine_SLL.resetEngine(); // Free all memory, reset entire engine

			visEngine_SLL.initSLLData();
			return false;
		}
		visEngine_SLL.resetEngine(); // Free all memory, reset entire engine

		SLLData = getDataSLLString(dataString);
		visEngine_SLL.initSLLData(SLLData);

		return true;
	case DATA_INIT_FROM_FILE: // Data from file
		SLL_dataFile.open(SLL_DATA_FILEPATH); // Open data file
		validData = validDataSLLFile(SLL_dataFile);

		if (!validData) {
			std::cout << "Invalid data file. Check the .txt data file and try again." << std::endl; // Invalid data
			visEngine_SLL.resetEngine(); // Free all memory, reset entire engine
			visEngine_SLL.initSLLData();

			SLL_dataFile.close(); // Close the data file
			return false;
		}
		visEngine_SLL.resetEngine(); // Free all memory, reset entire engine

		SLLData = getDataSLLFile(SLL_dataFile);
		visEngine_SLL.initSLLData(SLLData);

		SLL_dataFile.close(); // Close the data file
		return true;
	case DATA_INIT_RANDOMIZED: // Randomized data
		visEngine_SLL.resetEngine(); // Free all memory, reset entire engine
		visEngine_SLL.initSLLData(rng);

		return true;
	case DATA_INIT_EMPTY: // Empty data
	default:
		visEngine_SLL.resetEngine(); // Free all memory, reset entire engine
		visEngine_SLL.initSLLData();

		return true;
	}
}





///// HASH TABLE (LINEAR PROBING) /////
bool Program::initHashTable(const int dataInitOption) {
	bool validData; // Whether data from file/string is valid
	std::string dataString; // String of data
	std::vector<TableSlotInput> hashTableData; // Data to be initialized into HashTable

	switch (dataInitOption) {
	case DATA_INIT_CUSTOM: // Custom data as string
		dataString = std::string(customDataHashbuf);
		validData = validDataHashTableString(dataString);

		if (!validData) {
			//// THIS BRANCH SHOULD NOT RUN IN PRACTICE
			std::cout << "Invalid data string. Something went wrong!!" << std::endl; // Invalid data

			visEngine_Hash = HashVisEngine(initHashTableSizeBuf, initHashTableSizeBuf, &window, &textFont);
			return false;
		}

		hashTableData = getDataHashTableString(dataString);
		visEngine_Hash = HashVisEngine(hashTableData, hashTableData.size(), &window, &textFont);

		return true;
	case DATA_INIT_FROM_FILE: // Data from file
		hashTable_dataFile.open(HASH_DATA_FILEPATH); // Open data file
		validData = validDataHashTableFile(hashTable_dataFile);

		if (!validData) {
			std::cout << "Invalid data file. Check the .txt data file and try again." << std::endl; // Invalid data

			visEngine_Hash = HashVisEngine(initHashTableSizeBuf, initHashTableSizeBuf, &window, &textFont);
			hashTable_dataFile.close(); // Close the data file
			return false;
		}

		hashTableData = getDataHashTableFile(hashTable_dataFile);
		visEngine_Hash = HashVisEngine(hashTableData, hashTableData.size(), &window, &textFont);

		hashTable_dataFile.close(); // Close the data file
		return true;
	case DATA_INIT_RANDOMIZED: // Randomized data
		visEngine_Hash = HashVisEngine(initHashTableSizeBuf, initHashTableSizeBuf, rng, &window, &textFont);
		return true;
	case DATA_INIT_EMPTY: // Empty data
	default:
		visEngine_Hash = HashVisEngine(initHashTableSizeBuf, initHashTableSizeBuf, &window, &textFont);
		return true;
	}
}





///// AVL TREE /////
bool Program::initAVL(const int dataInitOption) {
	bool validData; // Whether data from file/string is valid
	std::string dataString; // String of data
	std::vector<int> AVLData; // Data to be initialized into AVL Tree

	switch (dataInitOption) {
	case DATA_INIT_CUSTOM: // Custom data as string
		dataString = std::string(customDataAVLbuf);
		validData = validDataAVLString(dataString);

		if (!validData) {
			//// THIS BRANCH SHOULD NOT RUN IN PRACTICE
			std::cout << "Invalid data string. Something went wrong!!" << std::endl; // Invalid data

			visEngine_AVL = AVLVisEngine(&window, &textFont);
			return false;
		}

		AVLData = getDataAVLString(dataString);
		visEngine_AVL = AVLVisEngine(AVLData, &window, &textFont);

		return true;
	case DATA_INIT_FROM_FILE: // Data from file
		AVL_dataFile.open(AVL_DATA_FILEPATH); // Open data file
		validData = validDataAVLFile(AVL_dataFile);

		if (!validData) {
			std::cout << "Invalid data file. Check the .txt data file and try again." << std::endl; // Invalid data

			visEngine_AVL = AVLVisEngine(&window, &textFont);
			AVL_dataFile.close(); // Close the data file
			return false;
		}

		AVLData = getDataAVLFile(AVL_dataFile);
		visEngine_AVL = AVLVisEngine(AVLData, &window, &textFont);

		AVL_dataFile.close(); // Close the data file
		return true;
	case DATA_INIT_RANDOMIZED: // Randomized data
		visEngine_AVL = AVLVisEngine(rng, &window, &textFont);
		return true;
	case DATA_INIT_EMPTY: // Empty data
	default:
		visEngine_AVL = AVLVisEngine(&window, &textFont);
		return true;
	}
}





///// TRIE (26-ARY TREE) /////
bool Program::initTrie(const int dataInitOption) {
	bool validData; // Whether data from file/string is valid
	std::string dataString; // String of data
	std::vector<std::string> trieData; // Data to be initialized into Trie

	switch (dataInitOption) {
	case DATA_INIT_CUSTOM: // Custom data as string
		dataString = std::string(customDataTriebuf);
		validData = validDataTrieString(dataString);

		if (!validData) {
			//// THIS BRANCH SHOULD NOT RUN IN PRACTICE
			std::cout << "Invalid data string. Something went wrong!!" << std::endl; // Invalid data

			visEngine_Trie = TrieVisEngine(&window, &textFont);
			return false;
		}

		trieData = getDataTrieString(dataString);
		visEngine_Trie = TrieVisEngine(trieData, &window, &textFont);

		return true;
	case DATA_INIT_FROM_FILE: // Data from file
		trie_dataFile.open(TRIE_DATA_FILEPATH); // Open data file
		validData = validDataTrieFile(trie_dataFile);

		if (!validData) {
			std::cout << "Invalid data file. Check the .txt data file and try again." << std::endl; // Invalid data

			visEngine_Trie = TrieVisEngine(&window, &textFont);
			trie_dataFile.close(); // Close the data file
			return false;
		}

		trieData = getDataTrieFile(trie_dataFile);
		visEngine_Trie = TrieVisEngine(trieData, &window, &textFont);

		trie_dataFile.close(); // Close the data file
		return true;
	case DATA_INIT_RANDOMIZED: // Randomized data
		visEngine_Trie = TrieVisEngine(rng, &window, &textFont);
		return true;
	case DATA_INIT_EMPTY: // Empty data
	default:
		visEngine_Trie = TrieVisEngine(&window, &textFont);
		return true;
	}
}
