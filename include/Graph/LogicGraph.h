#pragma once
#include <random>
#include <sstream>

#include "Graph/VisualGraphVertex.h"
#include "Graph/EdgeStruct.h"
// #include "Graph/GraphAnimStep.h"

#include "utils/readData.hpp"




///// GRAPH REPRESENTED AS ADJACENCY LIST
///// Event (animation step) generator
class LogicGraph {
public:
	explicit LogicGraph(unsigned int numVertex);
	explicit LogicGraph(std::mt19937& rng);
	explicit LogicGraph(std::vector<std::vector<int>>& adjMatrix);
	explicit LogicGraph(std::vector<std::vector<Edge>>& adjList);
	explicit LogicGraph(unsigned int numVertex, std::vector<GraphReader::GraphEdge>& edgeList);
	// LogicGraph(const LogicGraph& other); // Copy constructor

	// LogicGraph& operator=(const LogicGraph& other); // Assignment op


	std::vector<std::vector<Edge>> adjList;
	// std::vector<VisualGraphVertex> visualVertices;


	// Get number of nodes (O(1))
	unsigned int getNumVertex() const;
	// Print adjacency list
	void printAdjList() const;

	// Print graph to string
	std::string printAdjMatString() const;
	std::string printAdjListString() const;
	std::string printEdgeListString() const;

	// // Get vertex, knowing the ID
	// LogicGraphVertex* getVertexID(int ID);
	// // Check if word exists (plain version of generateSearchEvents)
	// bool wordExists(std::string word);



	///// ANIMATION EVENTS
	// // Returns bool whether word exists or not
	// bool generateSearchEvents(std::string word, 
	// 	std::vector<GraphAnimStep>& events, std::vector<LogicGraph>& treeSnapshots);
	// // Return the last inserted vertex with isEndOfWord = true
	// LogicGraphVertex* generateInsertEvents(std::string word, 
	// 	std::vector<GraphAnimStep>& events, std::vector<LogicGraph>& treeSnapshots);
	// void generateDeleteEvents(std::string word, 
	// 	std::vector<GraphAnimStep>& events, std::vector<LogicGraph>& treeSnapshots);


protected:
	unsigned int numVertex = 0;


	// void clear(LogicGraphVertex*& vertex);


	// ///// Helper functions for animation events generation
	// LogicGraphVertex* generateDeleteEventsHelper(LogicGraphVertex*& vertex, std::string word, int depth, 
	// 	std::vector<GraphAnimStep>& events, std::vector<LogicGraph>& treeSnapshots);

	// void setSnapshotReminder(GraphAnimType animType, std::string desc);
	// void clearSnapshotReminder();


	///// Helper functions (other)
	// LogicGraphVertex* copyTree(const LogicGraphVertex* vertex); // Return copy of tree

	// unsigned int getSizeHelper(LogicGraphVertex* vertex);
	// void         countLeafHelper(LogicGraphVertex* vertex, unsigned int& totalCnt);
	// // Get vertex, knowing the ID (helper function)
	// LogicGraphVertex* getVertexIDHelper(int ID, LogicGraphVertex* vertex);
};
