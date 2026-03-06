#include "HashTable/HashAnimStep.h"





HashAnimStep::HashAnimStep() {}

HashAnimStep::HashAnimStep(HashAnimType type, std::string desc, std::vector<int> highlightLineIndex, int curIndex)
	: type(type), desc(desc), highlightLineIndex(highlightLineIndex), curIndex(curIndex)
{}

// HashAnimStep::HashAnimStep(HashAnimType type, std::string desc, std::vector<int> highlightLineIndex, int curIndex, int curValue)
// 	: type(type), desc(desc), highlightLineIndex(highlightLineIndex), curIndex(curIndex), insertVal(curValue)
// {}
