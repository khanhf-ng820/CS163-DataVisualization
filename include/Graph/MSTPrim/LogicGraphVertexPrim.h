#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// #include "Graph/const.h"
#include <iostream>
#include <string>
#include <vector>





class LogicGraphVertexPrim {
public:
	LogicGraphVertexPrim();
	explicit LogicGraphVertexPrim(int id);
	LogicGraphVertexPrim(int id, int cost, int parentVertex);
	LogicGraphVertexPrim(const LogicGraphVertexPrim& v) = default;

	LogicGraphVertexPrim& operator=(const LogicGraphVertexPrim&) = default; // Copy assignment operator


	int getID() const;

	int cost = INT_MAX;  // Cheapest cost/weight of the minimum weight edge
	int parentVertex = -1; // Parent vertex in the MST
	bool visited = false; // To keep track of vertices included in MST

	// Whether engine should highlight edge in MST when drawing
	bool highlightMSTEdge = false;

	// Compare cheapest costs/weights
	bool operator<(const LogicGraphVertexPrim& other) const;
	bool operator>(const LogicGraphVertexPrim& other) const;

private:
	int id = 0; // Unique ID of a node
};
