#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// #include "Graph/const.h"
#include <iostream>
#include <string>
#include <vector>





class LogicGraphVertexDijkstra {
public:
	LogicGraphVertexDijkstra();
	explicit LogicGraphVertexDijkstra(int id);
	LogicGraphVertexDijkstra(int id, int cost, int prevVertex);
	LogicGraphVertexDijkstra(const LogicGraphVertexDijkstra& v) = default;

	LogicGraphVertexDijkstra& operator=(const LogicGraphVertexDijkstra& other) = default; // Copy assignment operator


	int getID() const;

	int cost = INT_MAX;  // Best cheapest cost to the start vertex
	int prevVertex = -1; // Previous vertex in the shortest path
	bool visited = false;

	// Compare cheapest costs
	bool operator<(const LogicGraphVertexDijkstra& other) const;
	bool operator>(const LogicGraphVertexDijkstra& other) const;

private:
	int id = 0; // Unique ID of a node
};
