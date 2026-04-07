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
	LogicGraphVertexDijkstra(int id, int dist, int prevVertex);
	explicit LogicGraphVertexDijkstra(const LogicGraphVertexDijkstra& v);

	int getID() const;

	int dist = 0;  // Best distance to start vertex
	int prevVertex = -1; // Previous vertex in the shortest path

private:
	int id = 0; // Unique ID of a node
};
