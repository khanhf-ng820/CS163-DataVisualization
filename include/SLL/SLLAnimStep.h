#pragma once
#include <iostream>
#include <string>




enum class SLLAnimType : unsigned char {
	NONE,
	CREATE_CUR, // Create cur pointer at head
	MOVE_CUR_FORWARD // Move cur to cur->pNext
};


class SLLAnimStep {
public:
	SLLAnimStep();
	SLLAnimStep(SLLAnimType type, std::string text);
	~SLLAnimStep();
	
	SLLAnimType type = SLLAnimType::NONE;

	// Index
	// int idxCreateCur = -1;
	// int idxMoveCur = -1;

	std::string text = ""; // Text to display
};
