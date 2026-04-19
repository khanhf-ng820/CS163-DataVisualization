#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "utils/utils.h"
#include "utils/readData/GraphReader/GraphInitMethod.h"
#include "Graph/const.h"





// --- Read Graph data ---
namespace GraphReader {
	bool validDataAdjMatFile(std::ifstream& ifile);
	bool validDataAdjMatString(std::string& data);
	std::vector<std::vector<int>> getDataAdjMatFile(std::ifstream& ifile);
	std::vector<std::vector<int>> getDataAdjMatString(std::string& data);
};
