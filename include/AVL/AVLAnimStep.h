#pragma once
#include "AVL/LogicAVLNode.h"





enum class AVLAnimType : unsigned char {
	NONE,
	HIGHLIGHT_NODE,
	HIGHLIGHT_FOUND_NODE,
	MOVE_HIGHLIGHT_LEFT_DOWN,  // curKey is the parent's key
	MOVE_HIGHLIGHT_RIGHT_DOWN, // curKey is the parent's key

	INSERT_NODE,               // Includes highlighting, lerp tree
	HIGHLIGHT_NODE_UPDATE_HEIGHT,
	MOVE_HIGHLIGHT_LEFT_UP,    // curKey is the parent's key
	MOVE_HIGHLIGHT_RIGHT_UP,   // curKey is the parent's key
	ROTATE_RIGHT_LL, // No highlighting nodes in rotation events, lerp tree
	ROTATE_LEFT_RR,
	ROTATE_LEFT_LR,
	ROTATE_RIGHT_LR,
	ROTATE_LEFT_RL,
	ROTATE_RIGHT_RL,

	COPY_KEY_FROM_MIN_SUCC,    // Highlights node that got copied, curKey is the key to be copied
	DELETE_LEAF_NODE,          // No highlighting
	DELETE_NODE_ONE_CHILD      // No highlighting
};



class AVLAnimStep {
public:
	AVLAnimStep();
	AVLAnimStep(AVLAnimType type, std::string description, std::vector<int> highlightCodeLineIndex);
	AVLAnimStep(AVLAnimType type, std::string description, std::vector<int> highlightCodeLineIndex, int curKey);
	AVLAnimStep(AVLAnimType type, std::string description, std::vector<int> highlightCodeLineIndex, int curKey, int oldTreeSnapshotIndex);

	AVLAnimType type = AVLAnimType::NONE;
	std::string description = "";
	std::vector<int> highlightCodeLineIndex;

	bool hasCurKey = false; // Whether anim step considers the current node
	int curKey = -1; // Key of current node (highlighted node)
	int oldTreeSnapshotIndex = -1; // Index of old tree snapshot
	// (if transitioning from tree index A to B, the int is B)
	// (-1 means current tree)

	// Whether this step happens at/after when copying minimum successor node
	bool afterCopyMinimumSucc = false;
};


inline const AVLAnimStep AVLAnimStepOldTreeIndex(AVLAnimType type, std::string description, std::vector<int> highlightCodeLineIndex, int oldTreeSnapshotIndex) {
	AVLAnimStep animStep = AVLAnimStep(type, description, highlightCodeLineIndex, -1, oldTreeSnapshotIndex);
	animStep.hasCurKey = false;
	return animStep;
}
