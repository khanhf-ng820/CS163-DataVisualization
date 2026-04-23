#include "Graph/MSTPrim/PrimVisEngine.h"




PrimVisEngine::PrimVisEngine(unsigned int numVertex, sf::RenderWindow* window, sf::Font* font, sf::View* view)
	: windowPtr(window), fontPtr(font), viewPtr(view)
	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
	, graph(numVertex) , visualNodesCur(numVertex)
{
	///// ONLY FOR TESTING, WILL DELETE LATER /////
	for (int i = 0; i < numVertex; i++) {
		visualNodesCur[i] = VisualGraphVertex(i, {cos(3.14f/5*i) * 100.f, sin(3.14f/5*i) * 100.f});
	}
}


PrimVisEngine::PrimVisEngine(std::mt19937& rng, sf::RenderWindow* window, sf::Font* font, sf::View* view)
	: windowPtr(window), fontPtr(font), viewPtr(view)
	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
	, graph(rng) /*, visualNodesCur(numVertex)*/
{
	visualNodesCur = std::vector<VisualGraphVertex>(graph.getNumVertex());

	///// ONLY FOR TESTING, WILL DELETE LATER /////
	for (int i = 0; i < graph.getNumVertex(); i++) {
		visualNodesCur[i] = VisualGraphVertex(i, {cos(3.14f/5*i) * 100.f, sin(3.14f/5*i) * 100.f});
	}
}


PrimVisEngine::PrimVisEngine(std::vector<std::vector<int>>& adjMatrix, 
sf::RenderWindow* window, sf::Font* font, sf::View* view)
	: windowPtr(window), fontPtr(font), viewPtr(view)
	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
	, graph(adjMatrix) , visualNodesCur(adjMatrix.size())
{
	///// ONLY FOR TESTING, WILL DELETE LATER /////
	for (int i = 0; i < graph.getNumVertex(); i++) {
		visualNodesCur[i] = VisualGraphVertex(i, {cos(3.14f/5*i) * 100.f, sin(3.14f/5*i) * 100.f});
	}
}


PrimVisEngine::PrimVisEngine(std::vector<std::vector<Edge>>& adjList, sf::RenderWindow* window, sf::Font* font, sf::View* view)
	: windowPtr(window), fontPtr(font), viewPtr(view)
	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
	, graph(adjList) , visualNodesCur(adjList.size())
{
	///// ONLY FOR TESTING, WILL DELETE LATER /////
	for (int i = 0; i < graph.getNumVertex(); i++) {
		visualNodesCur[i] = VisualGraphVertex(i, {cos(3.14f/5*i) * 100.f, sin(3.14f/5*i) * 100.f});
	}
}


PrimVisEngine::PrimVisEngine(unsigned int numVertex, std::vector<GraphReader::GraphEdge>& edgeList, 
sf::RenderWindow* window, sf::Font* font, sf::View* view)
	: windowPtr(window), fontPtr(font), viewPtr(view)
	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
	, graph(numVertex, edgeList) /*, visualNodesCur(numVertex)*/
{
	visualNodesCur = std::vector<VisualGraphVertex>(graph.getNumVertex());

	///// ONLY FOR TESTING, WILL DELETE LATER /////
	for (int i = 0; i < numVertex; i++) {
		visualNodesCur[i] = VisualGraphVertex(i, {cos(3.14f/5*i) * 100.f, sin(3.14f/5*i) * 100.f});
	}
}




// Reset all properties to get ready for visualize new action
///// MAKE SURE TO RESET ALL NECESSARY PROPERTIES
void PrimVisEngine::resetParams() {
	resetAnimParams();
}






///// --- LOGICAL ALGORITHMS AND EVENTS --- /////
// -- SEARCHING --
std::vector<PrimAnimStep> PrimVisEngine::getEventsPrim(int startVertex) {
	std::vector<PrimAnimStep> events;
	oldGraphSnapshots.clear();
	oldGraphSnapshots.push_back(graph.logicVertices);

	events.push_back(PrimAnimStep(PrimAnimType::NONE, "Before running Prim\'s algorithm with starting vertex: " + std::to_string(startVertex), {1,2,3}, 
		-1, -1, oldGraphSnapshots.size() - 1));
	graph.generatePrimEvents(startVertex, events, oldGraphSnapshots);

	std::cerr << "Done generating Prim events!" << std::endl; // DEBUG
	std::cerr << ", size = " << graph.getNumVertex() << std::endl; // DEBUG

	return events;
}



