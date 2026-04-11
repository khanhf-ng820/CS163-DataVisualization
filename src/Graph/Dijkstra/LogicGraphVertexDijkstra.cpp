#include "Graph/Dijkstra/LogicGraphVertexDijkstra.h"




LogicGraphVertexDijkstra::LogicGraphVertexDijkstra() {}

LogicGraphVertexDijkstra::LogicGraphVertexDijkstra(int id)
	: id(id)
{}

LogicGraphVertexDijkstra::LogicGraphVertexDijkstra(int id, int cost, int prevVertex)
	: id(id), cost(cost), prevVertex(prevVertex)
{}

LogicGraphVertexDijkstra::LogicGraphVertexDijkstra(const LogicGraphVertexDijkstra& v)
	: id(v.getID()), cost(v.cost), prevVertex(v.prevVertex), visited(v.visited)
{}



int LogicGraphVertexDijkstra::getID() const {
	return id;
}



// Compare costs
bool LogicGraphVertexDijkstra::operator<(const LogicGraphVertexDijkstra& other) const {
	return cost > other.cost;
}
