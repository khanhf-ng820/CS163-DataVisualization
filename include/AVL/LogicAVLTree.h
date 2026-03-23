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


	LogicAVLNode* getNodeKey(int key); // Get node knowing key

private:
	void clear(LogicAVLNode*& node);

	// Helper functions
	LogicAVLNode* copyTree(const LogicAVLNode* node); // Return copy of tree
	unsigned int getSize(LogicAVLNode* node);
	LogicAVLNode* getNodeKey(int key, LogicAVLNode* node); // Get node knowing key
};
