#include "SLL/SLLAnimStep.h"




SLLAnimStep::SLLAnimStep() {}

SLLAnimStep::SLLAnimStep(SLLAnimType type, std::string desc, SLLNode* pCur, int curIndex)
	: type(type), desc(desc)
	, pCur(pCur), curIndex(curIndex)
	// , pSearch(pSearch)
{}

SLLAnimStep::SLLAnimStep(SLLAnimType type, std::string desc, 
					   	 std::vector<int> highlightLineIndex, SLLNode* pCur, int curIndex)
	: type(type), desc(desc)
	, pCur(pCur), curIndex(curIndex)
	, highlightLineIndex(highlightLineIndex)
{}

SLLAnimStep::~SLLAnimStep() {}
