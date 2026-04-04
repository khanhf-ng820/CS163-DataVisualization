#include "AVL/LogicAVLTree.h"



LogicAVLTree::LogicAVLTree() {
	///// EXAMPLE TREE
	///// ONLY FOR TESTING, WILL DELETE LATER
	root = nullptr;

	// LogicAVLNode* leftright = new LogicAVLNode(18);
	// LogicAVLNode* left = new LogicAVLNode(16, nullptr, leftright);
	// LogicAVLNode* rightright = new LogicAVLNode(69);
	// LogicAVLNode* right = new LogicAVLNode(67, nullptr, rightright);
	// root = new LogicAVLNode(36, left, right);
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
	return getSizeHelper(root);
}

// Get node, knowing the key
LogicAVLNode* LogicAVLTree::getNodeKey(int key) {
	return getNodeKeyHelper(key, root);
}

// Print inorder
void LogicAVLTree::inorderPrint() {
	inorderPrintHelper(root);
}

// Find min successor node
LogicAVLNode* LogicAVLTree::minSuccNode(LogicAVLNode* node, int deleteKey,
	std::vector<AVLAnimStep>& events, std::vector<LogicAVLTree>& treeSnapshots) {
	return node ? minValueNode(node->right, deleteKey, events, treeSnapshots) : nullptr;
}










///// ANIMATION EVENTS
// Remind to snapshot tree after insertion/rotation
void LogicAVLTree::snapshotTree(int key, std::vector<AVLAnimStep>& events, std::vector<LogicAVLTree>& treeSnapshots) {
	if (snapshotTreeReminder) {
		treeSnapshots.push_back(*this);
		if (animTypeReminder == AVLAnimType::INSERT_NODE)
			events.push_back(AVLAnimStep(animTypeReminder, descriptionReminder, {}, key, treeSnapshots.size() - 1));
		else
			events.push_back(AVLAnimStepOldTreeIndex(animTypeReminder, descriptionReminder, {}, treeSnapshots.size() - 1));
		clearSnapshotReminder();
	}
}


LogicAVLNode* LogicAVLTree::leftRotate(LogicAVLNode*& node, std::vector<AVLAnimStep>& events, std::vector<LogicAVLTree>& treeSnapshots) {
	LogicAVLNode* rightChild = node->right;
	LogicAVLNode* rightleftChild = rightChild->left;
	rightChild->left = node;
	node->right = rightleftChild;
	setHeight(node);
	setHeight(rightChild);
	// treeSnapshots.push_back(*this);
	return rightChild;
}

LogicAVLNode* LogicAVLTree::rightRotate(LogicAVLNode*& node, std::vector<AVLAnimStep>& events, std::vector<LogicAVLTree>& treeSnapshots) {
	LogicAVLNode* leftChild = node->left;
	LogicAVLNode* leftrightChild = leftChild->right;
	leftChild->right = node;
	node->left = leftrightChild;
	setHeight(node);
	setHeight(leftChild);
	// treeSnapshots.push_back(*this);
	return leftChild;
}





