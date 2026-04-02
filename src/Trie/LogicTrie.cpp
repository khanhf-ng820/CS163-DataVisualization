#include "Trie/LogicTrie.h"



LogicTrie::LogicTrie() {
	///// EXAMPLE TREE
	///// ONLY FOR TESTING, WILL DELETE LATER
	root = nullptr;

	root = newNode('a');
	root->getChild('p') = newNode('p');
	root->getChild('p')->getChild('p') = newNode('p');
	root->getChild('p')->getChild('t') = newNode('t');
}

LogicTrie::~LogicTrie() {
	clear(root);
	root = nullptr;
}

LogicTrie::LogicTrie(const LogicTrie& other)
	: root(nullptr)
{
	if (!other.root) return;
	root = copyTree(other.root);
}

LogicTrie& LogicTrie::operator=(const LogicTrie& other) {
	if (this != &other) {
		LogicTrie tempTree(other);
		std::swap(root, tempTree.root);
	}
	return *this;
}



LogicTrieNode* LogicTrie::newNode(char c) {
	return new LogicTrieNode(currentNodeID++, c);
}

unsigned int LogicTrie::getSize() {
	return getSizeHelper(root);
}

unsigned int LogicTrie::countLeaf() {
	unsigned int totalCnt = 0;
	countLeafHelper(root, totalCnt);
	return totalCnt;
}

// // Get node, knowing the key
// LogicTrieNode* LogicTrie::getNodeKey(int key) {
// 	return getNodeKeyHelper(key, root);
// }

// // Print inorder
// void LogicTrie::inorderPrint() {
// 	inorderPrintHelper(root);
// }

// // Find min successor node
// LogicTrieNode* LogicTrie::minSuccNode(LogicTrieNode* node, int deleteKey,
// 	std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots) {
// 	return node ? minValueNode(node->right, deleteKey, events, treeSnapshots) : nullptr;
// }







// ///// ANIMATION EVENTS
// // Remind to snapshot tree after insertion/rotation
// void LogicTrie::snapshotTree(int key, std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots) {
// 	if (snapshotTreeReminder) {
// 		treeSnapshots.push_back(*this);
// 		if (animTypeReminder == TrieAnimType::INSERT_NODE)
// 			events.push_back(TrieAnimStep(animTypeReminder, descriptionReminder, {}, key, treeSnapshots.size() - 1));
// 		else
// 			events.push_back(TrieAnimStepOldTreeIndex(animTypeReminder, descriptionReminder, {}, treeSnapshots.size() - 1));
// 		clearSnapshotReminder();
// 	}
// }


// LogicTrieNode* LogicTrie::leftRotate(LogicTrieNode*& node, std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots) {
// 	LogicTrieNode* rightChild = node->right;
// 	LogicTrieNode* rightleftChild = rightChild->left;
// 	rightChild->left = node;
// 	node->right = rightleftChild;
// 	setHeight(node);
// 	setHeight(rightChild);
// 	// treeSnapshots.push_back(*this);
// 	return rightChild;
// }

// LogicTrieNode* LogicTrie::rightRotate(LogicTrieNode*& node, std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots) {
// 	LogicTrieNode* leftChild = node->left;
// 	LogicTrieNode* leftrightChild = leftChild->right;
// 	leftChild->right = node;
// 	node->left = leftrightChild;
// 	setHeight(node);
// 	setHeight(leftChild);
// 	// treeSnapshots.push_back(*this);
// 	return leftChild;
// }



// // -- INSERTION --
// LogicTrieNode* LogicTrie::generateInsertEvents(LogicTrieNode*& node, int key, std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots) {
// 	if (!node) {
// 		// events.push_back(TrieAnimStep(TrieAnimType::INSERT_NODE, "Found null subtree, insert node " + std::to_string(key), {}, key, treeSnapshots.size() - 1));
// 		std::cerr << "INSERTED NEW NODE" << std::endl; // DEBUG
// 		setSnapshotReminder(TrieAnimType::INSERT_NODE, "Found null subtree, insert node " + std::to_string(key));
// 		return new LogicTrieNode(key);
// 	}

