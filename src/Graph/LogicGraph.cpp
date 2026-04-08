#include "Graph/LogicGraph.h"




LogicGraph::LogicGraph(unsigned int numVertex)
	: numVertex(numVertex)
	, adjList(numVertex, std::vector<Edge>())
	// , visualVertices(numVertex)
{
	// for (int i = 0; i < adjList.size(); i++) {
	// 	visualVertices[i] = VisualGraphVertex(i);
	// }
}

LogicGraph::LogicGraph(std::vector<std::vector<Edge>>& adjList)
	: numVertex(adjList.size())
	, adjList(adjList)
	// , visualVertices(adjList.size())
{
	// for (int i = 0; i < adjList.size(); i++) {
	// 	visualVertices[i] = VisualGraphVertex(i);
	// }
}





// Get number of nodes (O(1))
unsigned int LogicGraph::getNumVertex() const {
	return numVertex;
}
