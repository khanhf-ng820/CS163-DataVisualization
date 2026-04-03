#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Trie/const.h"
#include <iostream>
#include <string>
#include <vector>





class LogicTrieNode {
public:
	LogicTrieNode();
	LogicTrieNode(uint64_t id, char key);
	LogicTrieNode(uint64_t id, char key, bool isEndOfWord);
	explicit LogicTrieNode(const LogicTrieNode*& node);

	uint64_t getID() const;
	char key = 'a';
	bool isEndOfWord = false;
	std::vector<LogicTrieNode*> children;

	LogicTrieNode*& getChild(char linkChar);
	bool isLeaf();

private:
	uint64_t id = 0; // Unique ID of a node
};



/// Helper functions
