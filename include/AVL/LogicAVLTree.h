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

	LogicAVLNode* root = nullptr;


	unsigned int getSize(); // Get size of tree (not O(1))
	// Get node, knowing the key
	LogicAVLNode* getNodeKey(int key);
	// Print inorder
	void inorderPrint();
	// Find min successor node
	LogicAVLNode* minSuccNode(LogicAVLNode* node);


	bool snapshotTreeReminder = false; // Snapshot after rotation
	AVLAnimType animTypeReminder = AVLAnimType::NONE;
	std::string descriptionReminder = "";
	// Remind to snapshot tree after insertion/rotation
	void snapshotTree(int key, std::vector<AVLAnimStep>& events, std::vector<LogicAVLTree>& treeSnapshots);


	///// ANIMATION EVENTS
	// Returns copy of the whole tree
	LogicAVLNode* leftRotate(LogicAVLNode*& node, 
		std::vector<AVLAnimStep>& events, std::vector<LogicAVLTree>& treeSnapshots);
	LogicAVLNode* rightRotate(LogicAVLNode*& node, 
		std::vector<AVLAnimStep>& events, std::vector<LogicAVLTree>& treeSnapshots);
	LogicAVLNode* generateInsertEvents(LogicAVLNode*& node, int key, 
		std::vector<AVLAnimStep>& events, std::vector<LogicAVLTree>& treeSnapshots);


private:
	void clear(LogicAVLNode*& node);

	// Helper functions for animation events generation
	void setSnapshotReminder(AVLAnimType animType, std::string desc);
	void clearSnapshotReminder();


	///// Helper functions (other)
	LogicAVLNode* copyTree(const LogicAVLNode* node); // Return copy of tree

	unsigned int getSizeHelper(LogicAVLNode* node);
	// Get node, knowing the key
	LogicAVLNode* getNodeKeyHelper(int key, LogicAVLNode* node);
	// Print inorder
	void inorderPrintHelper(LogicAVLNode* node);
	// Get minimum node of subtree
	LogicAVLNode* minValueNode(LogicAVLNode* node);
};
