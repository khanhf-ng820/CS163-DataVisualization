#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <vector>



class VisualAVLNode {
public:
	VisualAVLNode();
	VisualAVLNode(int key, unsigned int height);
	VisualAVLNode(int key, unsigned int height, sf::Vector2f position);
	VisualAVLNode(int key, unsigned int height, unsigned int oldHeight);
	VisualAVLNode(int key, unsigned int height, unsigned int oldHeight, sf::Vector2f position);

	int key = -1;
	unsigned int height = 0;
	unsigned int oldHeight = 0;
	sf::Vector2f position = {0, 0};

	// For deletion
	// When a node gets assigned key of minimum successor
	bool hasSecondPos = false;
	sf::Vector2f secondPos = {0, 0};
	void setSecondPos(sf::Vector2f secPos);
};