// 	short int heavySide = 0; // Heavy side (left/right)
// 	if (key < node->key) {
// 		heavySide = -1;
// 		events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE, "Checking node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
// 		events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_LEFT_DOWN, "Looking at left subtree of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
// 		node->left = generateInsertEvents(node->left, key, events, treeSnapshots);
// 	} else if (key > node->key) {
// 		heavySide = 1;
// 		events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE, "Checking node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
// 		events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_RIGHT_DOWN, "Looking at right subtree of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
// 		node->right = generateInsertEvents(node->right, key, events, treeSnapshots);
// 	}
// 	// Remind to snapshot tree after rotation
// 	snapshotTree(key, events, treeSnapshots);
// 	assert(heavySide != 0);

// 	// Update the balance factor and balance the tree
// 	setHeight(node);
// 	if (heavySide == -1) {
// 		events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_LEFT_UP, "Unwinding recursion", {}, node->key, treeSnapshots.size() - 1));
// 	} else if (heavySide == 1) {
// 		events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_RIGHT_UP, "Unwinding recursion", {}, node->key, treeSnapshots.size() - 1));
// 	}
// 	treeSnapshots.push_back(*this);
// 	events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE_UPDATE_HEIGHT, "Update height of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));

// 	// Unwinding recursion, balancing the tree
// 	int balance = getBalance(node);
// 	// Rotation when unbalanced
// 	// Left Left
// 	if (balance > 1 && getBalance(node->left) >= 0) {
// 		LogicTrieNode* rotatedRoot = rightRotate(node, events, treeSnapshots);
// 		setSnapshotReminder(TrieAnimType::ROTATE_RIGHT_LL, "Single Rotate Right (LL)");
// 		return rotatedRoot;
// 	}
// 	// Right Right
// 	if (balance < -1 && getBalance(node->right) <= 0) {
// 		LogicTrieNode* rotatedRoot = leftRotate(node, events, treeSnapshots);
// 		setSnapshotReminder(TrieAnimType::ROTATE_LEFT_RR, "Single Rotate Left (RR)");
// 		return rotatedRoot;
// 	}
// 	// Left Right
// 	if (balance > 1 && getBalance(node->left) < 0) {
// 		node->left = leftRotate(node->left, events, treeSnapshots);
// 		treeSnapshots.push_back(*this);
// 		events.push_back(TrieAnimStepOldTreeIndex(TrieAnimType::ROTATE_LEFT_LR, "Double Rotate (LR), rotate left", {}, treeSnapshots.size() - 1));
		
// 		LogicTrieNode* rotatedRoot = rightRotate(node, events, treeSnapshots);
// 		setSnapshotReminder(TrieAnimType::ROTATE_RIGHT_LR, "Double Rotate (LR), rotate right");
// 		return rotatedRoot;
// 	}
// 	// Right Left
// 	if (balance < -1 && getBalance(node->right) > 0) {
// 		node->right = rightRotate(node->right, events, treeSnapshots);
// 		treeSnapshots.push_back(*this);
// 		events.push_back(TrieAnimStepOldTreeIndex(TrieAnimType::ROTATE_RIGHT_RL, "Double Rotate (RL), rotate right", {}, treeSnapshots.size() - 1));

// 		LogicTrieNode* rotatedRoot = leftRotate(node, events, treeSnapshots);
// 		setSnapshotReminder(TrieAnimType::ROTATE_LEFT_RL, "Double Rotate (RL), rotate left");
// 		return rotatedRoot;
// 	}
// 	return node;
// }



// // -- DELETION --
// LogicTrieNode* LogicTrie::generateDeleteEvents(LogicTrieNode*& node, int key, std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots) {
// 	if (!node) {
// 		events.push_back(TrieAnimStep(TrieAnimType::NONE, "Found null subtree", {}, key, treeSnapshots.size() - 1));
// 		return node;
// 	}

