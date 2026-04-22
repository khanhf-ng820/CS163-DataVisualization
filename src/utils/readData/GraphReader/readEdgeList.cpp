#include "utils/readData/GraphReader/readEdgeList.h"





bool GraphReader::validDataEdgeListFile(std::ifstream& ifile) {
	if (!ifile.is_open())
		return false; // Can't open file

	std::map<std::pair<unsigned short int, unsigned short int>, unsigned short int> edgeList;

	// Read number of vertices |V|
	unsigned long long int numVertices;
	if (ifile >> numVertices) {
		if (numVertices > GRAPH_INIT_NUM_VERTICES_MAX || ifile.fail() || ifile.bad()) {
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
	unsigned long long int vertex1, vertex2, weight;
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

		// Weight must be > 0, <= USHRT_MAX
		// Vertex must be between 0 and numVertices
		if (weight == 0 || weight > USHRT_MAX || vertex1 < 0 || vertex1 >= numVertices || vertex2 < 0 || vertex2 >= numVertices
			|| ifile.fail() || ifile.bad()) {
			ifile.clear(); // Cleanup
			ifile.seekg(0, std::ios::beg);
			return false;
		}

		// Edges must be valid
		// Check if edge already exists
		if (edgeList.count(std::make_pair(vertex1, vertex2))) {
			ifile.clear(); // Cleanup
			ifile.seekg(0, std::ios::beg);
			return false;
		}
		edgeList[std::make_pair(vertex1, vertex2)] = weight;
		edgeList[std::make_pair(vertex2, vertex1)] = weight;
		// if (!edgeList.count(std::make_pair(vertexIdx, vertexTo)))  {
		// }
	}

	// bool isValidEdgeList = isPerfectSquare(inputCount);
	// Valid if reached EOF
	bool isValid = read && ifile.eof();

	ifile.clear(); // Cleanup
	ifile.seekg(0, std::ios::beg);
	return isValid; // Valid if reached EOF
}





bool GraphReader::validDataEdgeListString(std::string& data) {
	std::string trimmedData = trim(data);
	std::istringstream iss(trimmedData);

	std::map<std::pair<unsigned short int, unsigned short int>, unsigned short int> edgeList;
	
	// Read number of vertices |V|
	unsigned long long int numVertices;
	if (iss >> numVertices) {
		if (numVertices > GRAPH_INIT_NUM_VERTICES_MAX || iss.fail() || iss.bad()) {
			return false;
		}
	} else {
		return false;
	}

	// Read each edge
	unsigned long long int vertex1, vertex2, weight;
	bool read = false;
	// unsigned int inputCount = 0;

	while (iss >> vertex1 >> vertex2 >> weight) {
		read = true;
		// inputCount++;
		// if (inputCount > GRAPH_INIT_NUM_VERTICES_MAX * GRAPH_INIT_NUM_VERTICES_MAX) {
		// 	return false;
		// }

		// Weight must be > 0, <= USHRT_MAX
		// Vertex must be between 0 and numVertices
		if (weight == 0 || weight > USHRT_MAX || vertex1 < 0 || vertex1 >= numVertices || vertex2 < 0 || vertex2 >= numVertices
			|| iss.fail() || iss.bad()) {
			return false;
		}

		// Edges must be valid
		// Check if edge already exists
		if (edgeList.count(std::make_pair(vertex1, vertex2))) {
			return false;
		}
		edgeList[std::make_pair(vertex1, vertex2)] = weight;
		edgeList[std::make_pair(vertex2, vertex1)] = weight;
		// if (!edgeList.count(std::make_pair(vertexIdx, vertexTo)))  {
		// }
	}

	// bool isValidEdgeList = isPerfectSquare(inputCount);
	// Valid if reached EOF
	return read && iss.eof();
}





std::vector<GraphReader::GraphEdge> GraphReader::getDataEdgeListFile(std::ifstream& ifile, unsigned int& numVertices) {
	if (!ifile.is_open()) return {};
	if (!validDataEdgeListFile(ifile)) return {};

	std::vector<GraphReader::GraphEdge> edges;

	// Read number of vertices |V|
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





std::vector<GraphReader::GraphEdge> GraphReader::getDataEdgeListString(std::string& data, unsigned int& numVertices) {
	if (!validDataEdgeListString(data)) return {};

	std::string trimmedData = trim(data);
	std::istringstream iss(trimmedData);

	std::vector<GraphReader::GraphEdge> edges;

	// Read number of vertices |V|
	iss >> numVertices;

	// Read each edge
	unsigned short int vertex1, vertex2, weight;
	while (iss >> vertex1 >> vertex2 >> weight) {
		edges.push_back(GraphReader::GraphEdge(vertex1, vertex2, weight));
	}

	return edges;
}
