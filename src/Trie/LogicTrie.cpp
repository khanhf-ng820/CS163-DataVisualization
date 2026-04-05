#include "Trie/LogicTrie.h"



LogicTrie::LogicTrie() {
	///// EXAMPLE TREE
	///// ONLY FOR TESTING, WILL DELETE LATER
	// root = newNode('-');

	// Inserts 'apt', 'apps', 'apple'
	root = newNode('-');
	// root->getChild('a') = newNode('a');
	// root->getChild('a')->getChild('p') = newNode('p');
	// root->getChild('a')->getChild('p')->getChild('p') = newNode('p');
	// root->getChild('a')->getChild('p')->getChild('t') = newNode('t', true);
	// root->getChild('a')->getChild('p')->getChild('p')->getChild('s') = newNode('s', true);
	// root->getChild('a')->getChild('p')->getChild('p')->getChild('l') = newNode('l');
	// root->getChild('a')->getChild('p')->getChild('p')->getChild('l')->getChild('e') = newNode('e', true);
}

LogicTrie::~LogicTrie() {
	clear(root);
}

LogicTrie::LogicTrie(const LogicTrie& other)
	: root(nullptr), currentNodeID(other.currentNodeID)
{
	if (!other.root) return;
	root = copyTree(other.root);
}

LogicTrie& LogicTrie::operator=(const LogicTrie& other) {
	if (this != &other) {
		LogicTrie tempTree(other);
		std::swap(root, tempTree.root);
		std::swap(currentNodeID, tempTree.currentNodeID);
	}
	return *this;
}



LogicTrieNode* LogicTrie::newNode(char c) {
	return new LogicTrieNode(currentNodeID++, c);
}

LogicTrieNode* LogicTrie::newNode(char c, bool isEndOfWord) {
	return new LogicTrieNode(currentNodeID++, c, isEndOfWord);
}


unsigned int LogicTrie::getSize() {
	return getSizeHelper(root);
}

unsigned int LogicTrie::countLeaf() {
	unsigned int totalCnt = 0;
	countLeafHelper(root, totalCnt);
	return totalCnt;
}

// Get node, knowing the ID
LogicTrieNode* LogicTrie::getNodeID(uint64_t ID) {
	return getNodeIDHelper(ID, root);
}

// Check if word exists (plain version of generateSearchEvents)
bool LogicTrie::wordExists(std::string word) {
	LogicTrieNode* node = root;

	for (const char& c : word) {
		if (node->getChild(c) == nullptr) {
			return false;
		}

		node = node->getChild(c);
	}

	return node->isEndOfWord;
}

// Insert a word to init data (plain version of generateInsertEvents)
void LogicTrie::insertWord(std::string word) {
	LogicTrieNode* node = root;

	for (const char& c : word) {
		if (node->getChild(c) == nullptr) {
			node->getChild(c) = newNode(c);
		}

		node = node->getChild(c);
	}

	node->isEndOfWord = true;
}







///// ANIMATION EVENTS /////
// Remind to snapshot tree after each insertion/rotation
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

// -- SEARCHING --
bool LogicTrie::generateSearchEvents(std::string word, std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots) {
	LogicTrieNode* node = root;
	events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE, "Looking at root node", {}, root->getID()));

	for (const char& c : word) {
		if (node->getChild(c) == nullptr) {
			events.push_back(TrieAnimStep(TrieAnimType::NONE, "Child \'" + std::string(1, c) + "\' does not exist. Word does not exist.", {}, node->getID()));
			return false;
		}

		if (node != root) {
			events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE, "Looking at node \'" + std::string(1, node->key) + "\'", {}, node->getID()));
		}
		events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_DOWN, "Going down to \'" + std::string(1, c) + "\' child", {}, node->getID()));
		events.back().charLink = c;

		node = node->getChild(c);
	}

	if (node->isEndOfWord) {
		events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_FOUND_NODE, "Found node \'" + std::string(1, node->key) + "\', reached end of string, isEndOfWord is true. Word found.", {}, node->getID()));
	} else {
		events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE, "Found node \'" + std::string(1, node->key) + "\', reached end of string, isEndOfWord is false. Word does not exist.", {}, node->getID()));
	}

	return node->isEndOfWord;
}