// // -- INSERTION --
// std::vector<PrimAnimStep> PrimVisEngine::getEventsInsert(std::string word) {
// 	std::vector<PrimAnimStep> events;
// 	oldGraphSnapshots.clear();
// 	oldGraphSnapshots.push_back(graph);

// 	events.push_back(PrimAnimStep(PrimAnimType::NONE, "Before inserting word: \"" + word + "\"", {}, 0, oldGraphSnapshots.size() - 1));
// 	// Insert node into graph and get animation events
// 	LogicPrimNode* lastInsertedNode = graph.generateInsertEvents(word, events, oldGraphSnapshots);
// 	// // Remind to snapshot graph after insertion/rotation
// 	// graph.snapshotGraph(ID, events, oldGraphSnapshots);

// 	events.push_back(PrimAnimStep(PrimAnimType::HIGHLIGHT_UPDATED_NODE, "Finished inserting word: \"" + word + "\"", {}, lastInsertedNode->getID(), -1));

// 	std::cerr << "Done generating insertion events!" << std::endl; // DEBUG
// 	std::cerr << ", size = " << graph.getNumVertex() << std::endl; // DEBUG

// 	return events;
// }



// // -- DELETION --
// std::vector<PrimAnimStep> PrimVisEngine::getEventsDelete(std::string word) {
// 	std::vector<PrimAnimStep> events;
// 	oldGraphSnapshots.clear();
// 	oldGraphSnapshots.push_back(graph);

// 	events.push_back(PrimAnimStep(PrimAnimType::NONE, "Before deleting word: \"" + word + "\"", {}, 0, oldGraphSnapshots.size() -1));
// 	graph.generateDeleteEvents(word, events, oldGraphSnapshots);

// 	std::cerr << "Done generating deletion events!" << std::endl; // DEBUG
// 	std::cerr << ", size = " << graph.getNumVertex() << std::endl; // DEBUG

// 	return events;
// }







// Update positions (based on force-directed graph drawing)
// Fruchterman-Reingold algorithm
void PrimVisEngine::updateNodePositions() {
	unsigned int numVertex = graph.getNumVertex();
	k = sqrt(static_cast<double>(windowPtr->getSize().x * windowPtr->getSize().y) / numVertex);
	for (auto& visVertex : visualNodesCur) {
		visVertex.force = sf::Vector2f(0, 0);
	}

	// Repulsion force
	for (int i = 0; i < numVertex; i++) {
		for (int j = i + 1; j < numVertex; j++) {
			sf::Vector2f delta = visualNodesCur[i].position - visualNodesCur[j].position;
			float d = std::max(0.01f, delta.length());
			float forceMag = (k * k) / d;

			// delta.setMag(forceMag);
			delta = delta.normalized() * forceMag;

			visualNodesCur[i].force += delta;
			visualNodesCur[j].force -= delta;
		}
	}

	// Attraction force
	for (int i = 0; i < numVertex; i++) {
		for (const auto& [to, weight] : graph.adjList[i]) {
			if (to > i) {
				sf::Vector2f delta = visualNodesCur[to].position - visualNodesCur[i].position;
				float d = std::max(0.01f, delta.length());
				float forceMag = (d * d) / k;

				delta = delta.normalized() * forceMag;

				visualNodesCur[i].force += delta;
				visualNodesCur[to].force -= delta;
			}
		}
	}

	// Apply movement
	for (auto& visVertex : visualNodesCur) {
		if (visVertex.getID() != draggedVertexID) {
			sf::Vector2f displacement = visVertex.force * timeStep;
			displacement = limitMag(displacement, temperature);
			visVertex.position += displacement;

			// Small centering force
			sf::Vector2f center = sf::Vector2f(0, 0);
			sf::Vector2f toCenter = (center - visVertex.position) * centerAttractionConstant;
			visVertex.position += toCenter;
		}
	}
}








void PrimVisEngine::getDraggedVertexID(sf::Vector2f mousePos, sf::Vector2f viewDisplacement, float viewZoomFactor) {
	draggedVertexID = -1; // Reset draggedVertexID
	mousePos -= sf::Vector2f(windowPtr->getSize()) / 2.f;

	unsigned int numVertex = graph.getNumVertex();
	for (int i = numVertex - 1; i >= 0; i--) {
		sf::Vector2f visualVertexPos = visualNodesCur[i].position;
		visualVertexPos -= viewDisplacement;
		visualVertexPos /= viewZoomFactor;
		float distanceMouseAndVertex = (visualVertexPos - mousePos).length();
		if (distanceMouseAndVertex < nodeCircleRadius / viewZoomFactor) {
			draggedVertexID = i;
			visualNodesCur[i].position = mousePos * viewZoomFactor + viewDisplacement;
			return;
		}
	}
}


