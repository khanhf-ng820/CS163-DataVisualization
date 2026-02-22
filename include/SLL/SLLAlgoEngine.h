#pragma once
#include "SLL/SLLAnimStep.h"
#include <vector>





// struct SLLNode {
// 	int val;
// 	SLLNode* pNext;
// };


class SLLAlgoEngine {
public:
	SLLAlgoEngine();
	~SLLAlgoEngine();


	SLLNode* pHead = nullptr;
	// SLLNode* pHead = new SLLNode{36, nullptr};
	SLLNode* pCur = nullptr;
	int curIndex = 0;

	SLLNode* pSearch = nullptr; // Hold the searched node

	SLLNode* pInsert = nullptr; // Hold the inserted node
	int idxInsert = -1;
	bool insertLinkPrev = false; // Prev is linked to inserted node
	bool insertLinkNext = false; // Inserted node is linked next

	int oldUpdateVal = -1; // Old value of a node before updating

	int oldRemoveVal = -1; // Old value of a node before removing
	int idxRemove = -1; // Index of the removed node (-1 means can't remove)

	int size = 0; // Size of linked list

	bool pCurCreated = false;


	void clear(); // Clear the linked list
	SLLNode* ithNode(int i);


	std::vector<SLLAnimStep> getEventsSearch(int x);
	void insert(int x, int idx);
	std::vector<SLLAnimStep> getEventsInsert(int x, int idx);
	void update(int x, int idx);
	std::vector<SLLAnimStep> getEventsUpdate(int x, int idx);
	void remove(int idx);
	std::vector<SLLAnimStep> getEventsRemove(int idx);
};
