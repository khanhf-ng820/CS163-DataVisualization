#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "utils/utils.h"
#include "utils/readData/GraphReader/const.h"
#include "Graph/const.h"





// --- Read Graph data ---
namespace GraphReader {
	bool validDataAdjListFile(std::ifstream& ifile);
	bool validDataAdjListString(std::string& data);
	std::vector<std::vector<int>> getDataAdjListFile(std::ifstream& ifile);
	std::vector<std::vector<int>> getDataAdjListString(std::string& data);
};
