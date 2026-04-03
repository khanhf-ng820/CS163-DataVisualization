#include "Trie/VisualTrieNode.h"



VisualTrieNode::VisualTrieNode() {}

VisualTrieNode::VisualTrieNode(uint64_t id, char key, bool isEndOfWord)
	: id(id), key(key), isEndOfWord(isEndOfWord)
{}

VisualTrieNode::VisualTrieNode(uint64_t id, char key, bool isEndOfWord, sf::Vector2f position)
	: id(id), key(key), isEndOfWord(isEndOfWord), position(position)
{}



uint64_t VisualTrieNode::getID() const {
	return id;
}
