#include "initData.h"



// --- Open data structure .txt files
void Program::createAndOpen(const fs::path dataFilePath) {
	fs::create_directories(dataFilePath.parent_path());
	SLL_dataFile = std::ifstream(dataFilePath);
	if (!SLL_dataFile) {
		std::ofstream createFile(dataFilePath);
		createFile.close();
		std::cout << "-- Created file" << dataFilePath << std::endl; // DEBUG
		// SLL_dataFile.open(dataFilePath, std::ios::in | std::ios::out);
	} else {
		std::cout << "-- " << dataFilePath << " file exists" << std::endl; // DEBUG
	}
	SLL_dataFile.close();
}





// --- Initialize data structures
bool Program::initSLL(const int dataInitOption) {
	bool validData;
	std::string dataString;

	switch (dataInitOption) {
	case DATA_INIT_RANDOMIZED: // Randomized data
		visEngine_SLL.resetEngine(); // Free all memory, reset entire engine
		visEngine_SLL.initSLLData(rng);
		return true;
	case DATA_INIT_CUSTOM: // Custom data as string
		dataString = std::string(customDataSLLbuf);
		validData = validDataSLLString(dataString);
		if (!validData) {
			// SHOULD NOT PRINT IN PRACTICE
			std::cout << "Invalid data string. Something went wrong!!" <<std::endl; // Invalid data
			visEngine_SLL.resetEngine(); // Free all memory, reset entire engine
			visEngine_SLL.initSLLData();
			return false;
		} else {
			visEngine_SLL.resetEngine(); // Free all memory, reset entire engine
			visEngine_SLL.initSLLData(getDataSLLString(dataString));
		}
		return true;
	case DATA_INIT_FROM_FILE: // Data from file
		SLL_dataFile.open(SLL_DATA_FILEPATH); // Open data file
		validData = validDataSLLFile(SLL_dataFile);
		if (!validData) {
			std::cout << "Invalid data file. Check the .txt data file and try again." << std::endl; // Invalid data
			visEngine_SLL.resetEngine(); // Free all memory, reset entire engine
			visEngine_SLL.initSLLData();
			return false;
		} else {
			visEngine_SLL.resetEngine(); // Free all memory, reset entire engine
			visEngine_SLL.initSLLData(getDataSLLFile(SLL_dataFile));
		}
		SLL_dataFile.close();
		return true;
	case DATA_INIT_EMPTY: // Empty data
	default:
		visEngine_SLL.resetEngine(); // Free all memory, reset entire engine
		visEngine_SLL.initSLLData();
		return true;
	}
}