void PrimVisEngine::resetDraggedVertexID() {
	draggedVertexID = -1; // Reset draggedVertexID
}


void PrimVisEngine::dragVertexByMouse(sf::Vector2f mousePos, sf::Vector2f viewDisplacement, float viewZoomFactor) {
	mousePos -= sf::Vector2f(windowPtr->getSize()) / 2.f;

	unsigned int numVertex = graph.getNumVertex();
	if (!(0 <= draggedVertexID && draggedVertexID < numVertex)) return;
	visualNodesCur[draggedVertexID].position = mousePos * viewZoomFactor + viewDisplacement;
}










// Draw nodes: Iterate through graph and draw nodes
// --- NORMAL MODE | RUNNING MST_PRIM MODE ---
void PrimVisEngine::addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, PrimAnimStep eventPrim) {
	// generateAllVisNodePos(visualNodesCur, graph);
	// generateAllVisNodePos(graph);
	size_t numOfOldGraphSnapshots = oldGraphSnapshots.size();

	// Generate all visual nodes, new and old
	// generateAllVisNodePos(graph);
	// for (int i = 0; i < numOfOldGraphSnapshots; i++) {
	// 	generateAllVisNodePos(oldGraphSnapshots[i]);
	// }
	if (visMode == PrimVisMode::MST_PRIM)
		std::cerr << "numOfOldGraphSnapshots = " << numOfOldGraphSnapshots << ", "; // DEBUG

	// Find old visual nodes and old graph snapshot
	std::vector<LogicGraphVertexPrim>& oldGraphSnapshot =
		(eventPrim.oldGraphSnapshotIndex == -1) ? graph.logicVertices : oldGraphSnapshots[eventPrim.oldGraphSnapshotIndex];

	drawStillGraph(drawableList, oldGraphSnapshot);

	// Draw highlighting circle
	switch (eventPrim.type) {
	case PrimAnimType::HIGHLIGHT_NODE:
		drawHighlightCircle(drawableList, visualNodesCur[eventPrim.vertexID].position, false);
		break;
	case PrimAnimType::HIGHLIGHT_UPDATED_NODE:
		drawHighlightCircle(drawableList, visualNodesCur[eventPrim.vertexID].position, true);
		break;
	case PrimAnimType::UPDATE_NEIGHBOR:
		drawHighlightCircle(drawableList, visualNodesCur[eventPrim.vertexID].position, false);
		drawHighlightEdge(drawableList, visualNodesCur[eventPrim.vertexID].position, visualNodesCur[eventPrim.toVertexID].position, false);
		drawHighlightCircle(drawableList, visualNodesCur[eventPrim.toVertexID].position, true);
		break;
	case PrimAnimType::ADD_EDGE_TO_MST:
		drawHighlightCircle(drawableList, visualNodesCur[eventPrim.vertexID].position, false);
		drawHighlightCircle(drawableList, visualNodesCur[eventPrim.toVertexID].position, false);
		break;
	// case PrimAnimType::MOVE_HIGHLIGHT_DOWN:
	// 	if (graph.getNodeID(eventPrim.vertexID) && graph.getNodeID(eventPrim.vertexID)->getChild(eventPrim.charLink))
	// 		drawHighlightCircle(drawableList,
	// 			easeInOutLerp(visualNodesCur[eventPrim.vertexID].position, 
	// 						  visualNodesCur[graph.getNodeID(eventPrim.vertexID)->getChild(eventPrim.charLink)->getID()].position, 
	// 						  fract(time)),
	// 			false);
	// 	else
	// 		drawHighlightCircle(drawableList, visualNodesCur[eventPrim.vertexID].position, false);
	// 	break;
	case PrimAnimType::NONE:
	default:
		break;
	}
}










