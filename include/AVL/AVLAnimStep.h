#pragma once
#include "AVL/LogicAVLNode.h"





enum class AVLAnimType : unsigned char {
	NONE,
	HIGHLIGHT_NODE,
	HIGHLIGHT_MOVE_LEFT,
	HIGHLIGHT_MOVE_RIGHT
};



class AVLAnimStep {
public:
	AVLAnimStep();
	AVLAnimStep(AVLAnimType type, std::string description, std::vector<int> highlightCodeLineIndex, int curKey);

	AVLAnimType type = AVLAnimType::NONE;
	std::string description = "";
	std::vector<int> highlightCodeLineIndex;

	int curKey = -1; // Key of current node (highlighted node)

	int rootKey = -1; // Key of first imbalanced node
	int pivotKey = -1; // Key of child of first imbalanced node
};
