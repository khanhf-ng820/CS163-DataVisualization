#pragma once
#include "AVL/LogicAVLNode.h"





enum class AVLAnimType : unsigned char {
	NONE,
	HIGHLIGHT_NODE,
	HIGHLIGHT_FOUND_NODE,
	MOVE_HIGHLIGHT_LEFT_DOWN,
	MOVE_HIGHLIGHT_RIGHT_DOWN
};



class AVLAnimStep {
public:
	AVLAnimStep();
	AVLAnimStep(AVLAnimType type, std::string description, std::vector<int> highlightCodeLineIndex);
	AVLAnimStep(AVLAnimType type, std::string description, std::vector<int> highlightCodeLineIndex, int curKey);

	AVLAnimType type = AVLAnimType::NONE;
	std::string description = "";
	std::vector<int> highlightCodeLineIndex;

	bool hasCurKey = false; // Whether anim step considers the current node
	int curKey = -1; // Key of current node (highlighted node)

	int rootKey = -1; // Key of first imbalanced node
	int pivotKey = -1; // Key of child of first imbalanced node
};
