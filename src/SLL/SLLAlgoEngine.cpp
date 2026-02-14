#include "SLL/SLLAlgoEngine.h"





SLLAlgoEngine::SLLAlgoEngine() {
	
}

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
	pSearch = nullptr;

	pCurCreated = false;
}



std::vector<SLLAnimStep> SLLAlgoEngine::getEventsSearch(int x) {
	pSearch = nullptr;
	std::vector<SLLAnimStep> events;

	events.push_back(SLLAnimStep(SLLAnimType::CREATE_CUR, "Created cur, cur points to head of linked list"));
	pCur = pHead;
	curIndex = 0;

	while (pCur) {
		events.push_back(SLLAnimStep(SLLAnimType::NONE, "Checking node " + std::to_string(pCur->val) + " with " + std::to_string(x)));
		if (pCur->val == x) {
			events.push_back(SLLAnimStep(SLLAnimType::NONE, "Found node with value " + std::to_string(x)));
			pSearch = pCur;
			return events;
		}
		events.push_back(SLLAnimStep(SLLAnimType::MOVE_CUR_FORWARD, "Different value, move cur to next node"));
		pCur = pCur->pNext;
		curIndex++;
	}

	events.push_back(SLLAnimStep(SLLAnimType::NONE, "Reached null node, stop."));
	return events;
}
