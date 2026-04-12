#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// #include "Graph/const.h"
#include <iostream>
#include <string>
#include <vector>





class VisualGraphVertex {
public:
	VisualGraphVertex();
	explicit VisualGraphVertex(int id);
	VisualGraphVertex(int id, sf::Vector2f position);

	int getID() const;

	sf::Vector2f position = {0, 0};
	sf::Vector2f displacement = {0, 0};
	sf::Vector2f force = {0, 0};

private:
	int id = 0; // Unique ID of a visual vertex
};
