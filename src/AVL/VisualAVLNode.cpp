#include "AVL/VisualAVLNode.h"



VisualAVLNode::VisualAVLNode() {}

VisualAVLNode::VisualAVLNode(int key)
	: key(key)
{}

VisualAVLNode::VisualAVLNode(int key, sf::Vector2f position)
	: key(key), position(position)
{}
