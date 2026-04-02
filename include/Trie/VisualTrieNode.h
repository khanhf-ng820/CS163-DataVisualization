#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Trie/const.h"
#include <iostream>
#include <string>
#include <vector>



class VisualTrieNode {
public:
	VisualTrieNode();
	explicit VisualTrieNode(uint64_t id, char key);
	VisualTrieNode(uint64_t id, char key, sf::Vector2f position);

	uint64_t getID() const;
	char key = 'a';
	sf::Vector2f position = {0, 0};

private:
	uint64_t id = 0; // Unique ID of a visual node
};
