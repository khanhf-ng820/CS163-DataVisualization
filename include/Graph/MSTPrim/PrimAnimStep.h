#pragma once
#include "Graph/LogicGraph.h"





enum class PrimAnimType : unsigned char {
	NONE,
	HIGHLIGHT_NODE,
	HIGHLIGHT_NODE_AND_EDGE,
	HIGHLIGHT_UPDATED_NODE,
	// MOVE_HIGHLIGHT_DOWN,       // vertexID is the parent's ID

	// INSERT_NODE,               // Includes highlighting, lerp tree
	// MOVE_HIGHLIGHT_UP,         // vertexID is the parent's ID
	// DELETE_LEAF_NODE,          // No highlighting

	UPDATE_NEIGHBOR,

	ADD_EDGE_TO_MST,              // The final steps before FINISHED_MST_PRIM
	FINISHED_MST_PRIM             // Only the final event
};



class PrimAnimStep {
public:
	PrimAnimStep();
	PrimAnimStep(PrimAnimType type, std::string description, 
		std::vector<int> highlightCodeLineIndex);
	PrimAnimStep(PrimAnimType type, std::string description, 
		std::vector<int> highlightCodeLineIndex, int vertexID);
	PrimAnimStep(PrimAnimType type, std::string description, 
		std::vector<int> highlightCodeLineIndex, int vertexID, int toVertexID);
	PrimAnimStep(PrimAnimType type, std::string description, 
		std::vector<int> highlightCodeLineIndex, int vertexID, int toVertexID, int oldGraphSnapshotIndex);

	PrimAnimType type = PrimAnimType::NONE;
	std::string description = "";
	std::vector<int> highlightCodeLineIndex;

	bool hasVertexID = false; // Whether anim step considers the current vertex
	int vertexID = -1;        // Key of current vertex (highlighted vertex)
	bool hasToVertexID = false; // Whether anim step considers the edge from current vertex to 'to' vertex
	int toVertexID = -1;        // Key of 'to' vertex (highlighted vertex)

	int oldGraphSnapshotIndex = -1; // Index of old graph snapshot
	// (if transitioning from graph index A to B, the variable is B)
	// (-1 means current graph)
};


// inline const PrimAnimStep PrimAnimStepOldTreeIndex(PrimAnimType type, std::string description, std::vector<int> highlightCodeLineIndex, int oldTreeSnapshotIndex) {
// 	PrimAnimStep animStep = PrimAnimStep(type, description, highlightCodeLineIndex, -1, oldTreeSnapshotIndex);
// 	animStep.hasVertexID = false;
// 	return animStep;
// }
