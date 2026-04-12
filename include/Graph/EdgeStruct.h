#pragma once




// Struct for an edge
struct Edge {
	int to;
	int weight;

	Edge() : to(0), weight(0) {}
	Edge(int toVal, int weightVal) : to(toVal), weight(weightVal) {}

	bool operator<(const Edge& other) const {
		if (weight != other.weight) return weight < other.weight;
		return to < other.to;
	}
	bool operator>(const Edge& other) const {
		if (weight != other.weight) return weight > other.weight;
		return to > other.to;
	}
};
