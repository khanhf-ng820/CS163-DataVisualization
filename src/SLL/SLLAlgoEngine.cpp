#include "SLL/SLLAlgoEngine.h"





SLLAlgoEngine::SLLAlgoEngine() {}

SLLAlgoEngine::~SLLAlgoEngine() {
	// Clear the linked list
	clear();
}

// Clear the linked list
void SLLAlgoEngine::clear() {
	SLLNode* cur = pHead;
	while (cur) {
		SLLNode* temp = cur;
		cur = cur->pNext;
		delete temp;
	}

	pHead = nullptr;
	pCur = nullptr;
	pSearch = nullptr; // Hold the searched node

	pCurCreated = false;
}
