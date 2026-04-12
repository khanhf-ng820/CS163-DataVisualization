#include "Graph/MSTPrim/PrimAnimStep.h"




PrimAnimStep::PrimAnimStep() {}

PrimAnimStep::PrimAnimStep(PrimAnimType type, std::string description, 
		std::vector<int> highlightCodeLineIndex)
	: type(type), description(description), highlightCodeLineIndex(highlightCodeLineIndex)
{}

PrimAnimStep::PrimAnimStep(PrimAnimType type, std::string description, 
		std::vector<int> highlightCodeLineIndex, int vertexID)
	: type(type), description(description), highlightCodeLineIndex(highlightCodeLineIndex)
	, hasVertexID(true), vertexID(vertexID)
{
	if (vertexID == -1) hasVertexID = false;
}

PrimAnimStep::PrimAnimStep(PrimAnimType type, std::string description, 
	std::vector<int> highlightCodeLineIndex, int vertexID, int toVertexID)
	: type(type), description(description), highlightCodeLineIndex(highlightCodeLineIndex)
	, hasVertexID(true), vertexID(vertexID)
	, hasToVertexID(true), toVertexID(toVertexID)
{
	if (vertexID == -1) hasVertexID = false;
	if (toVertexID == -1) hasToVertexID = false;
}

PrimAnimStep::PrimAnimStep(PrimAnimType type, std::string description, 
	std::vector<int> highlightCodeLineIndex, int vertexID, int toVertexID, int oldGraphSnapshotIndex)
	: type(type), description(description), highlightCodeLineIndex(highlightCodeLineIndex)
	, hasVertexID(true), vertexID(vertexID)
	, hasToVertexID(true), toVertexID(toVertexID)
	, oldGraphSnapshotIndex(oldGraphSnapshotIndex)
{
	if (vertexID == -1) hasVertexID = false;
	if (toVertexID == -1) hasToVertexID = false;
}
