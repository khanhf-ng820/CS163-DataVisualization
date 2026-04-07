#include "Graph/Dijkstra/LogicGraphVertexDijkstra.h"




LogicGraphVertexDijkstra::LogicGraphVertexDijkstra() {}

LogicGraphVertexDijkstra::LogicGraphVertexDijkstra(int id)
	: id(id)
{}

LogicGraphVertexDijkstra::LogicGraphVertexDijkstra(int id, int dist, int prevVertex)
	: id(id), dist(dist), prevVertex(prevVertex)
{}

LogicGraphVertexDijkstra::LogicGraphVertexDijkstra(const LogicGraphVertexDijkstra& v)
	: id(v.getID()), dist(v.dist), prevVertex(v.prevVertex)
{}



int LogicGraphVertexDijkstra::getID() const {
	return id;
}
