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
	VisualTrieNode(uint64_t id, char key, bool isEndOfWord);
	VisualTrieNode(uint64_t id, char key, bool isEndOfWord, sf::Vector2f position);

	uint64_t getID() const;
	char key = 'a';
	bool isEndOfWord = false;

	sf::Vector2f position = {0, 0};

private:
	uint64_t id = 0; // Unique ID of a visual node
};
