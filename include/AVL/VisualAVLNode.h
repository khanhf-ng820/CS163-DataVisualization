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
	explicit VisualAVLNode(int key);
	VisualAVLNode(int key, sf::Vector2f position);

	int key = -1;
	sf::Vector2f position = {0, 0};
};
