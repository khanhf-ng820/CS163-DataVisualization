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



// -- SEARCH --
std::vector<SLLAnimStep> SLLAlgoEngine::getEventsSearch(int x) {
	// pSearch = nullptr;
	std::vector<SLLAnimStep> events;

	events.push_back(SLLAnimStep(SLLAnimType::CREATE_CUR, "Created cur, cur points to head of linked list", {0}, pHead, 0));
	pCur = pHead;
	curIndex = 0;

	while (pCur) {
		events.push_back(SLLAnimStep(SLLAnimType::NONE, "Checking node " + std::to_string(pCur->val) + " with " + std::to_string(x), {1,2}, pCur, curIndex));
		if (pCur->val == x) {
			// pSearch = pCur;
			events.push_back(SLLAnimStepSearch(SLLAnimType::NONE, "Found node with value " + std::to_string(x) + ", and stop.", {3}, pCur, curIndex, pCur));
			return events;
		}
		events.push_back(SLLAnimStep(SLLAnimType::MOVE_CUR_FORWARD, "Different value, move cur forward", {4,5}, pCur, curIndex));
		pCur = pCur->pNext;
		curIndex++;
	}

	events.push_back(SLLAnimStep(SLLAnimType::NONE, "Reached null node, stop.", {6}, pCur, curIndex));
	return events;
}



// -- UPDATE --
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

	events.push_back(SLLAnimStep(SLLAnimType::CREATE_CUR, "Created cur, cur points to head of linked list", {0}, pHead, 0));
	pCur = pHead;
	curIndex = 0;

	while (pCur) {
		if (curIndex == idx) {
			events.push_back(SLLAnimStepSearch(SLLAnimType::NONE, "cur points to node at index " + std::to_string(idx), {1,2}, pCur, curIndex, pCur));
			events.push_back(SLLAnimStep(SLLAnimType::UPDATE_CUR_VAL, "Update node value to " + std::to_string(x) + ", and stop.", {3,4}, pCur, curIndex));
			return events;
		}
		events.push_back(SLLAnimStep(SLLAnimType::MOVE_CUR_FORWARD, "cur does not point to node at index " + std::to_string(idx) + ", move cur forward", {1,5,6}, pCur, curIndex));
		pCur = pCur->pNext;
		curIndex++;
	}

	events.push_back(SLLAnimStep(SLLAnimType::NONE, "Reached null node, stop.", {}, pCur, curIndex));
	return events;
}



// -- INSERT --
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
		events.push_back(SLLAnimStepInsert(SLLAnimType::CREATE_NEW_NODE, "We need to insert at the beginning. Created new node with value " + std::to_string(x), {0,1,2}, nullptr, -1, nullptr, idx));
		events.back().idxInsert = idx;

		events.push_back(SLLAnimStep(SLLAnimType::LINK_NEW_NODE_TO_NEXT, "Link the new node to head of linked list", {3}, nullptr, -1));
		events.back().idxInsert = idx;
		events.back().insertLinkNext = true;
		
		events.push_back(SLLAnimStep(SLLAnimType::LINK_HEAD_TO_NEW_NODE, "Set head of linked list as the new node", {4}, nullptr, -1));
		events.back().idxInsert = idx;
		events.back().insertLinkPrev = true;
		events.back().insertLinkNext = true;
		
		events.push_back(SLLAnimStep(SLLAnimType::MOVE_NODES_INSERT_BEG, "Move nodes (for visualization), and stop.", {5}, nullptr, -1));
		events.back().idxInsert = idx;
		events.back().insertLinkPrev = true;
		events.back().insertLinkNext = true;
		// size++;
		return events;
	} // else

	events.push_back(SLLAnimStep(SLLAnimType::CREATE_CUR, "Created cur, cur points to head of linked list", {6}, pHead, 0));
	events.back().idxInsert = idx;
	pCur = pHead;
	curIndex = 0;

	while (pCur) {
		if (curIndex != idx - 1) {
			events.push_back(SLLAnimStep(SLLAnimType::MOVE_CUR_FORWARD, "cur is not at index " + std::to_string(idx-1) + ", move cur forward", {7, 14}, pCur, curIndex));
			events.back().idxInsert = idx;
			pCur = pCur->pNext;
			curIndex++;
			continue;
		}
		// SLLNode* pInsert = new SLLNode{x, nullptr};
		events.push_back(SLLAnimStepInsert(SLLAnimType::CREATE_NEW_NODE, "Created new node with value " + std::to_string(x), {8,9,10}, pCur, curIndex, nullptr, idx));
		events.back().idxInsert = idx;

		// pInsert->pNext = pCur->pNext;
		events.push_back(SLLAnimStep(SLLAnimType::LINK_NEW_NODE_TO_NEXT, "Link the new node to the next node of cur", {11}, pCur, curIndex));
		events.back().idxInsert = idx;
		events.back().insertLinkNext = true;

		// pCur->pNext = pInsert;
		events.push_back(SLLAnimStep(SLLAnimType::LINK_PREV_TO_NEW_NODE, "Link the current node to the new node", {12}, pCur, curIndex));
		events.back().idxInsert = idx;
		events.back().insertLinkPrev = true;
		events.back().insertLinkNext = true;
		events.push_back(SLLAnimStep(SLLAnimType::MOVE_NODES_INSERT_K, "Move nodes (for visualization), and stop.", {13}, pCur, curIndex));
		events.back().idxInsert = idx;
		events.back().insertLinkPrev = true;
		events.back().insertLinkNext = true;

		// size++;
		break;
	}
	return events;
}