// // Create AND display ImGui window to highlight source code (pseudocode)
void PrimVisEngine::drawPseudocodeWindow(PrimAnimStep eventPrim) {
	ImGui::Begin("Pseudocode", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::PushFont(pseudocodeFont);

	switch (visMode) {
	case PrimVisMode::MST_PRIM:
		for (int i = 0; i < MST_PRIM_PSEUDOCODE.size(); i++) {
			bool highlightLine = vecContains(eventPrim.highlightCodeLineIndex, i);
			if (highlightLine)
				ImGui::PushStyleColor(ImGuiCol_Text, highlightCodeColor);
			ImGui::Text("%s", MST_PRIM_PSEUDOCODE[i].c_str());
			if (highlightLine)
				ImGui::PopStyleColor();
		}
		break;
	default:
		ImGui::Text("(Nothing to visualize.)");
		break;
	}

	ImGui::PopFont();
	ImGui::End();
}


std::string PrimVisEngine::getShortestPathString(int startVertex, int endVertex) {
	std::vector<int> path;
	int currentVertex = endVertex;
	while (currentVertex >= 0) {
		path.push_back(currentVertex);
		currentVertex = oldGraphSnapshots.back()[currentVertex].parentVertex;
	}
	std::reverse(path.begin(), path.end());

	if (oldGraphSnapshots.back()[endVertex].parentVertex == -1 && startVertex != endVertex) {
		return "No path from vertex " + std::to_string(startVertexID) + " to vertex " + std::to_string(endVertex) + "exists.";
	}
	std::string shortestPathString = "Shortest path from vertex " + std::to_string(startVertexID) + " to vertex " + std::to_string(endVertex) + ":\n";

	for (int i = 0; i < path.size(); i++) {
		shortestPathString += std::to_string(path[i]);
		if (i < static_cast<int>(path.size()) - 1)
			shortestPathString += ", ";
		else
			shortestPathString += ".";
	}
	return shortestPathString;
}










// Draw nodes and links, depending on eventList
void PrimVisEngine::createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::vector<std::unique_ptr<sf::Drawable>>& drawableListDefaultView) {
	refreshOriginPos(); // Refresh properties when window size changes
	drawableList.clear();
	drawableListDefaultView.clear();


	// If STILL mode, stop here
	if (eventList.size() <= 1) {
		// Update vertex positions due to forces
		updateNodePositions();
		// Display nodes: Iterate through graph and draw nodes
		addNodeDrawables(drawableList, PrimAnimStep());
		return;
	}


	// change visCur and visCurIndex
	animStepIndex = std::min(static_cast<int>(floor(time)), static_cast<int>(eventList.size()) - 1);
	time = std::min(std::max(time, 0.f), static_cast<float>(eventList.size()) - 0.0005f);
	PrimAnimStep eventPrim = eventList[animStepIndex];
	// if (time == static_cast<float>(eventList.size())) eventPrim = eventList.back();
	// Set parameters
	// searchSlotIdx = eventPrim.searchSlotIdx; // Set searchSlotIdx in the event
	// Less safe: animInProgress = (time != static_cast<float>(eventList.size()) - 0.0005f);
	animInProgress = (abs(time - (static_cast<float>(eventList.size()) - 0.0005f)) > EPSILON_TIME);

	if (animStepIndex > oldAnimStepIndex) {
		// if (eventList[oldAnimStepIndex].type == PrimAnimType::MOVE_CUR_FORWARD) {
		// 	visCurIndex++;
		// 	visCur = visCur->pNext;
		// }
		oldAnimStepIndex = animStepIndex;
	}



	
	// MST_PRIM MODE
	// Update vertex positions due to forces
	updateNodePositions();
	// Display nodes: Iterate through graph and draw nodes
	addNodeDrawables(drawableList, eventPrim);
	drawPseudocodeWindow(eventPrim);




	// Display description for algorithm visualization
	auto descriptionText = std::make_unique<sf::Text>(*fontPtr, eventPrim.description, descriptionFontSize);
	descriptionText->setFillColor(normalNodeColor);
	descriptionText->setPosition(descriptionTextPos);
	descriptionText->setPosition(round(descriptionText->getPosition()));

	drawableListDefaultView.push_back(std::move(descriptionText));


	std::cout << drawableList.size() << ' ' << time << " init done" << std::endl; // DEBUG
}












// Set correct positions for ALL VISUAL nodes
// Uses inorder positioning
void PrimVisEngine::generateAllVisNodePos(LogicGraphPrim& logicGraph) {
	// generateAllVisNodePosHelper(visualNodesCur, logicGraph, logicGraph.root);
	visualNodesCur.clear();
	unsigned int numVertex = logicGraph.getNumVertex();
	// float xPos = canvasLeftMargin;
	// float dx = (windowPtr->getSize().x - 2 * canvasLeftMargin) / (size > 1 ? size-1 : 1);
	// // Prevent nodes overlapping
	// if (dx < 2 * nodeCircleRadius) dx = 2 * nodeCircleRadius;

	// generateRecursiveVisNodePos(visualNodesCur, root, xPos, dx);
	// for (int i = 0; i < numVertex; i++) {
	// }
}