// -- INSERTION --
LogicAVLNode* LogicAVLTree::generateInsertEvents(LogicAVLNode*& node, int key, std::vector<AVLAnimStep>& events, std::vector<LogicAVLTree>& treeSnapshots) {
	if (!node) {
		// events.push_back(AVLAnimStep(AVLAnimType::INSERT_NODE, "Found null subtree, insert node " + std::to_string(key), {}, key, treeSnapshots.size() - 1));
		std::cerr << "INSERTED NEW NODE" << std::endl; // DEBUG
		setSnapshotReminder(AVLAnimType::INSERT_NODE, "Found null subtree, insert node " + std::to_string(key));
		return new LogicAVLNode(key);
	}

	short int heavySide = 0; // Heavy side (left/right)
	if (key < node->key) {
		heavySide = -1;
		events.push_back(AVLAnimStep(AVLAnimType::HIGHLIGHT_NODE, "Checking node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
		events.push_back(AVLAnimStep(AVLAnimType::MOVE_HIGHLIGHT_LEFT_DOWN, "Looking at left subtree of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
		node->left = generateInsertEvents(node->left, key, events, treeSnapshots);
	} else if (key > node->key) {
		heavySide = 1;
		events.push_back(AVLAnimStep(AVLAnimType::HIGHLIGHT_NODE, "Checking node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
		events.push_back(AVLAnimStep(AVLAnimType::MOVE_HIGHLIGHT_RIGHT_DOWN, "Looking at right subtree of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
		node->right = generateInsertEvents(node->right, key, events, treeSnapshots);
	}
	// Remind to snapshot tree after rotation
	snapshotTree(key, events, treeSnapshots);
	assert(heavySide != 0);

	// Update the balance factor and balance the tree
	setHeight(node);
	if (heavySide == -1) {
		events.push_back(AVLAnimStep(AVLAnimType::MOVE_HIGHLIGHT_LEFT_UP, "Unwinding recursion", {}, node->key, treeSnapshots.size() - 1));
	} else if (heavySide == 1) {
		events.push_back(AVLAnimStep(AVLAnimType::MOVE_HIGHLIGHT_RIGHT_UP, "Unwinding recursion", {}, node->key, treeSnapshots.size() - 1));
	}
	treeSnapshots.push_back(*this);
	events.push_back(AVLAnimStep(AVLAnimType::HIGHLIGHT_NODE_UPDATE_HEIGHT, "Update height of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));

	// Unwinding recursion, balancing the tree
	int balance = getBalance(node);
	// Rotation when unbalanced
	// Left Left
	if (balance > 1 && getBalance(node->left) >= 0) {
		LogicAVLNode* rotatedRoot = rightRotate(node, events, treeSnapshots);
		setSnapshotReminder(AVLAnimType::ROTATE_RIGHT_LL, "Single Rotate Right (LL)");
		return rotatedRoot;
	}
	// Right Right
	if (balance < -1 && getBalance(node->right) <= 0) {
		LogicAVLNode* rotatedRoot = leftRotate(node, events, treeSnapshots);
		setSnapshotReminder(AVLAnimType::ROTATE_LEFT_RR, "Single Rotate Left (RR)");
		return rotatedRoot;
	}
	// Left Right
	if (balance > 1 && getBalance(node->left) < 0) {
		node->left = leftRotate(node->left, events, treeSnapshots);
		treeSnapshots.push_back(*this);
		events.push_back(AVLAnimStepOldTreeIndex(AVLAnimType::ROTATE_LEFT_LR, "Double Rotate (LR), rotate left", {}, treeSnapshots.size() - 1));
		
		LogicAVLNode* rotatedRoot = rightRotate(node, events, treeSnapshots);
		setSnapshotReminder(AVLAnimType::ROTATE_RIGHT_LR, "Double Rotate (LR), rotate right");
		return rotatedRoot;
	}
	// Right Left
	if (balance < -1 && getBalance(node->right) > 0) {
		node->right = rightRotate(node->right, events, treeSnapshots);
		treeSnapshots.push_back(*this);
		events.push_back(AVLAnimStepOldTreeIndex(AVLAnimType::ROTATE_RIGHT_RL, "Double Rotate (RL), rotate right", {}, treeSnapshots.size() - 1));

		LogicAVLNode* rotatedRoot = leftRotate(node, events, treeSnapshots);
		setSnapshotReminder(AVLAnimType::ROTATE_LEFT_RL, "Double Rotate (RL), rotate left");
		return rotatedRoot;
	}
	return node;
}





// -- DELETION --
LogicAVLNode* LogicAVLTree::generateDeleteEvents(LogicAVLNode*& node, int key, std::vector<AVLAnimStep>& events, std::vector<LogicAVLTree>& treeSnapshots) {
	if (!node) {
		events.push_back(AVLAnimStep(AVLAnimType::NONE, "Found null subtree", {}, key, treeSnapshots.size() - 1));
		return node;
	}

	short int heavySide = 0; // Heavy side (left/right)
	if (key < node->key) {
		heavySide = -1;
		events.push_back(AVLAnimStep(AVLAnimType::HIGHLIGHT_NODE, "Checking node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
		events.push_back(AVLAnimStep(AVLAnimType::MOVE_HIGHLIGHT_LEFT_DOWN, "Looking at left subtree of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
		node->left = generateDeleteEvents(node->left, key, events, treeSnapshots);
	} else if (key > node->key) {
		heavySide = 1;
		events.push_back(AVLAnimStep(AVLAnimType::HIGHLIGHT_NODE, "Checking node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
		events.push_back(AVLAnimStep(AVLAnimType::MOVE_HIGHLIGHT_RIGHT_DOWN, "Looking at right subtree of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
		node->right = generateDeleteEvents(node->right, key, events, treeSnapshots);
	} else {
		events.push_back(AVLAnimStep(AVLAnimType::HIGHLIGHT_NODE, "Found node " + std::to_string(key), {}, key, treeSnapshots.size() - 1));

		if (node->left == nullptr) {
			LogicAVLNode* temp = node->right;
			node = nullptr;

			if (temp == nullptr) {
				setSnapshotReminder(AVLAnimType::DELETE_LEAF_NODE, "Delete the leaf node");
			} else {
				setSnapshotReminder(AVLAnimType::DELETE_NODE_ONE_CHILD, "Delete the node with one child");
			}
			return temp;
		} else if (node->right == nullptr) {
			LogicAVLNode* temp = node->left;
			node = nullptr;

			setSnapshotReminder(AVLAnimType::DELETE_NODE_ONE_CHILD, "Delete the node with one child");
			return temp;
		}

		events.push_back(AVLAnimStep(AVLAnimType::MOVE_HIGHLIGHT_RIGHT_DOWN, "Looking at right subtree of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
		LogicAVLNode* temp = minValueNode(node->right, key, events, treeSnapshots);

		treeSnapshots.push_back(*this);
		events.push_back(AVLAnimStep(AVLAnimType::COPY_KEY_FROM_MIN_SUCC, "Copy the minimum successor into node to delete", {}, temp->key, treeSnapshots.size() - 1));
		node->key = temp->key;
		minSuccKey = temp->key; // Minimum successor key placeholder

		// events.push_back(AVLAnimStep(AVLAnimType::HIGHLIGHT_NODE, "Checking node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
		// events.push_back(AVLAnimStep(AVLAnimType::MOVE_HIGHLIGHT_RIGHT_DOWN, "Looking at right subtree of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));
		events.push_back(AVLAnimStep(AVLAnimType::HIGHLIGHT_NODE, "Checking node " + std::to_string(node->key), {}, key, treeSnapshots.size() - 1));
		events.push_back(AVLAnimStep(AVLAnimType::MOVE_HIGHLIGHT_RIGHT_DOWN, "Looking at right subtree of node " + std::to_string(node->key), {}, key, treeSnapshots.size() - 1));
		node->right = generateDeleteEvents(node->right, temp->key, events, treeSnapshots);
	}

	// Remind to snapshot tree after rotation
	snapshotTree(key, events, treeSnapshots);

	// If deletion removed the node completely, stop
	if (node == nullptr) {
		return node;
	}

	// Update the balance factor and balance the tree
	int balance = getBalance(node);
	if (heavySide == -1) {
		events.push_back(AVLAnimStep(AVLAnimType::MOVE_HIGHLIGHT_LEFT_UP, "Unwinding recursion", {}, node->key, treeSnapshots.size() - 1));
	} else if (heavySide == 1) {
		events.push_back(AVLAnimStep(AVLAnimType::MOVE_HIGHLIGHT_RIGHT_UP, "Unwinding recursion", {}, node->key, treeSnapshots.size() - 1));
	} else {
		// Moving up right subtree because we want minimum successor
		events.push_back(AVLAnimStep(AVLAnimType::MOVE_HIGHLIGHT_RIGHT_UP, "Unwinding recursion", {}, node->key, treeSnapshots.size() - 1));
	}
	node->height = 1U + std::max(getHeight(node->left), getHeight(node->right));
	treeSnapshots.push_back(*this);
	events.push_back(AVLAnimStep(AVLAnimType::HIGHLIGHT_NODE_UPDATE_HEIGHT, "Update height of node " + std::to_string(node->key), {}, node->key, treeSnapshots.size() - 1));

	// Rotation when unbalanced
	// Left Left
	if (balance > 1 && getBalance(node->left) >= 0) {
		LogicAVLNode* rotatedRoot = rightRotate(node, events, treeSnapshots);
		setSnapshotReminder(AVLAnimType::ROTATE_RIGHT_LL, "Single Rotate Right (LL)");
		return rotatedRoot;
	}
	// Right Right
	if (balance < -1 && getBalance(node->right) <= 0) {
		LogicAVLNode* rotatedRoot = leftRotate(node, events, treeSnapshots);
		setSnapshotReminder(AVLAnimType::ROTATE_LEFT_RR, "Single Rotate Left (RR)");
		return rotatedRoot;
	}
	// Left Right
	if (balance > 1 && getBalance(node->left) < 0) {
		node->left = leftRotate(node->left, events, treeSnapshots);
		treeSnapshots.push_back(*this);
		events.push_back(AVLAnimStepOldTreeIndex(AVLAnimType::ROTATE_LEFT_LR, "Double Rotate (LR), rotate left", {}, treeSnapshots.size() - 1));
		
		LogicAVLNode* rotatedRoot = rightRotate(node, events, treeSnapshots);
		setSnapshotReminder(AVLAnimType::ROTATE_RIGHT_LR, "Double Rotate (LR), rotate right");
		return rotatedRoot;
	}
	// Right Left
	if (balance < -1 && getBalance(node->right) > 0) {
		node->right = rightRotate(node->right, events, treeSnapshots);
		treeSnapshots.push_back(*this);
		events.push_back(AVLAnimStepOldTreeIndex(AVLAnimType::ROTATE_RIGHT_RL, "Double Rotate (RL), rotate right", {}, treeSnapshots.size() - 1));

		LogicAVLNode* rotatedRoot = leftRotate(node, events, treeSnapshots);
		setSnapshotReminder(AVLAnimType::ROTATE_LEFT_RL, "Double Rotate (RL), rotate left");
		return rotatedRoot;
	}

	return node;
}











///// Private methods
void LogicAVLTree::clear(LogicAVLNode*& node) {
	if (!node) return;
	clear(node->left);
	clear(node->right);
	delete node;
	node = nullptr;
}


void LogicAVLTree::setSnapshotReminder(AVLAnimType animType, std::string desc) {
	snapshotTreeReminder = true;
	animTypeReminder = animType;
	descriptionReminder = desc;
}
void LogicAVLTree::clearSnapshotReminder() {
	snapshotTreeReminder = false;
	animTypeReminder = AVLAnimType::NONE;
	descriptionReminder = "";
}



LogicAVLNode* LogicAVLTree::copyTree(const LogicAVLNode* node) {
	if (!node) return nullptr;
	LogicAVLNode* copyNode = new LogicAVLNode(node->key);
	copyNode->left = copyTree(node->left);
	copyNode->right = copyTree(node->right);
	copyNode->height = node->height;
	return copyNode;
}

unsigned int LogicAVLTree::getSizeHelper(LogicAVLNode* node) {
	if (!node) return 0;
	return getSizeHelper(node->left) + 1U + getSizeHelper(node->right);
}

// Get node, knowing the key
LogicAVLNode* LogicAVLTree::getNodeKeyHelper(int key, LogicAVLNode* node) {
	if (!node) return nullptr;
	if (node->key > key) {
		return getNodeKeyHelper(key, node->left);
	} else if (node->key < key) {
		return getNodeKeyHelper(key, node->right);
	} else return node;
}

// Print inorder
void LogicAVLTree::inorderPrintHelper(LogicAVLNode* node) {
	if (!node) return;
	inorderPrintHelper(node->left);
	std::cout << node->key << " ";
	inorderPrintHelper(node->right);
}

// Get minimum node of subtree
LogicAVLNode* LogicAVLTree::minValueNode(LogicAVLNode* node, int deleteKey, std::vector<AVLAnimStep>& events, std::vector<LogicAVLTree>& treeSnapshots) {
	LogicAVLNode* cur = node;
	events.push_back(AVLAnimStep(AVLAnimType::HIGHLIGHT_NODE, "Finding the leftmost node of right subtree of node " + std::to_string(deleteKey), {}, cur->key, treeSnapshots.size() - 1));
	while (cur && cur->left) {
		LogicAVLNode* oldCur = cur;
		cur = cur->left;
		if (cur)
			events.push_back(AVLAnimStep(AVLAnimType::MOVE_HIGHLIGHT_LEFT_DOWN, "Finding the leftmost node of right subtree of node " + std::to_string(deleteKey), {}, oldCur->key, treeSnapshots.size() - 1));
	}
	return cur;
}