// -- REMOVE --
void SLLAlgoEngine::remove(int idx) {
	if (pHead == nullptr) { // Empty list
		idxRemove = -1;
		return;
	}
	if (idx == 0) { // Remove head
		oldRemoveVal = pHead->val;
		idxRemove = idx;
		SLLNode* temp = pHead;
		pHead = pHead->pNext;
		delete temp;
		size--;
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
		SLLNode* temp = cur->pNext;
		cur->pNext = temp->pNext;
		oldRemoveVal = temp->val;
		idxRemove = idx;
		delete temp;
		size--;
		return;
	}
}


std::vector<SLLAnimStep> SLLAlgoEngine::getEventsRemove(int idx) {
	std::vector<SLLAnimStep> events;
	if (idxRemove == -1) return events; // Empty list

	if (idx == 0) {
		events.push_back(SLLAnimStep(SLLAnimType::MOVE_NODES_REMOVE_BEG, "We need to remove head of linked list. Move nodes (for visualization).", {0}, nullptr, -1));
		events.back().idxRemove = idx;

		// Might edit comments soon
		events.push_back(SLLAnimStep(SLLAnimType::CHANGE_LINK_OF_HEAD, "Change link of the node that pHead points to", {1,2}, nullptr, -1));
		events.back().idxRemove = idx;
		events.back().removeChangeLink = true;

		events.push_back(SLLAnimStep(SLLAnimType::REMOVE_NODE, "Remove the desired node, and stop.", {3,4}, nullptr, -1));
		events.back().idxRemove = idx;
		events.back().removeChangeLink = true;
		events.back().removedNode = true;

		return events;
	}

	events.push_back(SLLAnimStep(SLLAnimType::CREATE_CUR, "Created cur, cur points to head of linked list", {5}, pHead, 0));
	events.back().idxRemove = idx;
	pCur = pHead;
	curIndex = 0;

	while (pCur) {
		if (curIndex != idx - 1) {
			events.push_back(SLLAnimStep(SLLAnimType::MOVE_CUR_FORWARD, "cur is not at index " + std::to_string(idx-1) + ", move cur forward", {6,12}, pCur, curIndex));
			events.back().idxRemove = idx;
			pCur = pCur->pNext;
			curIndex++;
			continue;
		}

		events.push_back(SLLAnimStep(SLLAnimType::MOVE_NODES_REMOVE_K, "Move nodes (for visualization)", {6,7}, pCur, curIndex));
		events.back().idxRemove = idx;

		// Might edit comments soon
		events.push_back(SLLAnimStep(SLLAnimType::CHANGE_LINK_OF_CUR, "Change the link of the node that cur points to", {8,9}, pCur, curIndex));
		events.back().idxRemove = idx;
		events.back().removeChangeLink = true;

		events.push_back(SLLAnimStep(SLLAnimType::REMOVE_NODE, "Remove the desired node, and stop.", {10,11}, pCur, curIndex));
		events.back().idxRemove = idx;
		events.back().removeChangeLink = true;
		events.back().removedNode = true;
		break;
	}
	return events;
}