///// --- DRAWING FUNCTIONS ---
// Draw a node (a circle with the ID as text inside it)
void PrimVisEngine::drawNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, 
	const VisualGraphVertex& visVertex, const std::vector<LogicGraphVertexPrim>& graphSnapshot) {
	// Draw circle
	auto nodeCircle = std::make_unique<sf::CircleShape>(nodeCircleRadius);
	nodeCircle->setOrigin({nodeCircle->getRadius(), nodeCircle->getRadius()}); 
	nodeCircle->setFillColor((draggedVertexID == visVertex.getID()) 
		? draggedNodeColor 
		: (graphSnapshot[visVertex.getID()].visited ? visitedNodeColor : sf::Color::Transparent));
	nodeCircle->setOutlineColor(normalNodeColor);
	nodeCircle->setOutlineThickness(nodeOutlineThickness);
	nodeCircle->setPosition(visVertex.position);
	// Draw ID text
	auto nodeIDText = std::make_unique<sf::Text>(*fontPtr, std::to_string(visVertex.getID()), nodeIDTextFontSize);
	sf::FloatRect localBounds = nodeIDText->getLocalBounds();
	nodeIDText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	nodeIDText->setFillColor(normalNodeKeyColor);
	nodeIDText->setPosition(nodeCircle->getPosition());
	nodeIDText->setPosition(round(nodeIDText->getPosition()));
	// Draw cost text
	auto nodeCostText = std::make_unique<sf::Text>(*fontPtr, 
		graphSnapshot[visVertex.getID()].cost == INT_MAX ? "INF" : std::to_string(graphSnapshot[visVertex.getID()].cost), 
		nodeInfoTextFontSize
	);
	localBounds = nodeCostText->getLocalBounds();
	nodeCostText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	nodeCostText->setFillColor(nodeInfoTextColor);
	nodeCostText->setPosition(nodeCircle->getPosition() + sf::Vector2f(0, -nodeCircleRadius) * 0.6f);
	nodeCostText->setPosition(round(nodeCostText->getPosition()));
	// Draw previous vertex text
	auto nodePrevVertText = std::make_unique<sf::Text>(*fontPtr, 
		graphSnapshot[visVertex.getID()].parentVertex == -1 ? "NULL" : std::to_string(graphSnapshot[visVertex.getID()].parentVertex), 
		nodeInfoTextFontSize
	);
	localBounds = nodePrevVertText->getLocalBounds();
	nodePrevVertText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	nodePrevVertText->setFillColor(nodeInfoTextColor);
	nodePrevVertText->setPosition(nodeCircle->getPosition() + sf::Vector2f(0, nodeCircleRadius) * 0.6f);
	nodePrevVertText->setPosition(round(nodePrevVertText->getPosition()));

	drawableList.push_back(std::move(nodeCircle));
	drawableList.push_back(std::move(nodeIDText));
	drawableList.push_back(std::move(nodeCostText));
	drawableList.push_back(std::move(nodePrevVertText));
}


// Draw the highlight circle (a circle highlighting a node)
void PrimVisEngine::drawHighlightCircle(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, 
	sf::Vector2f center, bool isHighlighted) {
	auto highlightCircle = std::make_unique<sf::CircleShape>(nodeCircleRadius + highlightCircleThickness / 2);
	highlightCircle->setOrigin({highlightCircle->getRadius(), highlightCircle->getRadius()}); 
	highlightCircle->setFillColor(sf::Color::Transparent);
	highlightCircle->setOutlineColor(isHighlighted ? highlightCircleColor : highlightFoundCircleColor);
	highlightCircle->setOutlineThickness(highlightCircleThickness);
	highlightCircle->setPosition(center);
	drawableList.push_back(std::move(highlightCircle));
}


// Draw graph edges (arrows)
void PrimVisEngine::drawGraphEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, 
	const std::vector<LogicGraphVertexPrim>& graphSnapshot) {
	unsigned int numVertex = graphSnapshot.size();
	for (int i = 0; i < numVertex; i++) {
		for (const auto& [to, weight] : graph.adjList[i]) {
			if (i > to) continue; // Don't draw twice
			sf::Vector2f start = visualNodesCur[i].position, end = visualNodesCur[to].position;

			drawEdgeLine(drawableList, start, end);

			drawEdgeWeightText(drawableList, start, end, weight);
		}
	}
}


