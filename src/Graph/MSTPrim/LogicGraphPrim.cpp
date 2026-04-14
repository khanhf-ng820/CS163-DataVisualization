#include "Graph/MSTPrim/LogicGraphPrim.h"




LogicGraphPrim::LogicGraphPrim(unsigned int numVertex)
	: LogicGraph(numVertex), logicVertices(numVertex)
{
	for (int i = 0; i < numVertex; i++) {
		logicVertices[i] = LogicGraphVertexPrim(i);
	}
	// ///// FOR TESTING ONLY, WILL DELETE LATER /////
	// this->adjList = {
	// 	{{1,6}, {2,10}},                         // 0
	// 	{{0,6}, {2,12}, {3,11}, {4,14}},         // 1
	// 	{{0,10}, {1,12}, {3,12}, {6,8}, {7,16}}, // 2
	// 	{{1,11}, {2,12}, {5,6}, {6,3}},          // 3
	// 	{{1,14}, {5,4}, {8,6}},                  // 4
	// 	{{3,6}, {4,4}, {8,12}},                  // 5
	// 	{{2,8}, {3,3}, {8,16}, {9,6}},           // 6
	// 	{{2,16}, {9,8}},                         // 7
	// 	{{4,6}, {5,12}, {6,16}, {9,13}},         // 8
	// 	{{6,6}, {7,8}, {8,13}}                   // 9
	// };
}



LogicGraphPrim::LogicGraphPrim(std::mt19937& rng)
	: LogicGraph(rng)
{
	for (int i = 0; i < numVertex; i++) {
		logicVertices.push_back(LogicGraphVertexPrim(i));
	}
	// ///// FOR TESTING ONLY, WILL DELETE LATER /////
	// this->adjList = {
	// 	{{1,6}, {2,10}},                         // 0
	// 	{{0,6}, {2,12}, {3,11}, {4,14}},         // 1
	// 	{{0,10}, {1,12}, {3,12}, {6,8}, {7,16}}, // 2
	// 	{{1,11}, {2,12}, {5,6}, {6,3}},          // 3
	// 	{{1,14}, {5,4}, {8,6}},                  // 4
	// 	{{3,6}, {4,4}, {8,12}},                  // 5
	// 	{{2,8}, {3,3}, {8,16}, {9,6}},           // 6
	// 	{{2,16}, {9,8}},                         // 7
	// 	{{4,6}, {5,12}, {6,16}, {9,13}},         // 8
	// 	{{6,6}, {7,8}, {8,13}}                   // 9
	// };
}



LogicGraphPrim::LogicGraphPrim(std::vector<std::vector<int>>& adjMatrix)
	: LogicGraph(adjMatrix), logicVertices(adjMatrix.size())
{
	for (int i = 0; i < numVertex; i++) {
		logicVertices[i] = LogicGraphVertexPrim(i);
	}
	// ///// FOR TESTING ONLY, WILL DELETE LATER /////
	// this->adjList = {
	// 	{{1,6}, {2,10}},                         // 0
	// 	{{0,6}, {2,12}, {3,11}, {4,14}},         // 1
	// 	{{0,10}, {1,12}, {3,12}, {6,8}, {7,16}}, // 2
	// 	{{1,11}, {2,12}, {5,6}, {6,3}},          // 3
	// 	{{1,14}, {5,4}, {8,6}},                  // 4
	// 	{{3,6}, {4,4}, {8,12}},                  // 5
	// 	{{2,8}, {3,3}, {8,16}, {9,6}},           // 6
	// 	{{2,16}, {9,8}},                         // 7
	// 	{{4,6}, {5,12}, {6,16}, {9,13}},         // 8
	// 	{{6,6}, {7,8}, {8,13}}                   // 9
	// };
}



