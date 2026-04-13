#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "utils/utils.h"
#include "Graph/const.h"
#include "utils/readData/GraphReader/const.h"
#include "utils/readData/GraphReader/readAdjMatrix.h"
#include "utils/readData/GraphReader/readAdjList.h"
#include "utils/readData/GraphReader/readEdgeList.h"





// --- Read Graph data ---
namespace GraphReader {
	bool validDataGraphFile(std::ifstream& ifile, 
		GraphReader::GraphInitMethod initMethod);
	bool validDataGraphString(std::string& data, 
		GraphReader::GraphInitMethod initMethod);
	// std::vector<GraphEdge> getDataGraphFile(std::ifstream& ifile, 
	// 	GraphReader::GraphInitMethod initMethod);
	// std::vector<GraphEdge> getDataGraphString(std::string& data, 
	// 	GraphReader::GraphInitMethod initMethod);
};
