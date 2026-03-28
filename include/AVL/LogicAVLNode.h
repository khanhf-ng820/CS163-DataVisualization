#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <vector>





class LogicAVLNode {
public:
	LogicAVLNode();
	explicit LogicAVLNode(int key);
	LogicAVLNode(int key, LogicAVLNode* left, LogicAVLNode* right);

	int key = -1; // Also acts as ID of a node
	unsigned int height = 0;
	LogicAVLNode* left  = nullptr;
	LogicAVLNode* right = nullptr;
};



/// Helper functions
inline const unsigned int getHeight(LogicAVLNode* node) {
	if (!node) return 0;
	return node->height;
}

inline const unsigned int setHeight(LogicAVLNode* node) {
	if (!node) return 0;
	node->height = 1U + std::max(getHeight(node->left), getHeight(node->right));
	return node->height;
}

inline const int getBalance(LogicAVLNode* node) {
	if (!node) return 0;
	return getHeight(node->left) - getHeight(node->right);
}