void PrimVisEngine::drawStillGraph(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, 
	const std::vector<LogicGraphVertexPrim>& graphSnapshot) {
	drawGraphEdges(drawableList, graphSnapshot);
	unsigned int numVertex = graphSnapshot.size();
	// Draw nodes
	for (int ID = 0; ID < numVertex; ID++) {
		drawNode(drawableList, visualNodesCur[ID], graphSnapshot);
	}
	// Drawing MST by highlighting edges
	for (int ID = 0; ID < numVertex; ID++) {
		if (!(0 <= graphSnapshot[ID].parentVertex && graphSnapshot[ID].parentVertex < numVertex)) continue;
		if (!graphSnapshot[ID].highlightMSTEdge) continue;

		int parentVertex = graphSnapshot[ID].parentVertex;
		drawHighlightEdge(drawableList, visualNodesCur[ID].position, visualNodesCur[parentVertex].position, 
			true);
	}
}



// // Draw lerped node
// void PrimVisEngine::drawLerpNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualPrimNode& visVertex1, const VisualPrimNode& visVertex2) {
// 	// Draw circle
// 	auto nodeCircle = std::make_unique<sf::CircleShape>(nodeCircleRadius);
// 	nodeCircle->setOrigin({nodeCircle->getRadius(), nodeCircle->getRadius()}); 
// 	nodeCircle->setFillColor(visVertex1.isEndOfWord ? normalNodeEOW_BGColor : sf::Color::Transparent);
// 	nodeCircle->setOutlineColor(normalNodeColor);
// 	nodeCircle->setOutlineThickness(nodeOutlineThickness);
// 	nodeCircle->setPosition(easeInOutLerp(visVertex1.position, visVertex2.position, fract(time)));
// 	// Draw ID text
// 	auto nodeIDText = std::make_unique<sf::Text>(*fontPtr, std::string(1, visVertex1.ID), nodeIDTextFontSize);
// 	sf::FloatRect localBounds = nodeIDText->getLocalBounds();
// 	nodeIDText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
// 	nodeIDText->setFillColor(normalNodeKeyColor);
// 	nodeIDText->setPosition(nodeCircle->getPosition());
// 	nodeIDText->setPosition(round(nodeIDText->getPosition()));
// 	// // Draw height text
// 	// auto nodeHeightText = std::make_unique<sf::Text>(*fontPtr, std::to_string(visVertex.height), nodeHeightTextFontSize);
// 	// localBounds = nodeHeightText->getLocalBounds();
// 	// nodeHeightText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
// 	// nodeHeightText->setFillColor(normalNodeHeightColor);
// 	// nodeHeightText->setPosition(nodeCircle->getPosition() + sf::Vector2f(nodeCircleRadius, -nodeCircleRadius));
// 	// nodeHeightText->setPosition(round(nodeHeightText->getPosition()));

// 	drawableList.push_back(std::move(nodeCircle));
// 	drawableList.push_back(std::move(nodeIDText));
// 	// drawableList.push_back(std::move(nodeHeightText));
// }

// // Draw lerped graph edges (arrows)
// void PrimVisEngine::drawLerpGraphEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const LogicPrimNode* root,
// 	std::vector<VisualPrimNode>& visualNodes1, std::vector<VisualPrimNode>& visualNodes2) {
// 	if (!root) return;
// 	for (int i = 0; i < MST_PRIM_ALPHABET_SIZE; i++)
// 		drawLerpGraphEdges(drawableList, root->children[i], visualNodes1, visualNodes2);
// 	for (int i = 0; i < MST_PRIM_ALPHABET_SIZE; i++) {
// 		if (!root->children[i]) continue;
// 		sf::Vector2f start = easeInOutLerp(visualNodes1[root->getID()].position, visualNodes2[root->getID()].position, fract(time));
// 		sf::Vector2f end = easeInOutLerp(visualNodes1[root->children[i]->getID()].position, 
// 										 visualNodes2[root->children[i]->getID()].position, 
// 										 fract(time));
// 		drawEdgeLine(drawableList, start, end);
// 	}
// }

