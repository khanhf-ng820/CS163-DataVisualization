#pragma once
#include "SLL/SLLAnimStep.h"





struct SLLNode {
	int val;
	SLLNode* pNext;
};



class SLLAlgoEngine {
public:
	SLLAlgoEngine();
	~SLLAlgoEngine();

	void clear(); // Clear the linked list

	SLLNode* pHead = nullptr;
	SLLNode* pCur = nullptr;
	SLLNode* pSearch = nullptr; // Hold the searched node

	bool pCurCreated = false;
};
