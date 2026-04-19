#pragma once
#include "Trie/LogicTrieNode.h"





enum class TrieAnimType : unsigned char {
	NONE,
	HIGHLIGHT_NODE,
	HIGHLIGHT_FOUND_NODE,
	MOVE_HIGHLIGHT_DOWN,       // curID is the parent's ID

	INSERT_NODE,               // Includes highlighting, lerp tree
	MOVE_HIGHLIGHT_UP,         // curID is the parent's ID

	DELETE_LEAF_NODE           // No highlighting
};


enum class TrieDisplayPseudocode : unsigned char {
	NORMAL,
	DELETION,
	INSERTION
};



class TrieAnimStep {
public:
	TrieAnimStep();
	TrieAnimStep(TrieAnimType type, std::string description, 
		std::vector<int> highlightCodeLineIndex);
	TrieAnimStep(TrieAnimType type, std::string description, 
		std::vector<int> highlightCodeLineIndex, uint64_t curID);
	TrieAnimStep(TrieAnimType type, std::string description, 
		std::vector<int> highlightCodeLineIndex, uint64_t curID, int oldTreeSnapshotIndex);

	TrieAnimType type = TrieAnimType::NONE;
	std::string description = "";
	std::vector<int> highlightCodeLineIndex;

	bool hasCurID = false; // Whether anim step considers the current node
	uint64_t curID = -1;        // Key of current node (highlighted node)
	char charLink = 0;     // Char of link to the child node
	int oldTreeSnapshotIndex = -1; // Index of old tree snapshot
	// (if transitioning from tree index A to B, the variable is B)
	// (-1 means current tree)

	// Which pseudocode to display and highlight
	TrieDisplayPseudocode displayPseudocode = TrieDisplayPseudocode::NORMAL;
};


inline const TrieAnimStep TrieAnimStepOldTreeIndex(TrieAnimType type, std::string description, std::vector<int> highlightCodeLineIndex, int oldTreeSnapshotIndex) {
	TrieAnimStep animStep = TrieAnimStep(type, description, highlightCodeLineIndex, -1, oldTreeSnapshotIndex);
	animStep.hasCurID = false;
	return animStep;
}
