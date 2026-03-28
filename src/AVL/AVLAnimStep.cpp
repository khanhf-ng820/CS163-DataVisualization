#include "AVL/AVLAnimStep.h"



AVLAnimStep::AVLAnimStep() {}

AVLAnimStep::AVLAnimStep(AVLAnimType type, std::string description, std::vector<int> highlightCodeLineIndex)
	: type(type), description(description), highlightCodeLineIndex(highlightCodeLineIndex)
{}

AVLAnimStep::AVLAnimStep(AVLAnimType type, std::string description, std::vector<int> highlightCodeLineIndex, int curKey)
	: type(type), description(description), highlightCodeLineIndex(highlightCodeLineIndex)
	, hasCurKey(true), curKey(curKey)
{}

AVLAnimStep::AVLAnimStep(AVLAnimType type, std::string description, std::vector<int> highlightCodeLineIndex, int curKey, int oldTreeSnapshotIndex)
	: type(type), description(description), highlightCodeLineIndex(highlightCodeLineIndex)
	, hasCurKey(true), curKey(curKey), oldTreeSnapshotIndex(oldTreeSnapshotIndex)
{}
