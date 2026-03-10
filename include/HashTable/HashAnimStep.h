#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "HashTable/HashTableSlot.h"





enum class HashAnimType : unsigned char {
	NONE,
	HIGHLIGHT_SLOT,
	HIGHLIGHT_FOUND_SLOT, // Includes highlighting INSERTED slot
	SET_KEY_TO_SLOT,      // Includes highlighting slot
	// UPDATE_VALUE,      // Includes highlighting slot
	SET_DELETED_TO_SLOT   // Includes highlighting slot
};


class HashAnimStep {
public:
	HashAnimStep();
	HashAnimStep(HashAnimType type, std::string desc, std::vector<int> highlightLineIndex, int curIndex);
	// HashAnimStep(HashAnimType type, std::string desc, std::vector<int> highlightLineIndex, int curIndex, int curValue);

	HashAnimType type = HashAnimType::NONE; // Type of animation
	std::string desc; // Description text
	std::vector<int> highlightLineIndex; // Which row(s) of pseudocode to highlight


	// FOR ANIMATION
	int curIndex = -1; // Index of slot currently highlighted

	int searchSlotIdx = -1; // Index of slot currently animating

	int oldKeySlot = -1; // Old key of slot before changes
	int insertSlotIdx = -1; // Index of inserted slot
	int insertKey = -1; // Key to assign/insert to the slot
	// int insertVal = -1; // Value to assign/insert to the slot

	int removeSlotIdx = -1; // Index of slot to remove
	// int removeVal = -1; // Value to remove from the slot
};