// -- INSERTION --
LogicTrieNode* LogicTrie::generateInsertEvents(std::string word, std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots) {
	LogicTrieNode* node = root;
	events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE, "Looking at root node", {}, root->getID(), treeSnapshots.size() - 1));

	for (const char& c : word) {
		if (node->getChild(c) == nullptr) {
			std::string eventDescription = "Child \'" + std::string(1, c) + "\' does not exist. Creating child \'" + std::string(1, c) + "\'";
			events.push_back(TrieAnimStep(TrieAnimType::NONE, eventDescription, {}, node->getID(), treeSnapshots.size() - 1));

			node->getChild(c) = newNode(c);

			treeSnapshots.push_back(*this);
			events.push_back(TrieAnimStep(TrieAnimType::INSERT_NODE, eventDescription, {}, node->getChild(c)->getID(), treeSnapshots.size() - 1));
		}

		if (node != root) {
			events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE, "Looking at node \'" + std::string(1, node->key) + "\'", {}, node->getID(), treeSnapshots.size() - 1));
		}
		events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_DOWN, "Going down to \'" + std::string(1, c) + "\' child", {}, node->getID(), treeSnapshots.size() - 1));
		events.back().charLink = c;

		node = node->getChild(c);
	}

	node->isEndOfWord = true;

	treeSnapshots.push_back(*this);
	events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_FOUND_NODE, "Set isEndOfWord of node \'" + std::string(1, node->key) + "\' to true", {}, node->getID(), treeSnapshots.size() - 1));

	return node;
}





// -- DELETION --
void LogicTrie::generateDeleteEvents(std::string word, std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots) {
	deleteSuccessful = false;
	events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE, "Looking at root node", {}, root->getID(), treeSnapshots.size() -1));

	// Delete node into tree and get animation events
	root = generateDeleteEventsHelper(root, word, 0, events, treeSnapshots);
	// // Remind to snapshot tree after deletion/rotation
	// snapshotTree(word, events, treeSnapshots);

	if (deleteSuccessful) {
		events.push_back(TrieAnimStep(TrieAnimType::NONE, "Finished deleting word: \"" + word + "\"", {}, 0, treeSnapshots.size() -1));
	} else {
		events.push_back(TrieAnimStep(TrieAnimType::NONE, "Word \"" + word + "\" does not exist, nothing to delete.", {}, 0, treeSnapshots.size() -1));
	}
}


LogicTrieNode* LogicTrie::generateDeleteEventsHelper(LogicTrieNode*& node, std::string word, int depth, std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots) {
	if (!node) {
		events.push_back(TrieAnimStep(TrieAnimType::NONE, "Found null node", {}, 0, treeSnapshots.size() - 1));
		return nullptr;
	}

	if (depth == word.size()) {
		if (node->isEndOfWord) deleteSuccessful = true;

		node->isEndOfWord = false;

		if (deleteSuccessful) {
			treeSnapshots.push_back(*this);
			events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_FOUND_NODE, "Set isEndOfWord of node \'" + std::string(1, node->key) + "\' to false", {}, node->getID(), treeSnapshots.size() - 1));
		} else {
			events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_FOUND_NODE, "isEndOfWord of node \'" + std::string(1, node->key) + "\' is false", {}, node->getID(), treeSnapshots.size() - 1));
		}

		if (node != root && node->isLeaf()) {
			events.push_back(TrieAnimStep(TrieAnimType::DELETE_LEAF_NODE, "Delete leaf node \'" + std::string(1, node->key) + "\'", {}, node->getID(), treeSnapshots.size()));

			delete node;
			node = nullptr;

			treeSnapshots.push_back(*this);
		}

		return node;
	}

	if (node != root) {
		events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_NODE, "Looking at node \'" + std::string(1, node->key) + "\'", {}, node->getID(), treeSnapshots.size() - 1));
	}
	events.push_back(TrieAnimStep(TrieAnimType::MOVE_HIGHLIGHT_DOWN, "Going down to \'" + std::string(1, word[depth]) + "\' child", {}, node->getID(), treeSnapshots.size() - 1));
	events.back().charLink = word[depth];

	node->getChild(word[depth]) = generateDeleteEventsHelper(node->getChild(word[depth]), word, depth + 1, events, treeSnapshots);

	if (node != root && node->isLeaf() && !node->isEndOfWord) {
		events.push_back(TrieAnimStep(TrieAnimType::DELETE_LEAF_NODE, "Delete leaf node \'" + std::string(1, node->key) + "\'", {}, node->getID(), treeSnapshots.size()));

		delete node;
		node = nullptr;

		treeSnapshots.push_back(*this);
	}

	return node;
}











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

// Get node, knowing the ID
LogicTrieNode* LogicTrie::getNodeIDHelper(uint64_t ID, LogicTrieNode* node) {
	if (!node) return nullptr;
	if (node->getID() == ID) return node;
	for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
		LogicTrieNode* result = getNodeIDHelper(ID, node->children[i]);
		if (result) return result;
	}
	return nullptr;
}
