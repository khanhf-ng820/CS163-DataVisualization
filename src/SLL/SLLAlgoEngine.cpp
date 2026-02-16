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
	pSearch = nullptr;
	size = 0;

	pCurCreated = false;
}

SLLNode* SLLAlgoEngine::ithNode(int i) {
	int ix = 0;
	SLLNode* cur = pHead;
	while (cur) {
		if (ix == i)
			return cur;
		cur = cur->pNext;
		ix++;
	}
	return cur;
}



// -- SEARCHING --
std::vector<SLLAnimStep> SLLAlgoEngine::getEventsSearch(int x) {
	// pSearch = nullptr;
	std::vector<SLLAnimStep> events;

	events.push_back(SLLAnimStep(SLLAnimType::CREATE_CUR, "Created cur, cur points to head of linked list", pHead, 0));
	pCur = pHead;
	curIndex = 0;

	while (pCur) {
		events.push_back(SLLAnimStep(SLLAnimType::NONE, "Checking node " + std::to_string(pCur->val) + " with " + std::to_string(x), pCur, curIndex));
		if (pCur->val == x) {
			// pSearch = pCur;
			events.push_back(SLLAnimStepSearch(SLLAnimType::NONE, "Found node with value " + std::to_string(x), pCur, curIndex, pCur));
			return events;
		}
		events.push_back(SLLAnimStep(SLLAnimType::MOVE_CUR_FORWARD, "Different value, move cur forward", pCur, curIndex));
		pCur = pCur->pNext;
		curIndex++;
	}

	events.push_back(SLLAnimStep(SLLAnimType::NONE, "Reached null node, stop.", pCur, curIndex));
	return events;
}



// -- UPDATING --
void SLLAlgoEngine::update(int x, int idx) {
	SLLNode* cur = pHead;
	int curIdx = 0;
	while (cur) {
		if (curIdx == idx) {
			oldUpdateVal = cur->val;
			cur->val = x;
			return;
		}
		cur = cur->pNext;
		curIdx++;
	}
}

std::vector<SLLAnimStep> SLLAlgoEngine::getEventsUpdate(int x, int idx) {
	std::vector<SLLAnimStep> events;

	events.push_back(SLLAnimStep(SLLAnimType::CREATE_CUR, "Created cur, cur points to head of linked list", pHead, 0));
	pCur = pHead;
	curIndex = 0;

	while (pCur) {
		if (curIndex == idx) {
			events.push_back(SLLAnimStepSearch(SLLAnimType::NONE, "cur points to node at index " + std::to_string(idx), pCur, curIndex, pCur));
			events.push_back(SLLAnimStep(SLLAnimType::UPDATE_CUR_VAL, "Update node value to " + std::to_string(x), pCur, curIndex));
			return events;
		}
		events.push_back(SLLAnimStep(SLLAnimType::MOVE_CUR_FORWARD, "cur does not point to node at index " + std::to_string(idx) + ", move cur forward", pCur, curIndex));
		pCur = pCur->pNext;
		curIndex++;
	}

	events.push_back(SLLAnimStep(SLLAnimType::NONE, "Reached null node, stop.", pCur, curIndex));
	return events;
}



// -- INSERTING --
void SLLAlgoEngine::insert(int x, int idx) {
	if (idx == 0) {
		pInsert = new SLLNode{x, nullptr};
		pInsert->pNext = pHead;
		pHead = pInsert;
		size++;
		return;
	}
	SLLNode* cur = pHead;
	int curIdx = 0;
	while (cur) {
		if (curIdx != idx - 1) {
			cur = cur->pNext;
			curIdx++;
			continue;
		}
		pInsert = new SLLNode{x, nullptr};
		pInsert->pNext = cur->pNext;
		cur->pNext = pInsert;
		size++;
		return;
	}
}


std::vector<SLLAnimStep> SLLAlgoEngine::getEventsInsert(int x, int idx) {
	std::vector<SLLAnimStep> events;

	if (idx == 0) {
		events.push_back(SLLAnimStepInsert(SLLAnimType::CREATE_NEW_NODE, "Created new node with value " + std::to_string(x), nullptr, -1, nullptr, idx));
		events.back().idxInsert = idx;

		events.push_back(SLLAnimStep(SLLAnimType::LINK_NEW_NODE_TO_NEXT, "Link new node to head of linked list", nullptr, -1));
		events.back().idxInsert = idx;
		events.back().insertLinkNext = true;
		
		events.push_back(SLLAnimStep(SLLAnimType::LINK_HEAD_TO_NEW_NODE, "Set head of linked list as the new node", nullptr, -1));
		events.back().idxInsert = idx;
		events.back().insertLinkPrev = true;
		events.back().insertLinkNext = true;
		
		events.push_back(SLLAnimStep(SLLAnimType::MOVE_NODES_INSERT_BEG, "Move nodes", nullptr, -1));
		events.back().idxInsert = idx;
		events.back().insertLinkPrev = true;
		events.back().insertLinkNext = true;
		// size++;
		return events;
	} // else

	events.push_back(SLLAnimStep(SLLAnimType::CREATE_CUR, "Created cur, cur points to head of linked list", pHead, 0));
	events.back().idxInsert = idx;
	pCur = pHead;
	curIndex = 0;

	while (pCur) {
		if (curIndex != idx - 1) {
			events.push_back(SLLAnimStep(SLLAnimType::MOVE_CUR_FORWARD, "cur is not at index " + std::to_string(idx-1) + ", move cur forward", pCur, curIndex));
			events.back().idxInsert = idx;
			pCur = pCur->pNext;
			curIndex++;
			continue;
		}
		// SLLNode* pInsert = new SLLNode{x, nullptr};
		events.push_back(SLLAnimStepInsert(SLLAnimType::CREATE_NEW_NODE, "Created new node with value " + std::to_string(x), pCur, curIndex, nullptr, idx));
		events.back().idxInsert = idx;

		// pInsert->pNext = pCur->pNext;
		events.push_back(SLLAnimStep(SLLAnimType::LINK_NEW_NODE_TO_NEXT, "Link new node to the next of cur", pCur, curIndex));
		events.back().idxInsert = idx;
		events.back().insertLinkNext = true;

		// pCur->pNext = pInsert;
		events.push_back(SLLAnimStep(SLLAnimType::LINK_PREV_TO_NEW_NODE, "Link cur to the new node", pCur, curIndex));
		events.back().idxInsert = idx;
		events.back().insertLinkPrev = true;
		events.back().insertLinkNext = true;
		events.push_back(SLLAnimStep(SLLAnimType::MOVE_NODES_INSERT_K, "Move nodes", pCur, curIndex));
		events.back().idxInsert = idx;
		events.back().insertLinkPrev = true;
		events.back().insertLinkNext = true;

		// size++;
		break;
	}
	return events;
}