// 	short int heavySide = 0; // Heavy side (left/right)
// 	if (key < node->key) {
// 		heavySide = -1;
// 		events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE, "Checking node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
// 		events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_LEFT_DOWN, "Looking at left subtree of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
// 		node->left = generateDeleteEvents(node->left, key, events, treeSnapshots);
// 	} else if (key > node->key) {
// 		heavySide = 1;
// 		events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE, "Checking node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
// 		events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_RIGHT_DOWN, "Looking at right subtree of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
// 		node->right = generateDeleteEvents(node->right, key, events, treeSnapshots);
// 	} else {
// 		events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE, "Found node " + std::to_string(key), {}, key, treeSnapshots.size() - 1));

// 		if (node->left == nullptr) {
// 			LogicTrieNode* temp = node->right;
// 			node = nullptr;

// 			if (temp == nullptr) {
// 				setSnapshotReminder(TrieAnimType::DELETE_LEAF_NODE, "Delete the leaf node");
// 			} else {
// 				setSnapshotReminder(TrieAnimType::DELETE_NODE_ONE_CHILD, "Delete the node with one child");
// 			}
// 			return temp;
// 		} else if (node->right == nullptr) {
// 			LogicTrieNode* temp = node->left;
// 			node = nullptr;

// 			setSnapshotReminder(TrieAnimType::DELETE_NODE_ONE_CHILD, "Delete the node with one child");
// 			return temp;
// 		}

// 		events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_RIGHT_DOWN, "Looking at right subtree of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
// 		LogicTrieNode* temp = minValueNode(node->right, key, events, treeSnapshots);

// 		treeSnapshots.push_back(*this);
// 		events.push_back(TrieAnimStep(TrieAnimType::COPY_KEY_FROM_MIN_SUCC, "Copy the minimum successor into node to delete", {}, temp->key, treeSnapshots.size() - 1));
// 		node->key = temp->key;
// 		minSuccKey = temp->key; // Minimum successor key placeholder

// 		// events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE, "Checking node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
// 		// events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_RIGHT_DOWN, "Looking at right subtree of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
// 		events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE, "Checking node " + std::to_string(node->key), {}, key, treeSnapshots.size() - 1));
// 		events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_RIGHT_DOWN, "Looking at right subtree of node " + std::to_string(node->key), {}, key, treeSnapshots.size() - 1));
// 		node->right = generateDeleteEvents(node->right, temp->key, events, treeSnapshots);
// 	}

// 	// Remind to snapshot tree after rotation
// 	snapshotTree(key, events, treeSnapshots);

// 	// If deletion removed the node completely, stop
// 	if (node == nullptr) {
// 		return node;
// 	}

// 	// Update the balance factor and balance the tree
// 	int balance = getBalance(node);
// 	if (heavySide == -1) {
// 		events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_LEFT_UP, "Unwinding recursion", {}, node->key, treeSnapshots.size() - 1));
// 	} else if (heavySide == 1) {
// 		events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_RIGHT_UP, "Unwinding recursion", {}, node->key, treeSnapshots.size() - 1));
// 	} else {
// 		// Moving up right subtree because we want minimum successor
// 		events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_RIGHT_UP, "Unwinding recursion", {}, node->key, treeSnapshots.size() - 1));
// 	}
// 	node->height = 1U + std::max(getHeight(node->left), getHeight(node->right));
// 	treeSnapshots.push_back(*this);
// 	events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE_UPDATE_HEIGHT, "Update height of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));

// 	// Rotation when unbalanced
// 	// Left Left
// 	if (balance > 1 && getBalance(node->left) >= 0) {
// 		LogicTrieNode* rotatedRoot = rightRotate(node, events, treeSnapshots);
// 		setSnapshotReminder(TrieAnimType::ROTATE_RIGHT_LL, "Single Rotate Right (LL)");
// 		return rotatedRoot;
// 	}
// 	// Right Right
// 	if (balance < -1 && getBalance(node->right) <= 0) {
// 		LogicTrieNode* rotatedRoot = leftRotate(node, events, treeSnapshots);
// 		setSnapshotReminder(TrieAnimType::ROTATE_LEFT_RR, "Single Rotate Left (RR)");
// 		return rotatedRoot;
// 	}
// 	// Left Right
// 	if (balance > 1 && getBalance(node->left) < 0) {
// 		node->left = leftRotate(node->left, events, treeSnapshots);
// 		treeSnapshots.push_back(*this);
// 		events.push_back(TrieAnimStepOldTreeIndex(TrieAnimType::ROTATE_LEFT_LR, "Double Rotate (LR), rotate left", {}, treeSnapshots.size() - 1));
		
