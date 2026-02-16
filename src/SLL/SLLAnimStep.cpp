#include "SLL/SLLAnimStep.h"




SLLAnimStep::SLLAnimStep() {}

SLLAnimStep::SLLAnimStep(SLLAnimType type, std::string text, SLLNode* pCur, int curIndex)
	: type(type), text(text)
	, pCur(pCur), curIndex(curIndex)
	// , pSearch(pSearch)
{}

SLLAnimStep::~SLLAnimStep() {}
