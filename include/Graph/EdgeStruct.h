#pragma once




// Struct for an edge
struct Edge {
	int to;
	int weight;

	Edge() : to(0), weight(0) {}
	Edge(int toVal, int weightVal) : to(toVal), weight(weightVal) {}
};
