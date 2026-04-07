#include "Graph/Dijkstra/DijkstraAnimStep.h"




DijkstraAnimStep::DijkstraAnimStep() {}

DijkstraAnimStep::DijkstraAnimStep(DijkstraAnimType type, std::string description, 
		std::vector<int> highlightCodeLineIndex)
	: type(type), description(description), highlightCodeLineIndex(highlightCodeLineIndex)
{}

DijkstraAnimStep::DijkstraAnimStep(DijkstraAnimType type, std::string description, 
		std::vector<int> highlightCodeLineIndex, int vertexID)
	: type(type), description(description), highlightCodeLineIndex(highlightCodeLineIndex)
	, hasVertexID(true), vertexID(vertexID)
{
	if (vertexID == -1) hasVertexID = false;
}

DijkstraAnimStep::DijkstraAnimStep(DijkstraAnimType type, std::string description, 
	std::vector<int> highlightCodeLineIndex, int vertexID, int toVertexID)
	: type(type), description(description), highlightCodeLineIndex(highlightCodeLineIndex)
	, hasVertexID(true), vertexID(vertexID)
	, hasToVertexID(true), toVertexID(toVertexID)
{
	if (vertexID == -1) hasVertexID = false;
	if (toVertexID == -1) hasToVertexID = false;
}

DijkstraAnimStep::DijkstraAnimStep(DijkstraAnimType type, std::string description, 
	std::vector<int> highlightCodeLineIndex, int vertexID, int toVertexID, int oldGraphSnapshotIndex)
	: type(type), description(description), highlightCodeLineIndex(highlightCodeLineIndex)
	, hasVertexID(true), vertexID(vertexID)
	, hasToVertexID(true), toVertexID(toVertexID)
	, oldGraphSnapshotIndex(oldGraphSnapshotIndex)
{
	if (vertexID == -1) hasVertexID = false;
	if (toVertexID == -1) hasToVertexID = false;
}
