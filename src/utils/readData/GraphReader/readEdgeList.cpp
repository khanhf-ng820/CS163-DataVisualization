#include "utils/readData/GraphReader/readEdgeList.h"





bool GraphReader::validDataEdgeListFile(std::ifstream& ifile) {
	if (!ifile.is_open())
		return false; // Can't open file

	// Read number of vertices |V|
	unsigned short int numVertices;
	if (ifile >> numVertices) {
		if (numVertices > GRAPH_INIT_NUM_VERTICES_MAX) {
			ifile.clear(); // Cleanup
			ifile.seekg(0, std::ios::beg);
			return false;
		}
	} else {
		ifile.clear(); // Cleanup
		ifile.seekg(0, std::ios::beg);
		return false;
	}

	// Read each edge
	unsigned short int vertex1, vertex2, weight;
	bool read = false;
	// unsigned int inputCount = 0;

	while (ifile >> vertex1 >> vertex2 >> weight) {
		read = true; // Successfully read an int
		// inputCount++;
		// if (inputCount > GRAPH_INIT_NUM_VERTICES_MAX * GRAPH_INIT_NUM_VERTICES_MAX) {
		// 	ifile.clear(); // Cleanup
		// 	ifile.seekg(0, std::ios::beg);
		// 	return false;
		// }
	}

	// bool isValidEdgeList = isPerfectSquare(inputCount);
	bool isValid = read && ifile.eof();

	ifile.clear(); // Cleanup
	ifile.seekg(0, std::ios::beg);
	return isValid; // Valid if reached EOF
}





bool GraphReader::validDataEdgeListString(std::string& data) {
	std::string trimmedData = trim(data);
	std::istringstream iss(trimmedData);

	// Read number of vertices |V|
	unsigned short int numVertices;
	if (iss >> numVertices) {
		if (numVertices > GRAPH_INIT_NUM_VERTICES_MAX) {
			return false;
		}
	} else {
		return false;
	}

	// Read each edge
	unsigned short int vertex1, vertex2, weight;
	bool read = false;
	// unsigned int inputCount = 0;

	while (iss >> vertex1 >> vertex2 >> weight) {
		read = true;
		// inputCount++;
		// if (inputCount > GRAPH_INIT_NUM_VERTICES_MAX * GRAPH_INIT_NUM_VERTICES_MAX) {
		// 	return false;
		// }
	}

	// bool isValidEdgeList = isPerfectSquare(inputCount);
	return read && iss.eof();
}





std::vector<GraphReader::GraphEdge> GraphReader::getDataEdgeListFile(std::ifstream& ifile) {
	if (!ifile.is_open()) return {};
	if (!validDataEdgeListFile(ifile)) return {};

	std::vector<GraphReader::GraphEdge> edges;

	// Read number of vertices |V|
	unsigned short int numVertices;
	ifile >> numVertices;

	// Read each edge
	unsigned short int vertex1, vertex2, weight;
	while (ifile >> vertex1 >> vertex2 >> weight) {
		edges.push_back(GraphReader::GraphEdge(vertex1, vertex2, weight));
	}

	ifile.clear(); // Cleanup
	ifile.seekg(0, std::ios::beg);
	return edges;
}





std::vector<GraphReader::GraphEdge> GraphReader::getDataEdgeListString(std::string& data) {
	if (!validDataEdgeListString(data)) return {};

	std::string trimmedData = trim(data);
	std::istringstream iss(trimmedData);

	std::vector<GraphReader::GraphEdge> edges;
	
	// Read number of vertices |V|
	unsigned short int numVertices;
	iss >> numVertices;

	// Read each edge
	unsigned short int vertex1, vertex2, weight;
	while (iss >> vertex1 >> vertex2 >> weight) {
		edges.push_back(GraphReader::GraphEdge(vertex1, vertex2, weight));
	}

	return edges;
}
