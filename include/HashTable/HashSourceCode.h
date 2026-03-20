#pragma once
#include <iostream>
#include <string>
#include <vector>





// Written in pseudocode
// -- SEARCH --
inline const std::vector<std::string> HASH_TABLE_CODE_SEARCH = {
	" 1 startIndex = hashFunction(key)", // 0
	" 2 curIndex = startIndex",
	" 3 while True:",
	" 4     currentSlot = table[curIndex]",
	" 5     if currentSlot.isEmpty() and not currentSlot.isDeleted():",
	" 6         return NO_KEY_FOUND",
	" 7     if currentSlot.key == key:",
	" 8         return currentSlot",
	" 9     curIndex = (curIndex + 1) mod TableSize",
	"10     if curIndex == startIndex:",
	"11         return NO_KEY_FOUND"
};


// -- UPDATE --
inline const std::vector<std::string> HASH_TABLE_CODE_UPDATE = {
	" 1 startIndex = hashFunction(key)", // 0
	" 2 curIndex = startIndex",
	" 3 while True:",
	" 4     currentSlot = table[curIndex]",
	" 5     if currentSlot.isEmpty() and not currentSlot.isDeleted():",
	" 6         return NO_KEY_FOUND",
	" 7     if currentSlot.key == key:",
	" 8         table[i].empty = True",
	" 9         table[i].deleted = True",
	"10     curIndex = (curIndex + 1) mod TableSize",
	"11     if curIndex == startIndex:",
	"12         return NO_KEY_FOUND",
	"13 startIndex = hashFunction(newKey)", // 12
	"14 curIndex = startIndex",
	"15 while True:",
	"16     currentSlot = table[curIndex]",
	"17     if currentSlot.isEmpty() and not currentSlot.isDeleted():",
	"18         currentSlot.key = key",
	"19         currentSlot.empty = currentSlot.deleted = False",
	"20     curIndex = (curIndex + 1) mod TableSize",
	"21     if curIndex == startIndex:",
	"22         return CANNOT_INSERT"
};


// -- INSERT --
inline const std::vector<std::string> HASH_TABLE_CODE_INSERT = {
	" 1 startIndex = hashFunction(key)", // 0
	" 2 curIndex = startIndex",
	" 3 while True:",
	" 4     currentSlot = table[curIndex]",
	" 5     if currentSlot.isEmpty() and not currentSlot.isDeleted():",
	" 6         currentSlot.key = key",
	" 7         currentSlot.empty = currentSlot.deleted = False",
	" 8     curIndex = (curIndex + 1) mod TableSize",
	" 9     if curIndex == startIndex:",
	"10         return CANNOT_INSERT"
};


// -- REMOVE --
inline const std::vector<std::string> HASH_TABLE_CODE_REMOVE = {
	" 1 startIndex = hashFunction(key)", // 0
	" 2 curIndex = startIndex",
	" 3 while True:",
	" 4     currentSlot = table[curIndex]",
	" 5     if currentSlot.isEmpty() and not currentSlot.isDeleted():",
	" 6         return NO_KEY_FOUND",
	" 7     if currentSlot.key == key:",
	" 8         table[i].empty = True",
	" 9         table[i].deleted = True",
	"10     curIndex = (curIndex + 1) mod TableSize",
	"11     if curIndex == startIndex:",
	"12         return NO_KEY_FOUND"
};
