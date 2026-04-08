#include "Graph/Dijkstra/DijkstraVisEngine.h"




DijkstraVisEngine::DijkstraVisEngine(unsigned int numVertex, sf::RenderWindow* window, sf::Font* font)
	: windowPtr(window), fontPtr(font)
	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
	, graph(numVertex) , visualNodesCur(numVertex)
{
	///// ONLY FOR TESTING, WILL DELETE LATER /////
	for (int i = 0; i < numVertex; i++) {
		visualNodesCur[i] = VisualGraphVertex(i, {cos(3.14f/5*i) * 100.f, sin(3.14f/5*i) * 100.f});
	}
}

// DijkstraVisEngine::DijkstraVisEngine(std::mt19937& rng, sf::RenderWindow* window, sf::Font* font)
// 	: windowPtr(window), fontPtr(font)
// 	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
// 	, graph(numVertex) , visualNodesCur(numVertex)
// {
// 	std::uniform_int_distribution<size_t> size_distrib(Dijkstra_INIT_MIN_SIZE, Dijkstra_INIT_MAX_SIZE);
// 	std::uniform_int_distribution<size_t> wordLen_distrib(Dijkstra_INIT_WORD_MIN_LENGTH, Dijkstra_INIT_WORD_MAX_LENGTH);
// 	std::uniform_int_distribution<int> char_distrib(Dijkstra_RANDOM_DISTRIB_KEY_MIN, Dijkstra_RANDOM_DISTRIB_KEY_MAX);

// 	size_t wordCount = size_distrib(rng);
// 	for (size_t i = 0; i < wordCount; i++) {
// 		size_t wordLen = wordLen_distrib(rng);
// 		std::string wordInit(wordLen, 'a');
// 		for (char& c : wordInit)
// 			c = static_cast<char>(char_distrib(rng));
// 		graph.insertWord(wordInit);
// 	}
// }

// DijkstraVisEngine::DijkstraVisEngine(std::vector<std::vector<Edge>>& adjList, sf::RenderWindow* window, sf::Font* font)
// 	: windowPtr(window), fontPtr(font)
// 	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
// 	, graph(numVertex) , visualNodesCur(numVertex)
// {
// 	size_t wordCount = words.size();
// 	for (size_t i = 0; i < wordCount; i++) {
// 		graph.insertWord(words[i]);
// 	}
// }

// Delete all dynamically allocated memory
DijkstraVisEngine::~DijkstraVisEngine() {}



// Reset all properties to get ready for visualize new action
///// MAKE SURE TO RESET ALL NECESSARY PROPERTIES
void DijkstraVisEngine::resetParams() {
	resetAnimParams();
}






///// --- LOGICAL ALGORITHMS AND EVENTS --- /////
// -- SEARCHING --
std::vector<DijkstraAnimStep> DijkstraVisEngine::getEventsDijkstra(int startVertex) {
	std::vector<DijkstraAnimStep> events;
	oldGraphSnapshots.clear();
	oldGraphSnapshots.push_back(graph);

	events.push_back(DijkstraAnimStep(DijkstraAnimType::NONE, "Before running Dijkstra\'s algorithm with starting vertex: \"" + std::to_string(startVertex) + "\"", {}, 0, 0));
	graph.generateDijkstraEvents(startVertex, events, oldGraphSnapshots);

	std::cerr << "Done generating insertion events!" << std::endl; // DEBUG
	std::cerr << ", size = " << graph.getNumVertex() << std::endl; // DEBUG

	return events;
}



// // -- INSERTION --
// std::vector<DijkstraAnimStep> DijkstraVisEngine::getEventsInsert(std::string word) {
// 	std::vector<DijkstraAnimStep> events;
// 	oldGraphSnapshots.clear();
// 	oldGraphSnapshots.push_back(graph);

// 	events.push_back(DijkstraAnimStep(DijkstraAnimType::NONE, "Before inserting word: \"" + word + "\"", {}, 0, oldGraphSnapshots.size() - 1));
// 	// Insert node into graph and get animation events
// 	LogicDijkstraNode* lastInsertedNode = graph.generateInsertEvents(word, events, oldGraphSnapshots);
// 	// // Remind to snapshot graph after insertion/rotation
// 	// graph.snapshotGraph(ID, events, oldGraphSnapshots);

// 	events.push_back(DijkstraAnimStep(DijkstraAnimType::HIGHLIGHT_FOUND_NODE, "Finished inserting word: \"" + word + "\"", {}, lastInsertedNode->getID(), -1));

