#pragma once
#include <iostream>
#include <string>
#include <vector>





// Written in pseudocode
// -- SEARCH --
inline const std::vector<std::string> HASH_TABLE_CODE_SEARCH = {
	"startIndex = hashFunction(key)", // 0
	"curIndex = startIndex",
	"while True:",
	"    currentSlot = table[curIndex]",
	"    if currentSlot.isEmpty() and not currentSlot.isDeleted():",
	"        return NO_KEY_FOUND",
	"    if currentSlot.key == key:",
	"        return currentSlot",
	"    curIndex = (curIndex + 1) mod TableSize",
	"    if curIndex == startIndex:",
	"        return NO_KEY_FOUND"
};


// -- UPDATE --
inline const std::vector<std::string> HASH_TABLE_CODE_UPDATE = {
	"startIndex = hashFunction(key)", // 0
	"curIndex = startIndex",
	"while True:",
	"    currentSlot = table[curIndex]",
	"    if currentSlot.isEmpty() and not currentSlot.isDeleted():",
	"        return NO_KEY_FOUND",
	"    if currentSlot.key == key:",
	"        table[i].empty = True",
	"        table[i].deleted = True",
	"    curIndex = (curIndex + 1) mod TableSize",
	"    if curIndex == startIndex:",
	"        return NO_KEY_FOUND",
	"startIndex = hashFunction(newKey)", // 12
	"curIndex = startIndex",
	"while True:",
	"    currentSlot = table[curIndex]",
	"    if currentSlot.isEmpty() and not currentSlot.isDeleted():",
	"        currentSlot.key = key",
	"        currentSlot.empty = currentSlot.deleted = False",
	"    curIndex = (curIndex + 1) mod TableSize",
	"    if curIndex == startIndex:",
	"        return CANNOT_INSERT"
};


// -- INSERT --
inline const std::vector<std::string> HASH_TABLE_CODE_INSERT = {
	"startIndex = hashFunction(key)", // 0
	"curIndex = startIndex",
	"while True:",
	"    currentSlot = table[curIndex]",
	"    if currentSlot.isEmpty() and not currentSlot.isDeleted():",
	"        currentSlot.key = key",
	"        currentSlot.empty = currentSlot.deleted = False",
	"    curIndex = (curIndex + 1) mod TableSize",
	"    if curIndex == startIndex:",
	"        return CANNOT_INSERT"
};


// -- REMOVE --
inline const std::vector<std::string> HASH_TABLE_CODE_REMOVE = {
	"startIndex = hashFunction(key)", // 0
	"curIndex = startIndex",
	"while True:",
	"    currentSlot = table[curIndex]",
	"    if currentSlot.isEmpty() and not currentSlot.isDeleted():",
	"        return NO_KEY_FOUND",
	"    if currentSlot.key == key:",
	"        table[i].empty = True",
	"        table[i].deleted = True",
	"    curIndex = (curIndex + 1) mod TableSize",
	"    if curIndex == startIndex:",
	"        return NO_KEY_FOUND"
};
