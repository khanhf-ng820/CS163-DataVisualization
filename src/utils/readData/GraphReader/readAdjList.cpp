#include "utils/readData/GraphReader/readAdjList.h"





bool GraphReader::validDataAdjListFile(std::ifstream& ifile) {
	if (!ifile.is_open())
		return false; // Can't open file

	std::map<std::pair<unsigned short int, unsigned short int>, unsigned short int> edgeList;

	std::string line;
	unsigned short int numVertices;
	bool doneReadNumVertices = false;
	bool read = false;
	unsigned short int vertexIdx = 0; // Current vertex index

	while (std::getline(ifile, line)) {
		std::istringstream iss(line);

		// Read number of vertices |V|
		if (!doneReadNumVertices) {
			if (iss >> numVertices) {
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
			doneReadNumVertices = true;
			read = true;
		} else {
		// Read edges (vertexTo, weight)
			unsigned short int vertexTo, weight;

			// reads whitespace-separated numbers
			while (iss >> vertexTo >> weight) {
				read = true;

				// Weight must be > 0, vertex must be between 0 and numVertices
				if (weight == 0 || vertexTo < 0 || vertexTo >= numVertices) {
					ifile.clear(); // Cleanup
					ifile.seekg(0, std::ios::beg);
					return false;
				}

				// Edges must be valid
				edgeList[std::make_pair(vertexIdx, vertexTo)] = weight;
				// if (!edgeList.count(std::make_pair(vertexIdx, vertexTo)))  {
				// }
			}

			vertexIdx++;
		}
	}

	// Valid if reached EOF
	bool isValid = read && ifile.eof();

	ifile.clear(); // Cleanup
	ifile.seekg(0, std::ios::beg);
	if (!isValid) return isValid;

	// Edges must be valid, must have reversed edge with the same weight
	for (const auto& [vertexPair, weight] : edgeList) {
		std::pair<unsigned short int, unsigned short int> reversedPair = std::make_pair(vertexPair.second, vertexPair.first);
		// Must have symmetry (have reversed edge and same weight)
		if (!edgeList.count(reversedPair)) return false;
		if (edgeList[reversedPair] != weight) return false;
	}
	return true;
}





bool GraphReader::validDataAdjListString(std::string& data) {
	std::string trimmedData = trim(data);
	std::istringstream dataStream(trimmedData);

	std::map<std::pair<unsigned short int, unsigned short int>, unsigned short int> edgeList;

	std::string line;
	unsigned short int numVertices;
	bool doneReadNumVertices = false;
	bool read = false;
	unsigned short int vertexIdx = 0; // Current vertex index

	while (std::getline(dataStream, line)) {
		std::istringstream iss(line);

		// Read number of vertices |V|
		if (!doneReadNumVertices) {
			if (iss >> numVertices) {
				if (numVertices > GRAPH_INIT_NUM_VERTICES_MAX) {
					return false;
				}
			} else {
				return false;
			}
			doneReadNumVertices = true;
			read = true;
		} else {
		// Read edges (vertexTo, weight)
			unsigned short int vertexTo, weight;

			// reads whitespace-separated numbers
			while (iss >> vertexTo >> weight) {
				read = true;

				// Weight must be > 0, vertex must be between 0 and numVertices
				if (weight == 0 || vertexTo < 0 || vertexTo >= numVertices) {
					return false;
				}

				// Edges must be valid
				edgeList[std::make_pair(vertexIdx, vertexTo)] = weight;
				// if (!edgeList.count(std::make_pair(vertexIdx, vertexTo)))  {
				// }
			}

			vertexIdx++;
		}
	}

	// Valid if reached EOF
	bool isValid = read && dataStream.eof();

	if (!isValid) return isValid;

	// Edges must be valid, must have reversed edge with the same weight
	for (const auto& [vertexPair, weight] : edgeList) {
		std::pair<unsigned short int, unsigned short int> reversedPair = std::make_pair(vertexPair.second, vertexPair.first);
		// Must have symmetry (have reversed edge and same weight)
		if (!edgeList.count(reversedPair)) return false;
		if (edgeList[reversedPair] != weight) return false;
	}
	return true;
}





std::vector<std::vector<Edge>> GraphReader::getDataAdjListFile(std::ifstream& ifile) {
	if (!ifile.is_open()) return {};
	if (!validDataAdjListFile(ifile)) return {};

	unsigned short int numVertices;
	std::vector<std::vector<Edge>> adjList;

	std::string line;
	bool doneReadNumVertices = false;
	unsigned short int vertexIdx = 0;

	while (std::getline(ifile, line)) {
		std::istringstream iss(line);

		// Read number of vertices |V|
		if (!doneReadNumVertices) {
			iss >> numVertices;
			adjList = std::vector<std::vector<Edge>>(numVertices, std::vector<Edge>());

			doneReadNumVertices = true;
		} else {
		// Read edges (vertexTo, weight)
			unsigned short int vertexTo, weight;

			// reads whitespace-separated numbers
			while (iss >> vertexTo >> weight) {
				adjList[vertexIdx].push_back(Edge(vertexTo, weight));
			}

			vertexIdx++;
		}
	}

	ifile.clear(); // Cleanup
	ifile.seekg(0, std::ios::beg);
	return adjList;
}





std::vector<std::vector<Edge>> GraphReader::getDataAdjListString(std::string& data) {
	if (!validDataAdjListString(data)) return {};

	std::string trimmedData = trim(data);
	std::istringstream dataStream(trimmedData);

	unsigned short int numVertices;
	std::vector<std::vector<Edge>> adjList;

	std::string line;
	bool doneReadNumVertices = false;
	unsigned short int vertexIdx = 0;

	while (std::getline(dataStream, line)) {
		std::istringstream iss(line);

		// Read number of vertices |V|
		if (!doneReadNumVertices) {
			iss >> numVertices;
			adjList = std::vector<std::vector<Edge>>(numVertices, std::vector<Edge>());

			doneReadNumVertices = true;
		} else {
		// Read edges (vertexTo, weight)
			unsigned short int vertexTo, weight;

			// reads whitespace-separated numbers
			while (iss >> vertexTo >> weight) {
				adjList[vertexIdx].push_back(Edge(vertexTo, weight));
			}

			vertexIdx++;
		}
	}

	return adjList;
}
