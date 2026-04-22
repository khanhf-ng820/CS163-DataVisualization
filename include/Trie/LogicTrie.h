#pragma once
#include "Trie/LogicTrieNode.h"
#include "Trie/VisualTrieNode.h"
#include "Trie/TrieAnimStep.h"





///// Event (animation step) generator
class LogicTrie {
public:
	LogicTrie();
	~LogicTrie();
	LogicTrie(const LogicTrie& other); // Copy constructor

	LogicTrie& operator=(const LogicTrie& other); // assignment op

	LogicTrieNode* root = nullptr;
	uint64_t currentNodeID = 0;


	unsigned int getSize(); // Get size of tree (number of nodes) (not O(1))
	unsigned int getNumWords(); // Get number of words (not O(1))
	unsigned int countLeaf(); // Get num of leaf nodes (not O(1))
	LogicTrieNode* newNode(char c);
	LogicTrieNode* newNode(char c, bool isEndOfWord);

	// Get node, knowing the ID
	LogicTrieNode* getNodeID(uint64_t ID);
	// Check if word exists (plain version of generateSearchEvents)
	bool wordExists(std::string word);
	// Insert a word to init data (plain version of generateInsertEvents)
	void insertWord(std::string word);


	// // Reminders
	// bool snapshotTreeReminder = false; // Snapshot after rotation
	// TrieAnimType animTypeReminder = TrieAnimType::NONE;
	// std::string descriptionReminder = "";
	// // Remind to snapshot tree after insertion/rotation
	// void snapshotTree(int key, std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots);


	///// ANIMATION EVENTS
	// Returns bool whether word exists or not
	bool generateSearchEvents(std::string word, 
		std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots);
	// Return the last inserted node with isEndOfWord = true
	LogicTrieNode* generateInsertEvents(std::string word, 
		std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots);
	void generateDeleteEvents(std::string word, 
		std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots);


private:
	void clear(LogicTrieNode*& node);


	///// Helper functions for animation events generation
	bool deleteSuccessful = false;
	LogicTrieNode* generateDeleteEventsHelper(LogicTrieNode*& node, std::string word, int depth, 
		std::vector<TrieAnimStep>& events, std::vector<LogicTrie>& treeSnapshots);

	void setSnapshotReminder(TrieAnimType animType, std::string desc);
	void clearSnapshotReminder();


	///// Helper functions (other)
	LogicTrieNode* copyTree(const LogicTrieNode* node); // Return copy of tree

	unsigned int getSizeHelper(LogicTrieNode* node);
	unsigned int getNumWordsHelper(LogicTrieNode* node);
	void         countLeafHelper(LogicTrieNode* node, unsigned int& totalCnt);
	// Get node, knowing the ID (helper function)
	LogicTrieNode* getNodeIDHelper(uint64_t ID, LogicTrieNode* node);
};
