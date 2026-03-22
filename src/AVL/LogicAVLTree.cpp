#include "AVL/LogicAVLTree.h"



LogicAVLTree::LogicAVLTree() {
	///// EXAMPLE TREE
	///// ONLY FOR TESTING, WILL DELETE LATER
	LogicAVLNode* left = new LogicAVLNode(18);
	LogicAVLNode* rightright = new LogicAVLNode(69);
	LogicAVLNode* right = new LogicAVLNode(67, nullptr, rightright);
	// LogicAVLNode* right = new LogicAVLNode(67);
	root = new LogicAVLNode(36, left, right);
}

LogicAVLTree::~LogicAVLTree() {
	clear(root);
	root = nullptr;
}

LogicAVLTree::LogicAVLTree(const LogicAVLTree& other)
	: root(nullptr)
{
	if (!other.root) return;
	root = copyTree(other.root);
}

LogicAVLTree& LogicAVLTree::operator=(const LogicAVLTree& other) {
	if (this != &other) {
		LogicAVLTree tempTree(other);
		std::swap(root, tempTree.root);
	}
	return *this;
}



unsigned int LogicAVLTree::getSize() {
	return getSize(root);
}







void LogicAVLTree::clear(LogicAVLNode*& node) {
	if (!node) return;
	clear(node->left);
	clear(node->right);
	delete node;
	node = nullptr;
}

unsigned int LogicAVLTree::getSize(LogicAVLNode* node) {
	if (!node) return 0;
	return getSize(node->left) + 1U + getSize(node->right);
}

LogicAVLNode* LogicAVLTree::copyTree(const LogicAVLNode* node) {
	if (!node) return nullptr;
	LogicAVLNode* copyNode = new LogicAVLNode(node->key);
	copyNode->left = copyTree(node->left);
	copyNode->right = copyTree(node->right);
	copyNode->height = node->height;
	return copyNode;
}
