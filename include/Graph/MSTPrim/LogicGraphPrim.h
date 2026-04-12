#pragma once
#include "Graph/LogicGraph.h"
#include "Graph/MSTPrim/LogicGraphVertexPrim.h"
#include "Graph/MSTPrim/PrimAnimStep.h"

#include <queue>





///// GRAPH REPRESENTED AS ADJACENCY LIST
class LogicGraphPrim : public LogicGraph {
public:
	explicit LogicGraphPrim(unsigned int numVertex);
	explicit LogicGraphPrim(std::vector<std::vector<Edge>>& adjList);
	// LogicGraphPrim(const LogicGraphPrim& other); // Copy constructor

	// LogicGraphPrim& operator=(const LogicGraphPrim& other); // Assignment op


	std::vector<LogicGraphVertexPrim> logicVertices;

	// // Get vertex, knowing the ID
	// LogicGraphVertexPrim* getVertexID(int ID);
	// // Check if word exists (plain version of generateSearchEvents)
	// bool wordExists(std::string word);

	// Return snapshot of graph (only the vertices)
	std::vector<LogicGraphVertexPrim> logicVerticesSnapshot() const;
	// Calculate the edge sum of MST, using a logicVertices snapshot
	unsigned int edgeSumMST(std::vector<LogicGraphVertexPrim>& graphSnapshot) const;



	///// ANIMATION EVENTS
	void generatePrimEvents(int startVertex, std::vector<PrimAnimStep>& events, 
		std::vector<std::vector<LogicGraphVertexPrim>>& graphSnapshots);
	// // Returns bool whether word exists or not
	// bool generateSearchEvents(std::string word, 
	// 	std::vector<PrimAnimStep>& events, std::vector<LogicGraphPrim>& graphSnapshots);
	// // Return the last inserted vertex with isEndOfWord = true
	// LogicGraphVertexPrim* generateInsertEvents(std::string word, 
	// 	std::vector<PrimAnimStep>& events, std::vector<LogicGraphPrim>& graphSnapshots);
	// void generateDeleteEvents(std::string word, 
	// 	std::vector<PrimAnimStep>& events, std::vector<LogicGraphPrim>& graphSnapshots);


private:
	// void clear(LogicGraphVertex*& vertex);


	// ///// Helper functions for animation events generation
	// LogicGraphVertex* generateDeleteEventsHelper(LogicGraphVertex*& vertex, std::string word, int depth, 
	// 	std::vector<PrimAnimStep>& events, std::vector<LogicGraph>& graphSnapshots);

	// void setSnapshotReminder(GraphAnimType animType, std::string desc);
	// void clearSnapshotReminder();


	///// Helper functions (other)
	// LogicGraphVertex* copyTree(const LogicGraphVertex* vertex); // Return copy of graph

	// unsigned int getSizeHelper(LogicGraphVertex* vertex);
	// void         countLeafHelper(LogicGraphVertex* vertex, unsigned int& totalCnt);
	// // Get vertex, knowing the ID (helper function)
	// LogicGraphVertex* getVertexIDHelper(int ID, LogicGraphVertex* vertex);
};
