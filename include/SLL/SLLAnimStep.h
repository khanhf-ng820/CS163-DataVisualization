#pragma once
#include <string>




enum class AnimType : int {
	NONE,
	CREATE_CUR, // Create cur pointer at head
	MOVE_CUR_FORWARD // Move cur to cur->pNext
};


class SLLAnimStep {
public:
	SLLAnimStep();
	~SLLAnimStep();
	
	AnimType type;

	// Index
	int idxCreateCur = -1;
	int idxMoveCur = -1;

	std::string text; // Text to display
};