// // Draw lerped graph (nodes and edges)
// void PrimVisEngine::drawLerpGraph(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
// 	std::vector<VisualPrimNode>& visualNodes1, LogicPrim& logicGraph1,
// 	std::vector<VisualPrimNode>& visualNodes2, LogicPrim& logicGraph2) {
// 	drawLerpGraphEdges(drawableList, logicGraph2.root, visualNodes1, visualNodes2);
// 	for (const auto& [ID, visVertex2] : visualNodes2) {
// 		drawLerpNode(drawableList, visualNodes1[ID], visVertex2);
// 	}
// }

// // Draw lerped graph when inserting a node
// void PrimVisEngine::drawLerpGraphInsertNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
// 	std::vector<VisualPrimNode>& visualNodes1, LogicPrim& logicGraph1,
// 	std::vector<VisualPrimNode>& visualNodes2, LogicPrim& logicGraph2,
// 	uint64_t nodeInsertID) {
// 	LogicPrim logicGraphBefore = logicGraph2;
// 	std::vector<VisualPrimNode> visualNodesBefore = visualNodes2;
// 	for (const auto& [ID, visVertex1] : visualNodes1) {
// 		visualNodesBefore[ID].position = visVertex1.position;
// 	}
// 	visualNodesBefore[nodeInsertID].position = originPos + newNodeStartPos;
// 	drawLerpGraph(drawableList, visualNodesBefore, logicGraphBefore, visualNodes2, logicGraph2);
// }

// // Draw lerped graph when deleting a node
// void PrimVisEngine::drawLerpGraphDeleteNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
// 	std::vector<VisualPrimNode>& visualNodes1, LogicPrim& logicGraph1,
// 	std::vector<VisualPrimNode>& visualNodes2, LogicPrim& logicGraph2,
// 	uint64_t nodeRemoveID) {
// 	LogicPrim logicGraphBefore = logicGraph2;
// 	std::vector<VisualPrimNode> visualNodesBefore = visualNodes2;
// 	for (const auto& [ID, visVertex1] : visualNodes1) {
// 		if (ID != nodeRemoveID)
// 			visualNodesBefore[ID].position = visVertex1.position;
// 	}
// 	// visualNodesBefore[nodeRemoveID].position = originPos + newNodeStartPos;
// 	drawLerpGraph(drawableList, visualNodesBefore, logicGraphBefore, visualNodes2, logicGraph2);
// }







// Helper drawing functions
void PrimVisEngine::drawEdgeLine(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, 
	sf::Vector2f start, sf::Vector2f end) {
	double radiusAngle = std::atan2(end.y - start.y, end.x - start.x);
	start += sf::Vector2f(nodeCircleRadius * std::cos(radiusAngle), nodeCircleRadius * std::sin(radiusAngle));
	end   -= sf::Vector2f(nodeCircleRadius * std::cos(radiusAngle), nodeCircleRadius * std::sin(radiusAngle));

	float dx = end.x - start.x, dy = end.y - start.y;
	float len = sqrt(dx*dx + dy*dy);
	if (abs(len) < 1e-3) return; // Too small, don't draw

	// float ux = dx / len, uy = dy / len;
	// float px = -uy, py = ux;
	// float height = sqrt(3.0) / 2 * arrowHeadSideLen;
	// float baseCenterX = end.x - height * ux;
	// float baseCenterY = end.y - height * uy;
	// float leftX  = baseCenterX + (arrowHeadSideLen / 2) * px;
	// float leftY  = baseCenterY + (arrowHeadSideLen / 2) * py;
	// float rightX = baseCenterX - (arrowHeadSideLen / 2) * px;
	// float rightY = baseCenterY - (arrowHeadSideLen / 2) * py;

	auto arrowBody = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Lines, 2);
	(*arrowBody)[0].position = start;
	(*arrowBody)[0].color = normalNodeColor;
	(*arrowBody)[1].position = end;
	(*arrowBody)[1].color = normalNodeColor;

	// auto arrowHead = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Triangles, 3);
	// (*arrowHead)[0].position = end;
	// (*arrowHead)[0].color = normalNodeColor;
	// (*arrowHead)[1].position = sf::Vector2f(leftX, leftY);
	// (*arrowHead)[1].color = normalNodeColor;
	// (*arrowHead)[2].position = sf::Vector2f(rightX, rightY);
	// (*arrowHead)[2].color = normalNodeColor;

	drawableList.push_back(std::move(arrowBody));
	// drawableList.push_back(std::move(arrowHead));
}


