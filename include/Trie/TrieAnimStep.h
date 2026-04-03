#pragma once
#include "Trie/LogicTrieNode.h"





enum class TrieAnimType : unsigned char {
	NONE,
	HIGHLIGHT_NODE,
	HIGHLIGHT_FOUND_NODE,
	MOVE_HIGHLIGHT_DOWN,       // curID is the parent's ID

	INSERT_NODE,               // Includes highlighting, lerp tree
	HIGHLIGHT_NODE_UPDATE_HEIGHT,
	MOVE_HIGHLIGHT_UP,         // curID is the parent's ID

	DELETE_LEAF_NODE           // No highlighting
};



class TrieAnimStep {
public:
	TrieAnimStep();
	TrieAnimStep(TrieAnimType type, std::string description, 
		std::vector<int> highlightCodeLineIndex);
	TrieAnimStep(TrieAnimType type, std::string description, 
		std::vector<int> highlightCodeLineIndex, int curID);
	TrieAnimStep(TrieAnimType type, std::string description, 
		std::vector<int> highlightCodeLineIndex, int curID, int oldTreeSnapshotIndex);

	TrieAnimType type = TrieAnimType::NONE;
	std::string description = "";
	std::vector<int> highlightCodeLineIndex;

	bool hasCurID = false; // Whether anim step considers the current node
	int curID = -1;        // Key of current node (highlighted node)
	char charLink = 0;     // Char of link to the child node
	int oldTreeSnapshotIndex = -1; // Index of old tree snapshot
	// (if transitioning from tree index A to B, the variable is B)
	// (-1 means current tree)

	// Whether this step happens at/after when copying minimum successor node
	bool afterCopyMinimumSucc = false;
};


inline const TrieAnimStep TrieAnimStepOldTreeIndex(TrieAnimType type, std::string description, std::vector<int> highlightCodeLineIndex, int oldTreeSnapshotIndex) {
	TrieAnimStep animStep = TrieAnimStep(type, description, highlightCodeLineIndex, -1, oldTreeSnapshotIndex);
	animStep.hasCurID = false;
	return animStep;
}