LogicGraphPrim::LogicGraphPrim(std::vector<std::vector<Edge>>& adjList)
	: LogicGraph(adjList), logicVertices(adjList.size())
{
	for (int i = 0; i < adjList.size(); i++) {
		logicVertices[i] = LogicGraphVertexPrim(i);
	}
	// ///// FOR TESTING ONLY, WILL DELETE LATER /////
	// this->adjList = {
	// 	{{1,6}, {2,10}},                         // 0
	// 	{{0,6}, {2,12}, {3,11}, {4,14}},         // 1
	// 	{{0,10}, {1,12}, {3,12}, {6,8}, {7,16}}, // 2
	// 	{{1,11}, {2,12}, {5,6}, {6,3}},          // 3
	// 	{{1,14}, {5,4}, {8,6}},                  // 4
	// 	{{3,6}, {4,4}, {8,12}},                  // 5
	// 	{{2,8}, {3,3}, {8,16}, {9,6}},           // 6
	// 	{{2,16}, {9,8}},                         // 7
	// 	{{4,6}, {5,12}, {6,16}, {9,13}},         // 8
	// 	{{6,6}, {7,8}, {8,13}}                   // 9
	// };
}



LogicGraphPrim::LogicGraphPrim(unsigned int numVertex, std::vector<GraphReader::GraphEdge>& edgeList)
	: LogicGraph(numVertex, edgeList), logicVertices(numVertex)
{
	for (int i = 0; i < numVertex; i++) {
		logicVertices[i] = LogicGraphVertexPrim(i);
	}
	// ///// FOR TESTING ONLY, WILL DELETE LATER /////
	// this->adjList = {
	// 	{{1,6}, {2,10}},                         // 0
	// 	{{0,6}, {2,12}, {3,11}, {4,14}},         // 1
	// 	{{0,10}, {1,12}, {3,12}, {6,8}, {7,16}}, // 2
	// 	{{1,11}, {2,12}, {5,6}, {6,3}},          // 3
	// 	{{1,14}, {5,4}, {8,6}},                  // 4
	// 	{{3,6}, {4,4}, {8,12}},                  // 5
	// 	{{2,8}, {3,3}, {8,16}, {9,6}},           // 6
	// 	{{2,16}, {9,8}},                         // 7
	// 	{{4,6}, {5,12}, {6,16}, {9,13}},         // 8
	// 	{{6,6}, {7,8}, {8,13}}                   // 9
	// };
}











std::vector<LogicGraphVertexPrim> LogicGraphPrim::logicVerticesSnapshot() const {
	return logicVertices;
}



unsigned int LogicGraphPrim::edgeSumMST(std::vector<LogicGraphVertexPrim>& graphSnapshot) const {
	unsigned int edgeSum = 0;
	for (int i = 0; i < logicVertices.size(); i++) {
		if (graphSnapshot[i].parentVertex >= 0 && graphSnapshot[i].parentVertex < logicVertices.size()) {
			unsigned int edgeWeight = 0;
			for (const auto& [to, weight] : adjList[i]) {
				if (to == graphSnapshot[i].parentVertex) {
					edgeWeight = weight;
					break;
				}
			}
			edgeSum += edgeWeight;
		}
	}
	return edgeSum;
}





