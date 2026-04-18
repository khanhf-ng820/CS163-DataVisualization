#include "Graph/LogicGraph.h"




LogicGraph::LogicGraph(unsigned int numVertex)
	: numVertex(numVertex)
	, adjList(numVertex, std::vector<Edge>())
{
	// for (int i = 0; i < adjList.size(); i++) {
	// }
}


LogicGraph::LogicGraph(std::mt19937& rng) {
	std::uniform_int_distribution<int> numVertexDistrib(GRAPH_INIT_RANDOM_NUM_VERTICES_MIN, GRAPH_INIT_RANDOM_NUM_VERTICES_MAX);
	
	numVertex = numVertexDistrib(rng);
	adjList = std::vector<std::vector<Edge>>(numVertex, std::vector<Edge>());

	std::uniform_real_distribution<float> weightProbThresholdDistrib(1.f / numVertex, 0.5f);
	std::uniform_real_distribution<float> weightProbDistrib(0.f, 1.f);
	std::uniform_int_distribution<int> weightDistrib(GRAPH_INIT_WEIGHT_MIN, GRAPH_INIT_WEIGHT_MAX);

	float weightProbThreshold = weightProbThresholdDistrib(rng);

	// Erdos-Renyi Model
	for (int i = 0; i < numVertex; i++) {
		for (int j = i+1; j < numVertex; j++) {
			if (weightProbDistrib(rng) < weightProbThreshold) {
				int randWeight = weightDistrib(rng);
				adjList[i].push_back(Edge(j, randWeight));
				adjList[j].push_back(Edge(i, randWeight));
			}
		}
	}
}


LogicGraph::LogicGraph(std::vector<std::vector<int>>& adjMatrix) {
	numVertex = adjMatrix.size();
	adjList = std::vector<std::vector<Edge>>(numVertex, std::vector<Edge>());

	for (int i = 0; i < numVertex; i++) {
		for (int j = i+1; j < numVertex; j++) {
			if (adjMatrix[i][j] > 0) {
				adjList[i].push_back(Edge(j, adjMatrix[i][j]));
				adjList[j].push_back(Edge(i, adjMatrix[i][j]));
			}
		}
	}
}


LogicGraph::LogicGraph(std::vector<std::vector<Edge>>& adjList)
	: numVertex(adjList.size())
	, adjList(adjList)
{}


LogicGraph::LogicGraph(unsigned int numVertex, std::vector<GraphReader::GraphEdge>& edgeList)
	: LogicGraph(numVertex)
{
	for (const auto& graphEdge : edgeList) {
		int i = graphEdge.vertexFrom, j = graphEdge.vertexTo, w = graphEdge.weight;
		if (w > 0) {
			adjList[i].push_back(Edge(j, w));
			adjList[j].push_back(Edge(i, w));
		}
	}
}





// Get number of nodes (O(1))
unsigned int LogicGraph::getNumVertex() const {
	return numVertex;
}

// Print adjacency list
void LogicGraph::printAdjList() const {
	for (int i = 0; i < numVertex; i++) {
		std::cerr << i << ": ";
		for (const auto& [to, weight] : adjList[i]) {
			std::cerr << to << ' ' << weight << ", ";
		}
		std::cerr << std::endl;
	}
}
