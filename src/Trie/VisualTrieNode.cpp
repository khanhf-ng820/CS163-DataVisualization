#include "Trie/VisualTrieNode.h"



VisualTrieNode::VisualTrieNode() {}

VisualTrieNode::VisualTrieNode(uint64_t id, char key)
	: id(id), key(key)
{}

VisualTrieNode::VisualTrieNode(uint64_t id, char key, sf::Vector2f position)
	: id(id), key(key), position(position)
{}



uint64_t VisualTrieNode::getID() const {
	return id;
}
