#include "AVL/LogicAVLNode.h"




LogicAVLNode::LogicAVLNode() {}

LogicAVLNode::LogicAVLNode(int key)
	: key(key), height(1)
{}

LogicAVLNode::LogicAVLNode(int key, LogicAVLNode* left, LogicAVLNode* right)
	: key(key), height(1U + std::max(getHeight(left), getHeight(right)))
	, left(left), right(right)
{}
