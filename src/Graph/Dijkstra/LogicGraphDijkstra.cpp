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
	// graphSnapshots.push_back(logicVerticesSnapshot());
	// events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Looking at node step 1", {}, 0, -1, graphSnapshots.size() - 1));
	// events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Looking at node step 2", {}, 1, -1, graphSnapshots.size() - 1));
	// events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Looking at node step 3", {}, 2, -1, graphSnapshots.size() - 1));

	std::priority_queue<LogicGraphVertexDijkstra, std::vector<LogicGraphVertexDijkstra>, std::greater<LogicGraphVertexDijkstra>>
		pqueue;
	std::vector<LogicGraphVertexDijkstra> dijkstraVertices;
	dijkstraVertices = logicVertices;
	dijkstraVertices[startVertex].cost = 0;

	pqueue.push(dijkstraVertices[startVertex]);

	graphSnapshots.push_back(dijkstraVertices);
	events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Cost of vertex " + std::to_string(startVertex) + " is 0", {3,4}, 
		startVertex, -1, graphSnapshots.size() - 1));
	events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Pushing vertex " + std::to_string(startVertex) + " into priority queue", {5}, 
		startVertex, -1, graphSnapshots.size() - 1));

	while (!pqueue.empty()) {
		LogicGraphVertexDijkstra cheapestVertex(pqueue.top());
		pqueue.pop();

		int cheapestVertexID = cheapestVertex.getID();
		if (cheapestVertex.cost > dijkstraVertices[cheapestVertexID].cost) {
			// events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Found outdated vertex in the priority queue: " + std::to_string(cheapestVertexID), {6,8,9}, 
			// 	cheapestVertexID, -1, graphSnapshots.size() - 1));
			continue;
		}

		events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Current cheapest unvisited vertex in the priority queue: " + std::to_string(cheapestVertexID), {6,7}, 
			cheapestVertexID, -1, graphSnapshots.size() - 1));
		events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Popping cheapest unvisited vertex from the priority queue: " + std::to_string(cheapestVertexID), {6,8}, 
			cheapestVertexID, -1, graphSnapshots.size() - 1));

		dijkstraVertices[cheapestVertexID].visited = true;

		graphSnapshots.push_back(dijkstraVertices);
		events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_NODE, "Marking vertex " + std::to_string(cheapestVertexID) + " as visited", {6,8}, 
			cheapestVertexID, -1, graphSnapshots.size() - 1));

		for (const auto& [to, weight] : adjList[cheapestVertexID]) {
			if (dijkstraVertices[cheapestVertexID].cost + weight < dijkstraVertices[to].cost) {
				dijkstraVertices[to].cost = dijkstraVertices[cheapestVertexID].cost + weight;

				graphSnapshots.push_back(dijkstraVertices);
				events.push_back(DijkstraAnimStep(DijkstraAnimType::UPDATE_NEIGHBOR, "Update cost of neighbor " + std::to_string(to) + " of vertex " + std::to_string(cheapestVertexID), {6,11,12,13}, 
					cheapestVertexID, to, graphSnapshots.size() - 1));

				dijkstraVertices[to].prevVertex = cheapestVertexID;

				graphSnapshots.push_back(dijkstraVertices);
				events.push_back(DijkstraAnimStep(DijkstraAnimType::UPDATE_NEIGHBOR, "Update \"previous vertex\" of neighbor " + std::to_string(to) + " of vertex " + std::to_string(cheapestVertexID), {6,11,12,14}, 
					cheapestVertexID, to, graphSnapshots.size() - 1));

				pqueue.push(dijkstraVertices[to]);

				events.push_back(DijkstraAnimStep(DijkstraAnimType::UPDATE_NEIGHBOR, "Pushing neighbor " + std::to_string(to) + " of vertex " + std::to_string(cheapestVertexID) + " into priority queue", {6,11,12,15}, 
					cheapestVertexID, to, graphSnapshots.size() - 1));
			}
		}
	}

	graphSnapshots.push_back(dijkstraVertices);
	events.push_back(DijkstraAnimStep(DijkstraAnimType::FINISHED_DIJKSTRA, "Finished Dijkstra\'s algorithm, right click on a vertex to see shortest path.", {16}, 
		-1, -1, graphSnapshots.size() - 1));
}
