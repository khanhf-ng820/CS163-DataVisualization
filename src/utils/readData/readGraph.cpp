#include "utils/readData/readGraph.h"





// --- Read Graph data ---
bool GraphReader::validDataGraphFile(std::ifstream& ifile, GraphReader::GraphInitMethod initMethod) {
	if (!ifile.is_open())
		return false; // Can't open file

	switch (initMethod) {
	case GraphReader::GraphInitMethod::ADJ_MATRIX:
		return GraphReader::validDataAdjMatFile(ifile);
	case GraphReader::GraphInitMethod::ADJ_LIST:
		return GraphReader::validDataAdjListFile(ifile);
	case GraphReader::GraphInitMethod::EDGE_LIST:
		return GraphReader::validDataEdgeListFile(ifile);
	}

	// short int num;
	// bool read = false;
	// unsigned int inputCount = 0;
	// while (ifile >> num) {
	// 	read = true; // Successfully read an int
	// 	inputCount++;
	// 	if (inputCount > GRAPH_INIT_MAX_SIZE) {
	// 		ifile.clear(); // Cleanup
	// 		ifile.seekg(0, std::ios::beg);
	// 		return false;
	// 	}
	// }
	// bool isValid = read && ifile.eof();

	// ifile.clear(); // Cleanup
	// ifile.seekg(0, std::ios::beg);
	// return isValid; // Valid if reached EOF
}





bool GraphReader::validDataGraphString(std::string& data, GraphReader::GraphInitMethod initMethod) {
	// std::string trimmedData = trim(data);
	// std::istringstream iss(trimmedData);

	switch (initMethod) {
	case GraphReader::GraphInitMethod::ADJ_MATRIX:
		return GraphReader::validDataAdjMatString(data);
	case GraphReader::GraphInitMethod::ADJ_LIST:
		return GraphReader::validDataAdjListString(data);
	case GraphReader::GraphInitMethod::EDGE_LIST:
		return GraphReader::validDataEdgeListString(data);
	}

	// short int num;
	// bool read = false;
	// unsigned int inputCount = 0;
	// while (iss >> num) {
	// 	read = true;
	// 	inputCount++;
	// 	if (inputCount > GRAPH_INIT_MAX_SIZE) {
	// 		return false;
	// 	}
	// }

	// return read && iss.eof();
}





// std::vector<GraphReader::GraphEdge> GraphReader::getDataGraphFile(std::ifstream& ifile, GraphReader::GraphInitMethod initMethod) {
// 	if (!ifile.is_open()) return {};
// 	if (!validDataGraphFile(ifile, initMethod)) return {};

// 	std::vector<int> vec;
// 	short int num;
// 	while (ifile >> num) {
// 		vec.push_back(num);
// 	}

// 	ifile.clear(); // Cleanup
// 	ifile.seekg(0, std::ios::beg);
// 	return vec;
// }





// std::vector<GraphReader::GraphEdge> GraphReader::getDataGraphString(std::string& data, GraphReader::GraphInitMethod initMethod) {
// 	if (!validDataGraphString(data)) return {};

// 	std::string trimmedData = trim(data);
// 	std::istringstream iss(trimmedData);
// 	std::vector<int> vec;
// 	short int num;
// 	while (iss >> num) {
// 		vec.push_back(num);
// 	}

// 	return vec;
// }
