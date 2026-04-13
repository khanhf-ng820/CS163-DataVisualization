#include "utils/readData/GraphReader/readAdjMatrix.h"





bool GraphReader::validDataAdjMatFile(std::ifstream& ifile) {
	if (!ifile.is_open())
		return false; // Can't open file

	unsigned short int weight;
	bool read = false;
	unsigned int inputCount = 0;

	while (ifile >> weight) {
		read = true; // Successfully read an int
		inputCount++;
		if (inputCount > GRAPH_INIT_NUM_VERTICES_MAX * GRAPH_INIT_NUM_VERTICES_MAX) {
			ifile.clear(); // Cleanup
			ifile.seekg(0, std::ios::beg);
			return false;
		}
	}

	bool isValidAdjMatrix = isPerfectSquare(inputCount);
	bool isValid = read && ifile.eof() && isValidAdjMatrix;

	ifile.clear(); // Cleanup
	ifile.seekg(0, std::ios::beg);
	return isValid; // Valid if reached EOF
}





bool GraphReader::validDataAdjMatString(std::string& data) {
	std::string trimmedData = trim(data);
	std::istringstream iss(trimmedData);

	unsigned short int weight;
	bool read = false;
	unsigned int inputCount = 0;

	while (iss >> weight) {
		read = true;
		inputCount++;
		if (inputCount > GRAPH_INIT_NUM_VERTICES_MAX * GRAPH_INIT_NUM_VERTICES_MAX) {
			return false;
		}
	}

	bool isValidAdjMatrix = isPerfectSquare(inputCount);
	return read && iss.eof() && isValidAdjMatrix;
}





std::vector<std::vector<int>> GraphReader::getDataAdjMatFile(std::ifstream& ifile) {
	if (!ifile.is_open()) return {};
	if (!validDataAdjMatFile(ifile)) return {};

	std::vector<int> weights;
	unsigned short int weight;
	unsigned int numVerticesSquared = 0;

	while (ifile >> weight) {
		numVerticesSquared++;
		weights.push_back(weight);
	}

	unsigned int numVertices = perfectSquareRoot(numVerticesSquared);
	std::vector<std::vector<int>> adjMat(numVertices, std::vector<int>(numVertices, 0));

	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			adjMat[i][j] = weights[i * numVertices + j];
		}
	}

	ifile.clear(); // Cleanup
	ifile.seekg(0, std::ios::beg);
	return adjMat;
}





std::vector<std::vector<int>> GraphReader::getDataAdjMatString(std::string& data) {
	if (!validDataAdjMatString(data)) return {};

	std::string trimmedData = trim(data);
	std::istringstream iss(trimmedData);

	std::vector<int> weights;
	unsigned short int weight;
	unsigned int numVerticesSquared = 0;

	while (iss >> weight) {
		numVerticesSquared++;
		weights.push_back(weight);
	}

	unsigned int numVertices = perfectSquareRoot(numVerticesSquared);
	std::vector<std::vector<int>> adjMat(numVertices, std::vector<int>(numVertices, 0));

	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			adjMat[i][j] = weights[i * numVertices + j];
		}
	}

	return adjMat;
}
