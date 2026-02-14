#pragma once
#include "SLL/SLLAnimStep.h"
#include <vector>





struct SLLNode {
	int val;
	SLLNode* pNext;
};


class SLLAlgoEngine {
public:
	SLLAlgoEngine();
	~SLLAlgoEngine();


	SLLNode* pHead = nullptr;
	// SLLNode* pHead = new SLLNode{36, nullptr};
	SLLNode* pCur = nullptr;
	int curIndex = -1;
	SLLNode* pSearch = nullptr; // Hold the searched node

	bool pCurCreated = false;


	void clear(); // Clear the linked list
	std::vector<SLLAnimStep> getEventsSearch(int x);
};
