#pragma once
#include <iostream>
#include <string>
#include <vector>





// Written in C++-like pseudocode
// -- SEARCH --
inline const std::vector<std::string> SLL_CODE_SEARCH = {
	"1 index = 0, cur = pHead", // 0
	"2 while (cur != NULLPTR):",
	"3     if (cur->val == searchValue):",
	"4         return index",
	"5     else:",
	"6         index++, cur = cur->pNext",
	"7 return NULLPTR"
};


// -- UPDATE --
inline const std::vector<std::string> SLL_CODE_UPDATE = {
	"1 index = 0, cur = pHead", // 0
	"2 while (cur != NULLPTR):",
	"3     if (index == updateIndex):",
	"4         cur->val = updateValue",
	"5         return",
	"6     else:",
	"7         index++, cur = cur->pNext"
};


// -- INSERT --
inline const std::vector<std::string> SLL_CODE_INSERT = {
	" 1 if (insertIndex == 0):", // 0
	" 2     node = new Node",
	" 3     node->val = insertValue",
	" 4     node->pNext = pHead",
	" 5     pHead = node",
	" 6     return",
	" 7 index = 0, cur = pHead", // 6
	" 8 while (cur != NULLPTR):", // 7
	" 9     if (index == insertIndex - 1):",
	"10         node = new Node",
	"11         node->val = insertValue",
	"12         node->pNext = cur->pNext",
	"13         cur->pNext = node",
	"14         return",
	"15     index++, cur = cur->pNext" // 14
};


// -- REMOVE --
inline const std::vector<std::string> SLL_CODE_REMOVE = {
	" 1 if (insertIndex == 0):", // 0
	" 2     temp = pHead",
	" 3     pHead = pHead->pNext",
	" 4     delete temp",
	" 5     return",
	" 6 index = 0, cur = pHead", // 5
	" 7 while (cur != NULLPTR):", // 6
	" 8     if (index == insertIndex - 1):",
	" 9         temp = cur->pNext",
	"10         cur->pNext = temp->pNext",
	"11         delete temp",
	"12         return",
	"13     index++, cur = cur->pNext" // 12
};