// 		LogicTrieNode* rotatedRoot = rightRotate(node, events, treeSnapshots);
// 		setSnapshotReminder(TrieAnimType::ROTATE_RIGHT_LR, "Double Rotate (LR), rotate right");
// 		return rotatedRoot;
// 	}
// 	// Right Left
// 	if (balance < -1 && getBalance(node->right) > 0) {
// 		node->right = rightRotate(node->right, events, treeSnapshots);
// 		treeSnapshots.push_back(*this);
// 		events.push_back(TrieAnimStepOldTreeIndex(TrieAnimType::ROTATE_RIGHT_RL, "Double Rotate (RL), rotate right", {}, treeSnapshots.size() - 1));

// 		LogicTrieNode* rotatedRoot = leftRotate(node, events, treeSnapshots);
// 		setSnapshotReminder(TrieAnimType::ROTATE_LEFT_RL, "Double Rotate (RL), rotate left");
// 		return rotatedRoot;
// 	}

// 	return node;
// }











///// Private methods
void LogicTrie::clear(LogicTrieNode*& node) {
	if (!node) return;
	for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
		clear(node->children[i]);
	}
	delete node;
	node = nullptr;
}


// void LogicTrie::setSnapshotReminder(TrieAnimType animType, std::string desc) {
// 	snapshotTreeReminder = true;
// 	animTypeReminder = animType;
// 	descriptionReminder = desc;
// }
// void LogicTrie::clearSnapshotReminder() {
// 	snapshotTreeReminder = false;
// 	animTypeReminder = TrieAnimType::NONE;
// 	descriptionReminder = "";
// }



LogicTrieNode* LogicTrie::copyTree(const LogicTrieNode* node) {
	if (!node) return nullptr;
	LogicTrieNode* copyNode = new LogicTrieNode(node);
	for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
		copyNode->children[i] = copyTree(node->children[i]);
	}
	return copyNode;
}

unsigned int LogicTrie::getSizeHelper(LogicTrieNode* node) {
	if (!node) return 0;
	unsigned int totalSize = 1U;
	for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
		totalSize += getSizeHelper(node->children[i]);
	}
	return totalSize;
}

void LogicTrie::countLeafHelper(LogicTrieNode* node, unsigned int& totalCnt) {
	if (!node) return;
	bool isLeaf = true;
	for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
		if (node->children[i]) {
			isLeaf = false;
			countLeafHelper(node->children[i], totalCnt);
		}
	}
	if (isLeaf) totalCnt++;
}

// // Get node, knowing the key
// LogicTrieNode* LogicTrie::getNodeKeyHelper(int key, LogicTrieNode* node) {
// 	if (!node) return nullptr;
// 	if (node->key > key) {
// 		return getNodeKeyHelper(key, node->left);
// 	} else if (node->key < key) {
// 		return getNodeKeyHelper(key, node->right);
// 	} else return node;
// }

// // Print inorder
// void LogicTrie::inorderPrintHelper(LogicTrieNode* node) {
// 	if (!node) return;
// 	inorderPrintHelper(node->left);
// 	std::cout << node->key << " ";
// 	inorderPrintHelper(node->right);
// }

// // Get minimum node of subtree
// LogicTrieNode* LogicTrie::minValueNode(LogicTrieNode* node, int deleteKey, std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots) {
// 	LogicTrieNode* cur = node;
// 	events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE, "Finding the leftmost node of right subtree of node " + std::to_string(deleteKey), {}, cur->key, treeSnapshots.size() - 1));
// 	while (cur && cur->left) {
// 		LogicTrieNode* oldCur = cur;
// 		cur = cur->left;
// 		if (cur)
// 			events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_LEFT_DOWN, "Finding the leftmost node of right subtree of node " + std::to_string(deleteKey), {}, oldCur->key, treeSnapshots.size() - 1));
// 	}
// 	return cur;
// }
