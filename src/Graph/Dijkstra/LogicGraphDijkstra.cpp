#include "Graph/Dijkstra/LogicGraphDijkstra.h"




LogicGraphDijkstra::LogicGraphDijkstra(unsigned int numVertex)
	: LogicGraph(numVertex), logicVertices(numVertex)
{
	for (int i = 0; i < numVertex; i++) {
		logicVertices[i] = LogicGraphVertexDijkstra(i);
	}
	///// FOR TESTING ONLY, WILL DELETE LATER /////
	this->adjList = {
        {{1,6}, {2,10}},                         // 0
        {{0,6}, {2,12}, {3,11}, {4,14}},         // 1
        {{0,10}, {1,12}, {3,12}, {6,8}, {7,16}}, // 2
        {{1,11}, {2,12}, {5,6}, {6,3}},          // 3
        {{1,14}, {5,4}, {8,6}},                  // 4
        {{3,6}, {4,4}, {8,12}},                  // 5
        {{2,8}, {3,3}, {8,16}, {9,6}},           // 6
        {{2,16}, {9,8}},                         // 7
        {{4,6}, {5,12}, {6,16}, {9,13}},         // 8
        {{6,6}, {7,8}, {8,13}}                   // 9
    };
}

LogicGraphDijkstra::LogicGraphDijkstra(std::vector<std::vector<Edge>>& adjList)
	: LogicGraph(adjList), logicVertices(adjList.size())
{
	for (int i = 0; i < adjList.size(); i++) {
		logicVertices[i] = LogicGraphVertexDijkstra(i);
	}
	///// FOR TESTING ONLY, WILL DELETE LATER /////
	this->adjList = {
        {{1,6}, {2,10}},                         // 0
        {{0,6}, {2,12}, {3,11}, {4,14}},         // 1
        {{0,10}, {1,12}, {3,12}, {6,8}, {7,16}}, // 2
        {{1,11}, {2,12}, {5,6}, {6,3}},          // 3
        {{1,14}, {5,4}, {8,6}},                  // 4
        {{3,6}, {4,4}, {8,12}},                  // 5
        {{2,8}, {3,3}, {8,16}, {9,6}},           // 6
        {{2,16}, {9,8}},                         // 7
        {{4,6}, {5,12}, {6,16}, {9,13}},         // 8
        {{6,6}, {7,8}, {8,13}}                   // 9
    };
}











void LogicGraphDijkstra::generateDijkstraEvents(int startVertex, 
	std::vector<DijkstraAnimStep>& events, std::vector<LogicGraphDijkstra>& treeSnapshots) {
	// LogicDijkstraNode* node = root;
	// events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Looking at root node", {}, root->getID()));

	// for (const char& c : word) {
	// 	if (node->getChild(c) == nullptr) {
	// 		events.push_back(DijkstraAnimStep(DijkstraAnimType::NONE, "Child \'" + std::string(1, c) + "\' does not exist. Word does not exist.", {}, node->getID()));
	// 		return false;
	// 	}

	// 	if (node != root) {
	// 		events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Looking at node \'" + std::string(1, node->key) + "\'", {}, node->getID()));
	// 	}
	// 	events.push_back(DijkstraAnimStep(DijkstraAnimType::MOVE_HIGHLIGHT_DOWN, "Going down to \'" + std::string(1, c) + "\' child", {}, node->getID()));
	// 	events.back().charLink = c;

	// 	node = node->getChild(c);
	// }

	// if (node->isEndOfWord) {
	// 	events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_FOUND_NODE, "Found node \'" + std::string(1, node->key) + "\', reached end of string, isEndOfWord is true. Word found.", {}, node->getID()));
	// } else {
	// 	events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Found node \'" + std::string(1, node->key) + "\', reached end of string, isEndOfWord is false. Word does not exist.", {}, node->getID()));
	// }
	events.push_back(DijkstraAnimStep(DijkstraAnimType::NONE, "Looking at root node step 1", {}, -1, -1, -1));
	events.push_back(DijkstraAnimStep(DijkstraAnimType::NONE, "Looking at root node step 2", {}, -1, -1, -1));
	events.push_back(DijkstraAnimStep(DijkstraAnimType::NONE, "Looking at root node step 3", {}, -1, -1, -1));
	events.push_back(DijkstraAnimStep(DijkstraAnimType::NONE, "Looking at root node step 4", {}, -1, -1, -1));
	events.push_back(DijkstraAnimStep(DijkstraAnimType::NONE, "Looking at root node step 5", {}, -1, -1, -1));
}
