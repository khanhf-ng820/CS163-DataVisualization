#include "Graph/MSTPrim/LogicGraphVertexPrim.h"




LogicGraphVertexPrim::LogicGraphVertexPrim() {}

LogicGraphVertexPrim::LogicGraphVertexPrim(int id)
	: id(id)
{}

LogicGraphVertexPrim::LogicGraphVertexPrim(int id, int cost, int parentVertex)
	: id(id), cost(cost), parentVertex(parentVertex)
{}

LogicGraphVertexPrim::LogicGraphVertexPrim(const LogicGraphVertexPrim& v)
	: id(v.getID()), cost(v.cost), parentVertex(v.parentVertex)
	, visited(v.visited), highlightMSTEdge(v.highlightMSTEdge)
{}



int LogicGraphVertexPrim::getID() const {
	return id;
}



// Compare cheapest costs/weights
bool LogicGraphVertexPrim::operator<(const LogicGraphVertexPrim& other) const {
	return cost < other.cost;
}

bool LogicGraphVertexPrim::operator>(const LogicGraphVertexPrim& other) const {
	return cost > other.cost;
}
