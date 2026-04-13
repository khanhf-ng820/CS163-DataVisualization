#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "utils/utils.h"
#include "utils/readData/GraphReader/const.h"
#include "Graph/const.h"
#include "Graph/EdgeStruct.h"





// --- Read Graph data ---
namespace GraphReader {
	struct GraphEdge {
		int vertexFrom, vertexTo, weight;

		GraphEdge(int v1, int v2, int w) : vertexFrom(v1), vertexTo(v2), weight(w) {};
	};

	bool validDataEdgeListFile(std::ifstream& ifile);
	bool validDataEdgeListString(std::string& data);
	std::vector<GraphEdge> getDataEdgeListFile(std::ifstream& ifile);
	std::vector<GraphEdge> getDataEdgeListString(std::string& data);
};
