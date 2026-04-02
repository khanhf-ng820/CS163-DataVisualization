#include "Trie/LogicTrieNode.h"



LogicTrieNode::LogicTrieNode() {}

LogicTrieNode::LogicTrieNode(uint64_t id, char key)
	: id(id), key(key), children(TRIE_ALPHABET_SIZE, nullptr)
{}

LogicTrieNode::LogicTrieNode(uint64_t id, char key, bool isEndOfWord)
	: id(id), key(key), children(TRIE_ALPHABET_SIZE, nullptr)
	, isEndOfWord(isEndOfWord)
{}

LogicTrieNode::LogicTrieNode(const LogicTrieNode*& node)
	: children(TRIE_ALPHABET_SIZE, nullptr)
{
	id = node->getID();
	key = node->key;
	isEndOfWord = node->isEndOfWord;
}

uint64_t LogicTrieNode::getID() const {
	return id;
}



LogicTrieNode*& LogicTrieNode::getChild(char linkChar) {
	assert('a' <= linkChar && linkChar <= 'z');
	return children[linkChar - 'a'];
}

bool LogicTrieNode::isLeaf() {
	for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
		if (children[i]) return false;
	}
	return true;
}