// 	std::cerr << "Done generating insertion events!" << std::endl; // DEBUG
// 	std::cerr << ", size = " << graph.getNumVertex() << std::endl; // DEBUG

// 	return events;
// }



// // -- DELETION --
// std::vector<DijkstraAnimStep> DijkstraVisEngine::getEventsDelete(std::string word) {
// 	std::vector<DijkstraAnimStep> events;
// 	oldGraphSnapshots.clear();
// 	oldGraphSnapshots.push_back(graph);

// 	events.push_back(DijkstraAnimStep(DijkstraAnimType::NONE, "Before deleting word: \"" + word + "\"", {}, 0, oldGraphSnapshots.size() -1));
// 	graph.generateDeleteEvents(word, events, oldGraphSnapshots);

// 	std::cerr << "Done generating deletion events!" << std::endl; // DEBUG
// 	std::cerr << ", size = " << graph.getNumVertex() << std::endl; // DEBUG

// 	return events;
// }







// Update positions (based on force-directed graph drawing)
// Fruchterman-Reingold algorithm
void DijkstraVisEngine::updateNodePositions() {
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








void DijkstraVisEngine::getDraggedVertexID(sf::Vector2f mousePos, sf::Vector2f viewDisplacement, float viewZoomFactor) {
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


void DijkstraVisEngine::resetDraggedVertexID() {
	draggedVertexID = -1; // Reset draggedVertexID
}


void DijkstraVisEngine::dragVertexByMouse(sf::Vector2f mousePos, sf::Vector2f viewDisplacement, float viewZoomFactor) {
	mousePos -= sf::Vector2f(windowPtr->getSize()) / 2.f;

	unsigned int numVertex = graph.getNumVertex();
	if (!(0 <= draggedVertexID && draggedVertexID < numVertex)) return;
	visualNodesCur[draggedVertexID].position = mousePos * viewZoomFactor + viewDisplacement;
}










// Draw nodes: Iterate through graph and draw nodes
// --- NORMAL MODE | RUNNING DIJKSTRA MODE ---
void DijkstraVisEngine::addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, DijkstraAnimStep eventDijkstra) {
	// generateAllVisNodePos(visualNodesCur, graph);
	// generateAllVisNodePos(graph);

	drawStillGraph(drawableList, graph);

	// Draw highlighting circle
	switch (eventDijkstra.type) {
	case DijkstraAnimType::HIGHLIGHT_NODE:
		drawHighlightCircle(drawableList, visualNodesCur[eventDijkstra.vertexID].position, false);
		break;
	// case DijkstraAnimType::HIGHLIGHT_FOUND_NODE:
	// 	drawHighlightCircle(drawableList, visualNodesCur[eventDijkstra.vertexID].position, true);
	// 	break;
	// case DijkstraAnimType::MOVE_HIGHLIGHT_DOWN:
	// 	if (graph.getNodeID(eventDijkstra.vertexID) && graph.getNodeID(eventDijkstra.vertexID)->getChild(eventDijkstra.charLink))
	// 		drawHighlightCircle(drawableList,
	// 			easeInOutLerp(visualNodesCur[eventDijkstra.vertexID].position, 
	// 						  visualNodesCur[graph.getNodeID(eventDijkstra.vertexID)->getChild(eventDijkstra.charLink)->getID()].position, 
	// 						  fract(time)),
	// 			false);
	// 	else
	// 		drawHighlightCircle(drawableList, visualNodesCur[eventDijkstra.vertexID].position, false);
	// 	break;
	case DijkstraAnimType::NONE:
	default:
		break;
	}
}





// // --- INSERT MODE ---
// void DijkstraVisEngine::addNodeDrawablesDijkstra(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, DijkstraAnimStep eventDijkstra) {
// 	groupsOldVisualNodes.clear();
// 	size_t numOfOldGraphSnapshots = oldGraphSnapshots.size();
// 	groupsOldVisualNodes.resize(numOfOldGraphSnapshots);

// 	// Generate all visual nodes, new and old
// 	// generateAllVisNodePos(visualNodesCur, graph);
// 	generateAllVisNodePos(graph);
// 	for (int i = 0; i < numOfOldGraphSnapshots; i++) {
// 		// generateAllVisNodePos(groupsOldVisualNodes[i], oldGraphSnapshots[i]);
// 		generateAllVisNodePos(oldGraphSnapshots[i]);
// 	}
// 	std::cerr << "numOfOldGraphSnapshots = " << numOfOldGraphSnapshots << ", "; // DEBUG

// 	// Find old visual nodes and old graph snapshot
// 	std::vector<VisualDijkstraNode>& oldVisualNodes =
// 		(eventDijkstra.oldTreeSnapshotIndex == -1) ? visualNodesCur : groupsOldVisualNodes[eventDijkstra.oldTreeSnapshotIndex];
// 	LogicDijkstra& oldTreeSnapshot =
// 		(eventDijkstra.oldTreeSnapshotIndex == -1) ? graph : oldGraphSnapshots[eventDijkstra.oldTreeSnapshotIndex];

// 	// Draw the graph
// 	switch (eventDijkstra.type) {
// 	case DijkstraAnimType::INSERT_NODE:
// 		// Node insertion animation
// 		drawLerpTreeInsertNode(drawableList,
// 			groupsOldVisualNodes[eventDijkstra.oldTreeSnapshotIndex - 1],
// 			oldGraphSnapshots[eventDijkstra.oldTreeSnapshotIndex - 1],
// 			oldVisualNodes, oldTreeSnapshot, 
// 			eventDijkstra.vertexID
// 		);
// 		break;
// 	default:
// 		drawStillTree(drawableList, oldVisualNodes, oldTreeSnapshot);
// 	}

// 	// Draw highlighting circle
// 	switch (eventDijkstra.type) {
// 	case DijkstraAnimType::HIGHLIGHT_NODE:
// 		drawHighlightCircle(drawableList, oldVisualNodes[eventDijkstra.vertexID].position, false);
// 		break;
// 	case DijkstraAnimType::HIGHLIGHT_FOUND_NODE:
// 	// case DijkstraAnimType::INSERT_NODE: // Highlight inserted node when at inserting event
// 		drawHighlightCircle(drawableList, oldVisualNodes[eventDijkstra.vertexID].position, true);
// 		break;
// 	case DijkstraAnimType::MOVE_HIGHLIGHT_DOWN:
// 		if (oldTreeSnapshot.getNodeID(eventDijkstra.vertexID) && oldTreeSnapshot.getNodeID(eventDijkstra.vertexID)->getChild(eventDijkstra.charLink)) {
// 			drawHighlightCircle(drawableList,
// 				easeInOutLerp(oldVisualNodes[eventDijkstra.vertexID].position, 
// 							  oldVisualNodes[oldTreeSnapshot.getNodeID(eventDijkstra.vertexID)->getChild(eventDijkstra.charLink)->getID()].position, 
// 							  fract(time)),
// 				false);
// 		} else {
// 			drawHighlightCircle(drawableList, oldVisualNodes[eventDijkstra.vertexID].position, false);
// 		}
// 		break;
// 	case DijkstraAnimType::NONE:
// 	default:
// 		break;
// 	}
// }





// Create AND display ImGui window to highlight source code (pseudocode)
void DijkstraVisEngine::drawPseudocodeWindow(DijkstraAnimStep eventDijkstra) {
	ImGui::Begin("Pseudocode", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	switch (visMode) {
	// case DijkstraVisMode::DIJKSTRA:
	// 	for (int i = 0; i < DIJKSTRA_CODE_SEARCH.size(); i++) {
	// 		if (vecContains(eventDijkstra.highlightCodeLineIndex, i))
	// 			ImGui::PushStyleColor(ImGuiCol_Text, highlightCodeColor);
	// 		ImGui::Text("%s", DIJKSTRA_CODE_SEARCH[i].c_str());
	// 		if (vecContains(eventDijkstra.highlightCodeLineIndex, i))
	// 			ImGui::PopStyleColor();
	// 	}
	// 	break;
	default:
		ImGui::Text("(Nothing to visualize.)");
		break;
	}

	ImGui::End();
}










// Draw nodes and links, depending on eventList
void DijkstraVisEngine::createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList) {
	refreshOriginPos(); // Refresh properties when window size changes
	drawableList.clear();


	// If STILL mode, stop here
	if (eventList.size() <= 1) {
		// Update vertex positions due to forces
		updateNodePositions();
		// Display nodes: Iterate through graph and draw nodes
		addNodeDrawables(drawableList, DijkstraAnimStep());
		return;
	}


	// change visCur and visCurIndex
	animStepIndex = std::min(static_cast<int>(floor(time)), static_cast<int>(eventList.size()) - 1);
	time = std::min(std::max(time, 0.f), static_cast<float>(eventList.size()) - 0.0005f);
	DijkstraAnimStep eventDijkstra = eventList[animStepIndex];
	// if (time == static_cast<float>(eventList.size())) eventDijkstra = eventList.back();
	// Set parameters
	// searchSlotIdx = eventDijkstra.searchSlotIdx; // Set searchSlotIdx in the event
	// Less safe: animInProgress = (time != static_cast<float>(eventList.size()) - 0.0005f);
	animInProgress = (abs(time - (static_cast<float>(eventList.size()) - 0.0005f)) > EPSILON_TIME);

	if (animStepIndex > oldAnimStepIndex) {
		// if (eventList[oldAnimStepIndex].type == DijkstraAnimType::MOVE_CUR_FORWARD) {
		// 	visCurIndex++;
		// 	visCur = visCur->pNext;
		// }
		oldAnimStepIndex = animStepIndex;
	}



	
	// DIJKSTRA MODE
	// Update vertex positions due to forces
	updateNodePositions();
	// Display nodes: Iterate through graph and draw nodes
	addNodeDrawables(drawableList, eventDijkstra);
	drawPseudocodeWindow(eventDijkstra);




	// Display description for algorithm visualization
	auto descriptionText = std::make_unique<sf::Text>(*fontPtr, eventDijkstra.description, descriptionFontSize);
	descriptionText->setFillColor(sf::Color::Black);
	descriptionText->setPosition(originPos - originPosDisplacement + descriptionTextPos);
	descriptionText->setPosition(round(descriptionText->getPosition()));

	drawableList.push_back(std::move(descriptionText));


	std::cout << drawableList.size() << ' ' << time << " init done" << std::endl; // DEBUG
}












// Set correct positions for ALL VISUAL nodes
// Uses inorder positioning
void DijkstraVisEngine::generateAllVisNodePos(LogicGraphDijkstra& logicGraph) {
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
void DijkstraVisEngine::drawNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, 
	const VisualGraphVertex& visVertex, const LogicGraphDijkstra& graphSnapshot) {
	// Draw circle
	auto nodeCircle = std::make_unique<sf::CircleShape>(nodeCircleRadius);
	nodeCircle->setOrigin({nodeCircle->getRadius(), nodeCircle->getRadius()}); 
	nodeCircle->setFillColor((draggedVertexID == visVertex.getID()) ? draggedNodeColor :sf::Color::Transparent);
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
	// // Draw height text
	// auto nodeHeightText = std::make_unique<sf::Text>(*fontPtr, std::to_string(visVertex.height), nodeHeightTextFontSize);
	// localBounds = nodeHeightText->getLocalBounds();
	// nodeHeightText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	// nodeHeightText->setFillColor(normalNodeHeightColor);
	// nodeHeightText->setPosition(nodeCircle->getPosition() + sf::Vector2f(nodeCircleRadius, -nodeCircleRadius));
	// nodeHeightText->setPosition(round(nodeHeightText->getPosition()));

	drawableList.push_back(std::move(nodeCircle));
	drawableList.push_back(std::move(nodeIDText));
	// drawableList.push_back(std::move(nodeHeightText));
}


// Draw the highlight circle (a circle highlighting a node)
void DijkstraVisEngine::drawHighlightCircle(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, 
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
void DijkstraVisEngine::drawGraphEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, 
	const LogicGraphDijkstra& graphSnapshot) {
	unsigned int numVertex = graphSnapshot.getNumVertex();
	for (int i = 0; i < numVertex; i++) {
		for (const auto& [to, weight] : graphSnapshot.adjList[i]) {
			if (i > to) continue; // Don't draw twice
			sf::Vector2f start = visualNodesCur[i].position, end = visualNodesCur[to].position;
			drawEdgeLine(drawableList, start, end);

			drawEdgeWeightText(drawableList, start, end, weight);
		}
	}
}


void DijkstraVisEngine::drawStillGraph(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, 
	const LogicGraphDijkstra& graphSnapshot) {
	drawGraphEdges(drawableList, graphSnapshot);
	unsigned int numVertex = graphSnapshot.getNumVertex();
	for (int ID = 0; ID < numVertex; ID++) {
		drawNode(drawableList, visualNodesCur[ID], graphSnapshot);
	}
}



// // Draw lerped node
// void DijkstraVisEngine::drawLerpNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualDijkstraNode& visVertex1, const VisualDijkstraNode& visVertex2) {
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
// void DijkstraVisEngine::drawLerpTreeEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const LogicDijkstraNode* root,
// 	std::vector<VisualDijkstraNode>& visualNodes1, std::vector<VisualDijkstraNode>& visualNodes2) {
// 	if (!root) return;
// 	for (int i = 0; i < DIJKSTRA_ALPHABET_SIZE; i++)
// 		drawLerpTreeEdges(drawableList, root->children[i], visualNodes1, visualNodes2);
// 	for (int i = 0; i < DIJKSTRA_ALPHABET_SIZE; i++) {
// 		if (!root->children[i]) continue;
// 		sf::Vector2f start = easeInOutLerp(visualNodes1[root->getID()].position, visualNodes2[root->getID()].position, fract(time));
// 		sf::Vector2f end = easeInOutLerp(visualNodes1[root->children[i]->getID()].position, 
// 										 visualNodes2[root->children[i]->getID()].position, 
// 										 fract(time));
// 		drawEdgeLine(drawableList, start, end);
// 	}
// }

// // Draw lerped graph (nodes and edges)
// void DijkstraVisEngine::drawLerpTree(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
// 	std::vector<VisualDijkstraNode>& visualNodes1, LogicDijkstra& logicGraph1,
// 	std::vector<VisualDijkstraNode>& visualNodes2, LogicDijkstra& logicGraph2) {
// 	drawLerpTreeEdges(drawableList, logicGraph2.root, visualNodes1, visualNodes2);
// 	for (const auto& [ID, visVertex2] : visualNodes2) {
// 		drawLerpNode(drawableList, visualNodes1[ID], visVertex2);
// 	}
// }

// // Draw lerped graph when inserting a node
// void DijkstraVisEngine::drawLerpTreeInsertNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
// 	std::vector<VisualDijkstraNode>& visualNodes1, LogicDijkstra& logicGraph1,
// 	std::vector<VisualDijkstraNode>& visualNodes2, LogicDijkstra& logicGraph2,
// 	uint64_t nodeInsertID) {
// 	LogicDijkstra logicGraphBefore = logicGraph2;
// 	std::vector<VisualDijkstraNode> visualNodesBefore = visualNodes2;
// 	for (const auto& [ID, visVertex1] : visualNodes1) {
// 		visualNodesBefore[ID].position = visVertex1.position;
// 	}
// 	visualNodesBefore[nodeInsertID].position = originPos + newNodeStartPos;
// 	drawLerpTree(drawableList, visualNodesBefore, logicGraphBefore, visualNodes2, logicGraph2);
// }

// // Draw lerped graph when deleting a node
// void DijkstraVisEngine::drawLerpTreeDeleteNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
// 	std::vector<VisualDijkstraNode>& visualNodes1, LogicDijkstra& logicGraph1,
// 	std::vector<VisualDijkstraNode>& visualNodes2, LogicDijkstra& logicGraph2,
// 	uint64_t nodeRemoveID) {
// 	LogicDijkstra logicGraphBefore = logicGraph2;
// 	std::vector<VisualDijkstraNode> visualNodesBefore = visualNodes2;
// 	for (const auto& [ID, visVertex1] : visualNodes1) {
// 		if (ID != nodeRemoveID)
// 			visualNodesBefore[ID].position = visVertex1.position;
// 	}
// 	// visualNodesBefore[nodeRemoveID].position = originPos + newNodeStartPos;
// 	drawLerpTree(drawableList, visualNodesBefore, logicGraphBefore, visualNodes2, logicGraph2);
// }







// Helper drawing functions
void DijkstraVisEngine::drawEdgeLine(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f start, sf::Vector2f end) {
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
	(*arrowBody)[0].color = sf::Color::Black;
	(*arrowBody)[1].position = end;
	(*arrowBody)[1].color = sf::Color::Black;

	// auto arrowHead = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Triangles, 3);
	// (*arrowHead)[0].position = end;
	// (*arrowHead)[0].color = sf::Color::Black;
	// (*arrowHead)[1].position = sf::Vector2f(leftX, leftY);
	// (*arrowHead)[1].color = sf::Color::Black;
	// (*arrowHead)[2].position = sf::Vector2f(rightX, rightY);
	// (*arrowHead)[2].color = sf::Color::Black;

	drawableList.push_back(std::move(arrowBody));
	// drawableList.push_back(std::move(arrowHead));
}

void DijkstraVisEngine::drawEdgeWeightText(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f start, sf::Vector2f end, int weight) {
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
	edgeWeightText->setPosition((start + end) / 2.f);
	edgeWeightText->setRotation(sf::radians(radiusAngle));
	edgeWeightText->setPosition(round(edgeWeightText->getPosition()));

	drawableList.push_back(std::move(edgeWeightText));
}





void DijkstraVisEngine::refreshOriginPos() {
	originPos = originPosDisplacement - sf::Vector2f(windowPtr->getSize()) / 2.f;
}
