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
	MOVE_CUR_FORWARD, // Move cur to cur->pNext

	CREATE_NEW_NODE, // Create a new node
	LINK_NEW_NODE_TO_NEXT, // Link the new node to the next node (or nullptr)
	LINK_PREV_TO_NEW_NODE, // Link the previous node to the new node
	LINK_HEAD_TO_NEW_NODE, // Set pHead to the new node (INSERT_BEG MODE)
	MOVE_NODES_INSERT_BEG, // Move the new node and nodes after it (INSERT_BEG MODE)
	MOVE_NODES_INSERT_K // Move the new node and nodes after it (INSERT_K MODE)
};


class SLLAnimStep {
public:
	SLLAnimStep();
	// SLLAnimStep(SLLAnimType type, std::string text);
	SLLAnimStep(SLLAnimType type, std::string text, SLLNode* pCur, int curIndex);
	~SLLAnimStep();
	
	SLLAnimType type = SLLAnimType::NONE;

	// Index
	// int idxCreateCur = -1;
	// int idxMoveCur = -1;

	// CREATE_CUR, MOVE_CUR_FORWARD
	// Before moving
	SLLNode* pCur = nullptr;
	unsigned int curIndex = 0;
	SLLNode* pSearch = nullptr; // Hold the searched node

	// FOR INSERT MODE ONLY
	SLLNode* pInsert = nullptr; // Hold the inserted node
	int idxInsert = 0;
	bool insertLinkPrev = false; // Prev is linked to inserted node
	bool insertLinkNext = false; // Inserted node is linked next

	std::string text = ""; // Text to display
};


// Other constructors
// SEARCHING
inline SLLAnimStep SLLAnimStepSearch(SLLAnimType type, std::string text, SLLNode* pCur, int curIndex, SLLNode* pSearch) {
	SLLAnimStep step;
	step.type = type;
	step.text = text;
	step.pCur = pCur;
	step.curIndex = curIndex;
	step.pSearch = pSearch;
	return step;
}
// INSERTING
inline SLLAnimStep SLLAnimStepInsert(SLLAnimType type, std::string text, SLLNode* pCur, int curIndex, SLLNode* pInsert, int idxInsert) {
	SLLAnimStep step;
	step.type = type;
	step.text = text;
	step.pCur = pCur;
	step.curIndex = curIndex;
	step.pInsert = pInsert;
	step.idxInsert = idxInsert;
	return step;
}