void LogicGraphPrim::generatePrimEvents(int startVertex, std::vector<PrimAnimStep>& events, 
	std::vector<std::vector<LogicGraphVertexPrim>>& graphSnapshots) {
	// graphSnapshots.push_back(logicVerticesSnapshot());
	// events.push_back(PrimAnimStep(PrimAnimType::HIGHLIGHT_NODE, "Looking at node step 1", {}, 0, -1, graphSnapshots.size() - 1));
	// events.push_back(PrimAnimStep(PrimAnimType::HIGHLIGHT_NODE, "Looking at node step 2", {}, 1, -1, graphSnapshots.size() - 1));
	// events.push_back(PrimAnimStep(PrimAnimType::HIGHLIGHT_NODE, "Looking at node step 3", {}, 2, -1, graphSnapshots.size() - 1));

	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pqueue;
	std::vector<LogicGraphVertexPrim> primVertices;
	primVertices = logicVertices;
	primVertices[startVertex].cost = 0;

	// pqueue.push(primVertices[startVertex]);
	pqueue.push(Edge(startVertex, primVertices[startVertex].cost));

	graphSnapshots.push_back(primVertices);
	events.push_back(PrimAnimStep(PrimAnimType::HIGHLIGHT_NODE, "Cost of vertex " + std::to_string(startVertex) + " is 0", {5}, 
		startVertex, -1, graphSnapshots.size() - 1));
	events.push_back(PrimAnimStep(PrimAnimType::HIGHLIGHT_NODE, "Pushing vertex " + std::to_string(startVertex) + " into priority queue", {6,7}, 
		startVertex, -1, graphSnapshots.size() - 1));

	while (!pqueue.empty()) {
		Edge cheapestEdge = pqueue.top();
		int cheapestVertex = cheapestEdge.to;
		int cheapestWeight = cheapestEdge.weight;
		pqueue.pop();

		if (primVertices[cheapestVertex].visited) {
			// events.push_back(PrimAnimStep(PrimAnimType::HIGHLIGHT_NODE, "Found already visited vertex in the priority queue: " + std::to_string(cheapestVertex), {8,10,11}, 
			// 	cheapestVertex, -1, graphSnapshots.size() - 1));
			continue;
		}

		events.push_back(PrimAnimStep(PrimAnimType::HIGHLIGHT_NODE, "Current cheapest unvisited vertex in the priority queue: " + std::to_string(cheapestVertex), {8,9}, 
			cheapestVertex, -1, graphSnapshots.size() - 1));
		events.push_back(PrimAnimStep(PrimAnimType::HIGHLIGHT_NODE, "Popping cheapest unvisited vertex from the priority queue: " + std::to_string(cheapestVertex), {8,9}, 
			cheapestVertex, -1, graphSnapshots.size() - 1));

		primVertices[cheapestVertex].visited = true;

		graphSnapshots.push_back(primVertices);
		events.push_back(PrimAnimStep(PrimAnimType::HIGHLIGHT_NODE, "Marking vertex " + std::to_string(cheapestVertex) + " as visited", {8,12}, 
			cheapestVertex, -1, graphSnapshots.size() - 1));

		for (const auto& [to, weight] : adjList[cheapestVertex]) {
			if (!primVertices[to].visited && weight < primVertices[to].cost) {
				primVertices[to].cost = weight;

				graphSnapshots.push_back(primVertices);
				events.push_back(PrimAnimStep(PrimAnimType::UPDATE_NEIGHBOR, "Update cheapest distance of neighbor " + std::to_string(to) + " of vertex " + std::to_string(cheapestVertex), {8,13,14,15}, 
					cheapestVertex, to, graphSnapshots.size() - 1));

				primVertices[to].parentVertex = cheapestVertex;

				graphSnapshots.push_back(primVertices);
				events.push_back(PrimAnimStep(PrimAnimType::UPDATE_NEIGHBOR, "Update \"previous vertex\" of neighbor " + std::to_string(to) + " of vertex " + std::to_string(cheapestVertex), {8,13,14,16}, 
					cheapestVertex, to, graphSnapshots.size() - 1));

				pqueue.push(Edge(to, primVertices[to].cost));

				events.push_back(PrimAnimStep(PrimAnimType::UPDATE_NEIGHBOR, "Pushing neighbor " + std::to_string(to) + " of vertex " + std::to_string(cheapestVertex) + " into priority queue", {8,13,14,17}, 
					cheapestVertex, to, graphSnapshots.size() - 1));
			}
		}
	}

	graphSnapshots.push_back(primVertices);
	events.push_back(PrimAnimStep(PrimAnimType::NONE, "No vertices left in the priority queue, start creating MST.", {18}, 
		-1, -1, graphSnapshots.size() - 1));


	for (int i = 0; i < primVertices.size(); i++) {
		int parentVertex = primVertices[i].parentVertex;
		if (primVertices[i].parentVertex >= 0 && primVertices[i].parentVertex < primVertices.size()
		&& !primVertices[i].highlightMSTEdge) {
			primVertices[i].highlightMSTEdge = true;

			graphSnapshots.push_back(primVertices);
			events.push_back(PrimAnimStep(PrimAnimType::ADD_EDGE_TO_MST, "Adding the edge between vertex " + std::to_string(i) + " and " + std::to_string(parentVertex) + " into the MST", {19,20,21}, 
				i, parentVertex, graphSnapshots.size() - 1));
		}
	}


	graphSnapshots.push_back(primVertices);
	events.push_back(PrimAnimStep(PrimAnimType::FINISHED_MST_PRIM, "Finished Prim\'s algorithm, the total cost of MST is " + std::to_string(edgeSumMST(primVertices)) + ".", {22}, 
		-1, -1, graphSnapshots.size() - 1));
}
