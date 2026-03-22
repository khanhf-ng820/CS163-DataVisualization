#pragma once
#include "AVL/LogicAVLNode.h"
#include "AVL/VisualAVLNode.h"
#include "AVL/AVLAnimStep.h"





///// Event (animation step) generator
class LogicAVLTree {
public:
	LogicAVLTree();
	~LogicAVLTree();
	LogicAVLTree(const LogicAVLTree& other); // Copy constructor

	LogicAVLTree& operator=(const LogicAVLTree& other); // assignment op
	unsigned int getSize();


	LogicAVLNode* root = nullptr;

private:
	void clear(LogicAVLNode*& node);

	// Helper functions
	unsigned int getSize(LogicAVLNode* node);
	LogicAVLNode* copyTree(const LogicAVLNode* node);
};
