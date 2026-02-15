#pragma once
#include <iostream>
#include <string>




struct SLLNode {
	int val;
	SLLNode* pNext;
};


enum class SLLAnimType : unsigned char {
	NONE,
	CREATE_CUR, // Create cur pointer at head
	MOVE_CUR_FORWARD // Move cur to cur->pNext
};


class SLLAnimStep {
public:
	SLLAnimStep();
	// SLLAnimStep(SLLAnimType type, std::string text);
	SLLAnimStep(SLLAnimType type, std::string text, SLLNode* pCur, int curIndex, SLLNode* pSearch);
	~SLLAnimStep();
	
	SLLAnimType type = SLLAnimType::NONE;

	// Index
	// int idxCreateCur = -1;
	// int idxMoveCur = -1;

	// CREATE_CUR, MOVE_CUR_FORWARD
	// Before moving
	SLLNode* pCur = nullptr;
	int curIndex = 0;
	SLLNode* pSearch = nullptr; // Hold the searched node

	std::string text = ""; // Text to display
};
