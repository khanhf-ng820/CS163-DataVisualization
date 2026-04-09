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











std::vector<LogicGraphVertexDijkstra> LogicGraphDijkstra::logicVerticesSnapshot() const {
	return logicVertices;
}





void LogicGraphDijkstra::generateDijkstraEvents(int startVertex, std::vector<DijkstraAnimStep>& events, 
	std::vector<std::vector<LogicGraphVertexDijkstra>>& graphSnapshots) {
	graphSnapshots.push_back(logicVerticesSnapshot());
	// events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Looking at node step 1", {}, 0, -1, graphSnapshots.size() - 1));
	// events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Looking at node step 2", {}, 1, -1, graphSnapshots.size() - 1));
	// events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Looking at node step 3", {}, 2, -1, graphSnapshots.size() - 1));

	std::priority_queue<LogicGraphVertexDijkstra> pqueue;
	std::vector<LogicGraphVertexDijkstra> dijkstraVertices;
	dijkstraVertices = logicVertices;
	dijkstraVertices[startVertex].cost = 0;

	graphSnapshots.push_back(dijkstraVertices);
	pqueue.push(dijkstraVertices[startVertex]);
	events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Cost of vertex " + std::to_string(startVertex) + " is 0", {}, startVertex, -1, graphSnapshots.size() - 1));

	while (!pqueue.empty()) {
		LogicGraphVertexDijkstra cheapestVertex(pqueue.top());
		pqueue.pop();

		int cheapestVertexID = cheapestVertex.getID();
		if (cheapestVertex.cost > dijkstraVertices[cheapestVertexID].cost) continue;

		events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Current cheapest vertex in the priority queue: " + std::to_string(cheapestVertexID), {}, cheapestVertexID, -1, graphSnapshots.size() - 1));

		for (const auto& [to, weight] : adjList[cheapestVertexID]) {
			if (dijkstraVertices[cheapestVertexID].cost + weight < dijkstraVertices[to].cost) {
				dijkstraVertices[to].cost = dijkstraVertices[cheapestVertexID].cost + weight;
				dijkstraVertices[to].prevVertex = cheapestVertexID;
				pqueue.push(dijkstraVertices[to]);

				graphSnapshots.push_back(dijkstraVertices);
				events.push_back(DijkstraAnimStep(DijkstraAnimType::UPDATE_NEIGHBOR, "Update neighbor " + std::to_string(to) + " of vertex " + std::to_string(cheapestVertexID), {}, cheapestVertexID, to, graphSnapshots.size() - 1));
			}
		}
	}

	graphSnapshots.push_back(dijkstraVertices);
	events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_UPDATED_NODE, "Looking at node step 5 finish", {}, startVertex, -1, graphSnapshots.size() - 1));
}
