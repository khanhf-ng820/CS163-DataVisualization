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
	void inorderPrint();


	bool snapshotTreeReminder = false; // Snapshot after rotation
	AVLAnimType animTypeReminder = AVLAnimType::NONE;
	std::string descriptionReminder = "";


	///// ANIMATION EVENTS
	// Returns copy of the whole tree
	LogicAVLNode* leftRotate(LogicAVLNode*& node, 
		std::vector<AVLAnimStep>& events, std::vector<LogicAVLTree>& treeSnapshots);
	LogicAVLNode* rightRotate(LogicAVLNode*& node, 
		std::vector<AVLAnimStep>& events, std::vector<LogicAVLTree>& treeSnapshots);
	LogicAVLNode* insertEvents(LogicAVLNode*& node, int key, 
		std::vector<AVLAnimStep>& events, std::vector<LogicAVLTree>& treeSnapshots);

private:
	void clear(LogicAVLNode*& node);

	// Helper functions for animation events generation
	void setSnapshotReminder(AVLAnimType animType, std::string desc);
	void clearSnapshotReminder();


	///// Helper functions (other)
	LogicAVLNode* copyTree(const LogicAVLNode* node); // Return copy of tree

	unsigned int getSizeHelper(LogicAVLNode* node);
	LogicAVLNode* getNodeKeyHelper(int key, LogicAVLNode* node); // Get node knowing key
	void inorderPrintHelper(LogicAVLNode* node);
};
