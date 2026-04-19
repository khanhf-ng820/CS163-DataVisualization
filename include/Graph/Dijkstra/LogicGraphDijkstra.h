#pragma once
#include "Graph/LogicGraph.h"
#include "Graph/Dijkstra/LogicGraphVertexDijkstra.h"
#include "Graph/Dijkstra/DijkstraAnimStep.h"

#include <queue>





///// GRAPH REPRESENTED AS ADJACENCY LIST
class LogicGraphDijkstra : public LogicGraph {
public:
	explicit LogicGraphDijkstra(unsigned int numVertex);
	explicit LogicGraphDijkstra(std::mt19937& rng);
	explicit LogicGraphDijkstra(std::vector<std::vector<int>>& adjMatrix);
	explicit LogicGraphDijkstra(std::vector<std::vector<Edge>>& adjList);
	explicit LogicGraphDijkstra(unsigned int numVertex, std::vector<GraphReader::GraphEdge>& edgeList);
	// LogicGraphDijkstra(const LogicGraphDijkstra& other); // Copy constructor

	// LogicGraphDijkstra& operator=(const LogicGraphDijkstra& other); // Assignment op


	std::vector<LogicGraphVertexDijkstra> logicVertices;

	// // Get vertex, knowing the ID
	// LogicGraphVertexDijkstra* getVertexID(int ID);
	// // Check if word exists (plain version of generateSearchEvents)
	// bool wordExists(std::string word);
	// Return snapshot of graph (only the vertices)
	std::vector<LogicGraphVertexDijkstra> logicVerticesSnapshot() const;



	///// ANIMATION EVENTS
	void generateDijkstraEvents(int startVertex, std::vector<DijkstraAnimStep>& events, 
		std::vector<std::vector<LogicGraphVertexDijkstra>>& graphSnapshots);
	// // Returns bool whether word exists or not
	// bool generateSearchEvents(std::string word, 
	// 	std::vector<DijkstraAnimStep>& events, std::vector<LogicGraphDijkstra>& graphSnapshots);
	// // Return the last inserted vertex with isEndOfWord = true
	// LogicGraphVertexDijkstra* generateInsertEvents(std::string word, 
	// 	std::vector<DijkstraAnimStep>& events, std::vector<LogicGraphDijkstra>& graphSnapshots);
	// void generateDeleteEvents(std::string word, 
	// 	std::vector<DijkstraAnimStep>& events, std::vector<LogicGraphDijkstra>& graphSnapshots);


private:
	// void clear(LogicGraphVertex*& vertex);


	// ///// Helper functions for animation events generation
	// LogicGraphVertex* generateDeleteEventsHelper(LogicGraphVertex*& vertex, std::string word, int depth, 
	// 	std::vector<DijkstraAnimStep>& events, std::vector<LogicGraph>& graphSnapshots);

	// void setSnapshotReminder(GraphAnimType animType, std::string desc);
	// void clearSnapshotReminder();


	///// Helper functions (other)
	// LogicGraphVertex* copyTree(const LogicGraphVertex* vertex); // Return copy of graph

	// unsigned int getSizeHelper(LogicGraphVertex* vertex);
	// void         countLeafHelper(LogicGraphVertex* vertex, unsigned int& totalCnt);
	// // Get vertex, knowing the ID (helper function)
	// LogicGraphVertex* getVertexIDHelper(int ID, LogicGraphVertex* vertex);
};
