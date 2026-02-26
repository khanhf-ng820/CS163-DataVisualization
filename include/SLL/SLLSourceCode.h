#pragma once
#include <iostream>
#include <string>
#include <vector>





// Written in C++-like pseudocode
// -- SEARCH --
inline const std::vector<std::string> SLL_CODE_SEARCH = {
	"index = 0, cur = pHead", // 0
	"while (cur != NULLPTR)",
	"    if (cur->val == searchValue)",
	"        return index",
	"    else",
	"        index++, cur = cur->pNext",
	"return NULLPTR"
};


// -- UPDATE --
inline const std::vector<std::string> SLL_CODE_UPDATE = {
	"index = 0, cur = pHead", // 0
	"while (cur != NULLPTR)",
	"    if (index == updateIndex)",
	"        cur->val = updateValue",
	"        return",
	"    else",
	"        index++, cur = cur->pNext"
};


// -- INSERT --
inline const std::vector<std::string> SLL_CODE_INSERT = {
	"if (insertIndex == 0)", // 0
	"    node = new Node",
	"    node->val = insertValue",
	"    node->pNext = pHead",
	"    pHead = node",
	"    return",
	"index = 0, cur = pHead", // 6
	"while (cur != NULLPTR)", // 7
	"    if (index == insertIndex - 1)",
	"        node = new Node",
	"        node->val = insertValue",
	"        node->pNext = cur->pNext",
	"        cur->pNext = node",
	"        return",
	"    index++, cur = cur->pNext" // 14
};


// -- REMOVE --
inline const std::vector<std::string> SLL_CODE_REMOVE = {
	"if (insertIndex == 0)", // 0
	"    temp = pHead",
	"    pHead = pHead->pNext",
	"    delete temp",
	"    return",
	"index = 0, cur = pHead", // 5
	"while (cur != NULLPTR)", // 6
	"    if (index == insertIndex - 1)",
	"        temp = cur->pNext",
	"        cur->pNext = temp->pNext",
	"        delete temp",
	"        return",
	"    index++, cur = cur->pNext" // 12
};
