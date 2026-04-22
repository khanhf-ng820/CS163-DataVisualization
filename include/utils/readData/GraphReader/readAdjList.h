#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <climits>

#include "utils/utils.h"
#include "utils/readData/GraphReader/GraphInitMethod.h"
#include "Graph/const.h"
#include "Graph/EdgeStruct.h"





// --- Read Graph data ---
namespace GraphReader {
	bool validDataAdjListFile(std::ifstream& ifile);
	bool validDataAdjListString(std::string& data);
	std::vector<std::vector<Edge>> getDataAdjListFile(std::ifstream& ifile);
	std::vector<std::vector<Edge>> getDataAdjListString(std::string& data);
};
