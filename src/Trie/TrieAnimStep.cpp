#include "Trie/TrieAnimStep.h"



TrieAnimStep::TrieAnimStep() {}

TrieAnimStep::TrieAnimStep(TrieAnimType type, std::string description, std::vector<int> highlightCodeLineIndex)
	: type(type), description(description), highlightCodeLineIndex(highlightCodeLineIndex)
{}

TrieAnimStep::TrieAnimStep(TrieAnimType type, std::string description, std::vector<int> highlightCodeLineIndex, uint64_t curID)
	: type(type), description(description), highlightCodeLineIndex(highlightCodeLineIndex)
	, hasCurID(true), curID(curID)
{}

TrieAnimStep::TrieAnimStep(TrieAnimType type, std::string description, std::vector<int> highlightCodeLineIndex, uint64_t curID, int oldTreeSnapshotIndex)
	: type(type), description(description), highlightCodeLineIndex(highlightCodeLineIndex)
	, hasCurID(true), curID(curID), oldTreeSnapshotIndex(oldTreeSnapshotIndex)
{}