void PrimVisEngine::drawEdgeWeightText(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f start, sf::Vector2f end, int weight) {
	double radiusAngle = std::atan2(end.y - start.y, end.x - start.x);
	start += sf::Vector2f(nodeCircleRadius * std::cos(radiusAngle), nodeCircleRadius * std::sin(radiusAngle));
	end   -= sf::Vector2f(nodeCircleRadius * std::cos(radiusAngle), nodeCircleRadius * std::sin(radiusAngle));
	if (radiusAngle > PI_CONST / 2) radiusAngle -= PI_CONST;
	else if (radiusAngle < -PI_CONST / 2) radiusAngle += PI_CONST;

	// Draw edge weight text
	auto edgeWeightText = std::make_unique<sf::Text>(*fontPtr, std::to_string(weight), edgeWeightTextFontSize);
	sf::FloatRect localBounds = edgeWeightText->getLocalBounds();
	edgeWeightText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	edgeWeightText->setFillColor(weightTextColor);
	edgeWeightText->setRotation(sf::radians(radiusAngle));
	edgeWeightText->setPosition((start + end) / 2.f
		- sf::Vector2f(localBounds.size).rotatedBy(sf::radians(radiusAngle)) / 2.f
		- sf::Vector2f(3, 3).rotatedBy(sf::radians(radiusAngle)) // Padding between text and line
	);
	edgeWeightText->setPosition(round(edgeWeightText->getPosition()));

	drawableList.push_back(std::move(edgeWeightText));
}


void PrimVisEngine::drawHighlightEdge(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, 
	sf::Vector2f start, sf::Vector2f end, bool inMST) {
	double radiusAngle = std::atan2(end.y - start.y, end.x - start.x);
	start += sf::Vector2f(nodeCircleRadius * std::cos(radiusAngle), nodeCircleRadius * std::sin(radiusAngle));
	end   -= sf::Vector2f(nodeCircleRadius * std::cos(radiusAngle), nodeCircleRadius * std::sin(radiusAngle));
	sf::Vector2f direction = end - start;
	float length = direction.length();
	float angle = std::atan2(direction.y, direction.x);

	auto highlightedEdgeLine = std::make_unique<sf::RectangleShape>(
		sf::Vector2f(length, inMST ? highlightEdgeInMSTThickness : highlightEdgeThickness)
	);
	highlightedEdgeLine->setFillColor(inMST ? highlightEdgeInMSTColor : highlightEdgeColor);
	highlightedEdgeLine->setPosition(start);
	highlightedEdgeLine->setRotation(sf::radians(angle));
	highlightedEdgeLine->setOrigin({0.f, highlightEdgeThickness / 2.0f});

	drawableList.push_back(std::move(highlightedEdgeLine));
}





void PrimVisEngine::refreshOriginPos() {
	originPos = originPosDisplacement - sf::Vector2f(windowPtr->getSize()) / 2.f;
}





// Set vis themes
void PrimVisEngine::setVisTheme(VIS_THEME visTheme) {
	switch (visTheme) {
	case VIS_THEME::LIGHT:
		setLightVisTheme();
		break;
	case VIS_THEME::DARK:
		setDarkVisTheme();
		break;
	}
}
void PrimVisEngine::setLightVisTheme() {
	normalNodeColor           = lightNormalNodeColor;
	normalNodeKeyColor        = lightNormalNodeKeyColor;
	visitedNodeColor          = lightVisitedNodeColor;
	draggedNodeColor          = lightDraggedNodeColor;
	weightTextColor           = lightWeightTextColor;
	nodeInfoTextColor         = lightNodeInfoTextColor;
	highlightCircleColor      = lightHighlightCircleColor;
	highlightFoundCircleColor = lightHighlightFoundCircleColor;
	highlightEdgeColor        = lightHighlightEdgeColor;
	highlightEdgeInMSTColor   = lightHighlightEdgeInMSTColor;
	highlightCodeColor        = lightHighlightCodeColor;
}
void PrimVisEngine::setDarkVisTheme() {
	normalNodeColor           = darkNormalNodeColor;
	normalNodeKeyColor        = darkNormalNodeKeyColor;
	visitedNodeColor          = darkVisitedNodeColor;
	draggedNodeColor          = darkDraggedNodeColor;
	weightTextColor           = darkWeightTextColor;
	nodeInfoTextColor         = darkNodeInfoTextColor;
	highlightCircleColor      = darkHighlightCircleColor;
	highlightFoundCircleColor = darkHighlightFoundCircleColor;
	highlightEdgeColor        = darkHighlightEdgeColor;
	highlightEdgeInMSTColor   = darkHighlightEdgeInMSTColor;
	highlightCodeColor        = darkHighlightCodeColor;
}