#include "AVL/VisualAVLNode.h"



VisualAVLNode::VisualAVLNode() {}

VisualAVLNode::VisualAVLNode(int key, unsigned int height)
	: key(key), height(height)
{}

VisualAVLNode::VisualAVLNode(int key, unsigned int height, sf::Vector2f position)
	: key(key), height(height), position(position)
{}

VisualAVLNode::VisualAVLNode(int key, unsigned int height, unsigned int oldHeight)
	: key(key), height(height), oldHeight(oldHeight)
{}

VisualAVLNode::VisualAVLNode(int key, unsigned int height, unsigned int oldHeight, sf::Vector2f position)
	: key(key), height(height), oldHeight(oldHeight), position(position)
{}



void VisualAVLNode::setSecondPos(sf::Vector2f secPos) {
	hasSecondPos = true;
	secondPos = secPos;
}
