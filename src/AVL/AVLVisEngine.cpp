#include "AVL/AVLVisEngine.h"




AVLVisEngine::AVLVisEngine(sf::RenderWindow* window, sf::Font* font)
	: windowPtr(window), fontPtr(font)
	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
{}





// Reset all properties to get ready for visualize new action
///// MAKE SURE TO RESET ALL NECESSARY PROPERTIES
void AVLVisEngine::resetParams() {
	resetAnimParams();
}





///// --- LOGICAL ALGORITHMS AND EVENTS --- /////
// -- SEARCHING --
void AVLVisEngine::getEventsSearchStep(std::vector<AVLAnimStep>& events, LogicAVLNode* root, int key) {
	if (!root) {
		events.push_back(AVLAnimStep(AVLAnimType::NONE, "Found null node, element not found.", {}));
		return;
	}
	if (root->key == key) {
		events.push_back(AVLAnimStep(AVLAnimType::HIGHLIGHT_NODE, "Checking node " + std::to_string(root->key), {}, root->key));
		events.push_back(AVLAnimStep(AVLAnimType::HIGHLIGHT_FOUND_NODE, "Found element " + std::to_string(key), {}, root->key));
		return;
	} else if (root->key > key) {
		events.push_back(AVLAnimStep(AVLAnimType::HIGHLIGHT_NODE, "Checking node " + std::to_string(root->key), {}, root->key));
		events.push_back(AVLAnimStep(AVLAnimType::MOVE_HIGHLIGHT_LEFT_DOWN, "Looking at left subtree of node " + std::to_string(root->key), {}, root->key));
		getEventsSearchStep(events, root->left, key);
	} else {
		events.push_back(AVLAnimStep(AVLAnimType::HIGHLIGHT_NODE, "Checking node " + std::to_string(root->key), {}, root->key));
		events.push_back(AVLAnimStep(AVLAnimType::MOVE_HIGHLIGHT_RIGHT_DOWN, "Looking at right subtree of node " + std::to_string(root->key), {}, root->key));
		getEventsSearchStep(events, root->right, key);
	}
}

std::vector<AVLAnimStep> AVLVisEngine::getEventsSearch(int key) {
	std::vector<AVLAnimStep> events;
	getEventsSearchStep(events, tree.root, key);
	return events;
}



// -- INSERTING --
std::vector<AVLAnimStep> AVLVisEngine::getEventsInsert(int key) {
	std::vector<AVLAnimStep> events;
	oldTreeSnapshots.clear();
	oldTreeSnapshots.push_back(tree);
	tree.inorderPrint(); // DEBUG

	events.push_back(AVLAnimStep(AVLAnimType::NONE, "Before inserting key " + std::to_string(key), {}, key, 0));
	// Insert node into tree and get animation events
	tree.root = tree.insertEvents(tree.root, key, events, oldTreeSnapshots);
	// Remind to snapshot tree after insertion/rotation
	tree.snapshotTree(key, events, oldTreeSnapshots);

	events.push_back(AVLAnimStep(AVLAnimType::HIGHLIGHT_FOUND_NODE, "Finished inserting key " + std::to_string(key), {}, key, -1));
	
	std::cerr << "Done generating insertion events!" << std::endl; // DEBUG
	tree.inorderPrint(); // DEBUG
	std::cerr << ", size = " << tree.getSize() << std::endl; // DEBUG

	return events;
}










// Draw nodes: Iterate through linked list and draw nodes
// --- NORMAL | SEARCH MODE ---
void AVLVisEngine::addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, AVLAnimStep eventAVL) {
	generateAllVisNodePos(visualNodesCur, tree);

	drawStillTree(drawableList, visualNodesCur, tree);

	// Draw highlighting circle
	switch (eventAVL.type) {
	case AVLAnimType::HIGHLIGHT_NODE:
		drawHighlightCircle(drawableList, visualNodesCur[eventAVL.curKey].position, false);
		break;
	case AVLAnimType::HIGHLIGHT_FOUND_NODE:
		drawHighlightCircle(drawableList, visualNodesCur[eventAVL.curKey].position, true);
		break;
	case AVLAnimType::MOVE_HIGHLIGHT_LEFT_DOWN:
		if (tree.getNodeKey(eventAVL.curKey) && tree.getNodeKey(eventAVL.curKey)->left)
			drawHighlightCircle(drawableList,
				easeInOutLerp(visualNodesCur[eventAVL.curKey].position, visualNodesCur[tree.getNodeKey(eventAVL.curKey)->left->key].position, fract(time)),
				false);
		else
			drawHighlightCircle(drawableList, visualNodesCur[eventAVL.curKey].position, false);
		break;
	case AVLAnimType::MOVE_HIGHLIGHT_RIGHT_DOWN:
		if (tree.getNodeKey(eventAVL.curKey) && tree.getNodeKey(eventAVL.curKey)->right)
			drawHighlightCircle(drawableList,
				easeInOutLerp(visualNodesCur[eventAVL.curKey].position, visualNodesCur[tree.getNodeKey(eventAVL.curKey)->right->key].position, fract(time)),
				false);
		else
			drawHighlightCircle(drawableList, visualNodesCur[eventAVL.curKey].position, false);
		break;
	case AVLAnimType::NONE:
	default:
		break;
	}
}



// --- INSERT MODE ---
void AVLVisEngine::addNodeDrawablesInsert(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, AVLAnimStep eventAVL) {
	groupsOldVisualNodes.clear();
	unsigned int numOfOldTreeSnapshots = oldTreeSnapshots.size();
	groupsOldVisualNodes.resize(numOfOldTreeSnapshots);
	generateAllVisNodePos(visualNodesCur, tree);
	for (int i = 0; i < numOfOldTreeSnapshots; i++) {
		generateAllVisNodePos(groupsOldVisualNodes[i], oldTreeSnapshots[i]);
	}
	std::cerr << "numOfOldTreeSnapshots = " << numOfOldTreeSnapshots << ", "; // DEBUG

	std::map<int, VisualAVLNode>& oldVisualNodes =
		(eventAVL.oldTreeSnapshotIndex == -1) ? visualNodesCur : groupsOldVisualNodes[eventAVL.oldTreeSnapshotIndex];
	LogicAVLTree& oldTreeSnapshot =
		(eventAVL.oldTreeSnapshotIndex == -1) ? tree : oldTreeSnapshots[eventAVL.oldTreeSnapshotIndex];

	// Draw the tree
	switch (eventAVL.type) {
	case AVLAnimType::ROTATE_RIGHT_LL:
	case AVLAnimType::ROTATE_LEFT_RR:
	case AVLAnimType::ROTATE_LEFT_LR:
	case AVLAnimType::ROTATE_RIGHT_LR:
	case AVLAnimType::ROTATE_LEFT_RL:
	case AVLAnimType::ROTATE_RIGHT_RL:
		// Tree rotations animation
		drawLerpTree(drawableList,
			groupsOldVisualNodes[eventAVL.oldTreeSnapshotIndex - 1],
			oldTreeSnapshots[eventAVL.oldTreeSnapshotIndex - 1],
			oldVisualNodes, oldTreeSnapshot
		);
		break;
	case AVLAnimType::INSERT_NODE:
		// Node insertion animation
		drawLerpTreeInsertNode(drawableList,
			groupsOldVisualNodes[eventAVL.oldTreeSnapshotIndex - 1],
			oldTreeSnapshots[eventAVL.oldTreeSnapshotIndex - 1],
			oldVisualNodes, oldTreeSnapshot
		);
		break;
	default:
		drawStillTree(drawableList, oldVisualNodes, oldTreeSnapshot);
	}

	// Draw highlighting circle
	switch (eventAVL.type) {
	case AVLAnimType::HIGHLIGHT_NODE:
	case AVLAnimType::HIGHLIGHT_NODE_UPDATE_HEIGHT:
		drawHighlightCircle(drawableList, oldVisualNodes[eventAVL.curKey].position, false);
		break;
	case AVLAnimType::HIGHLIGHT_FOUND_NODE:
	// case AVLAnimType::INSERT_NODE: // Highlight inserted node when at inserting event
		drawHighlightCircle(drawableList, oldVisualNodes[eventAVL.curKey].position, true);
		break;
	case AVLAnimType::MOVE_HIGHLIGHT_LEFT_DOWN:
		if (oldTreeSnapshot.getNodeKey(eventAVL.curKey) && oldTreeSnapshot.getNodeKey(eventAVL.curKey)->left)
			drawHighlightCircle(drawableList,
				easeInOutLerp(oldVisualNodes[eventAVL.curKey].position, oldVisualNodes[oldTreeSnapshot.getNodeKey(eventAVL.curKey)->left->key].position, fract(time)),
				false);
		else
			drawHighlightCircle(drawableList, oldVisualNodes[eventAVL.curKey].position, false);
		break;
	case AVLAnimType::MOVE_HIGHLIGHT_LEFT_UP:
		if (oldTreeSnapshot.getNodeKey(eventAVL.curKey) && oldTreeSnapshot.getNodeKey(eventAVL.curKey)->left)
			drawHighlightCircle(drawableList,
				easeInOutLerp(oldVisualNodes[oldTreeSnapshot.getNodeKey(eventAVL.curKey)->left->key].position, oldVisualNodes[eventAVL.curKey].position, fract(time)),
				false);
		else
			drawHighlightCircle(drawableList, oldVisualNodes[eventAVL.curKey].position, false);
		break;
	case AVLAnimType::MOVE_HIGHLIGHT_RIGHT_DOWN:
		if (oldTreeSnapshot.getNodeKey(eventAVL.curKey) && oldTreeSnapshot.getNodeKey(eventAVL.curKey)->right)
			drawHighlightCircle(drawableList,
				easeInOutLerp(oldVisualNodes[eventAVL.curKey].position, oldVisualNodes[oldTreeSnapshot.getNodeKey(eventAVL.curKey)->right->key].position, fract(time)),
				false);
		else
			drawHighlightCircle(drawableList, oldVisualNodes[eventAVL.curKey].position, false);
		break;
	case AVLAnimType::MOVE_HIGHLIGHT_RIGHT_UP:
		if (oldTreeSnapshot.getNodeKey(eventAVL.curKey) && oldTreeSnapshot.getNodeKey(eventAVL.curKey)->right)
			drawHighlightCircle(drawableList,
				easeInOutLerp(oldVisualNodes[oldTreeSnapshot.getNodeKey(eventAVL.curKey)->right->key].position, oldVisualNodes[eventAVL.curKey].position, fract(time)),
				false);
		else
			drawHighlightCircle(drawableList, oldVisualNodes[eventAVL.curKey].position, false);
		break;
	case AVLAnimType::NONE:
	default:
		break;
	}
}








// Draw nodes and links, depending on eventList
void AVLVisEngine::createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList) {
	drawableList.clear();


	// If STILL mode, stop here
	if (eventList.size() <= 1) {
		// Display nodes: Iterate through linked list and draw nodes
		addNodeDrawables(drawableList, AVLAnimStep());
		return;
	}


	// change visCur and visCurIndex
	animStepIndex = std::min(static_cast<int>(floor(time)), static_cast<int>(eventList.size()) - 1);
	time = std::min(std::max(time, 0.f), static_cast<float>(eventList.size()) - 0.0005f);
	AVLAnimStep eventAVL = eventList[animStepIndex];
	// if (time == static_cast<float>(eventList.size())) eventAVL = eventList.back();
	// Set parameters
	// searchSlotIdx = eventAVL.searchSlotIdx; // Set searchSlotIdx in the event
	// Less safe: animInProgress = (time != static_cast<float>(eventList.size()) - 0.0005f);
	animInProgress = (abs(time - (static_cast<float>(eventList.size()) - 0.0005f)) > EPSILON_TIME);

	if (animStepIndex > oldAnimStepIndex) {
		// if (eventList[oldAnimStepIndex].type == AVLAnimType::MOVE_CUR_FORWARD) {
		// 	visCurIndex++;
		// 	visCur = visCur->pNext;
		// }
		oldAnimStepIndex = animStepIndex;
	}



	if (visMode == AVLVisMode::INSERT) {
		// INSERT MODE
		addNodeDrawablesInsert(drawableList, eventAVL);
		// drawPseudocodeWindow(eventAVL);
	} else if (visMode == AVLVisMode::REMOVE) {
		// // REMOVE MODE
		// addNodeDrawablesRemove(drawableList, eventAVL);
		// drawPseudocodeWindow(eventAVL);
	} else if (visMode == AVLVisMode::UPDATE) {
		// // UPDATE MODE
		// addNodeDrawablesUpdate(drawableList, eventAVL);
		// drawPseudocodeWindow(eventAVL);
	} else {
		addNodeDrawables(drawableList, eventAVL);
		// drawPseudocodeWindow(eventAVL);
	}



	// Display description for algorithm visualization
	auto descriptionText = std::make_unique<sf::Text>(*fontPtr, eventAVL.description, descriptionFontSize);
	descriptionText->setFillColor(sf::Color::Black);
	descriptionText->setPosition(originPos - originPosDisplacement + descriptionTextPos);
	descriptionText->setPosition(round(descriptionText->getPosition()));

	drawableList.push_back(std::move(descriptionText));


	std::cout << drawableList.size() << ' ' << time << " init done" << std::endl; // DEBUG
}












// Set correct positions for ALL VISUAL nodes
// Uses inorder positioning
void AVLVisEngine::generateAllVisNodePos(std::map<int, VisualAVLNode>& visualNodes, LogicAVLTree& logicTree) {
	generateAllVisNodePosHelper(visualNodes, logicTree, logicTree.root);
}

void AVLVisEngine::generateAllVisNodePosHelper(std::map<int, VisualAVLNode>& visualNodes, LogicAVLTree& logicTree, LogicAVLNode* root) {
	visualNodes.clear();
	unsigned int size = logicTree.getSize();
	float xPos = canvasLeftMargin;
	float dx = (windowPtr->getSize().x - 2 * canvasLeftMargin) / (size > 1 ? size-1 : 1);
	int layerY = 0;
	// Prevent nodes overlapping
	if (dx < 2 * nodeCircleRadius) dx = 2 * nodeCircleRadius;

	generateRecursiveVisNodePos(visualNodes, root, xPos, dx, layerY);
}


void AVLVisEngine::generateRecursiveVisNodePos(std::map<int, VisualAVLNode>& visualNodes, LogicAVLNode* node, float& xPos, float dx, int& layerY) {
	if (!node) return;
	layerY++;
	generateRecursiveVisNodePos(visualNodes, node->left, xPos, dx, layerY);
	layerY--;
	visualNodes[node->key] = VisualAVLNode(node->key, 0, node->height,
		sf::Vector2f(originPos.x + xPos, originPos.y + layerY * nodeLayerSpacing)
	);
	xPos += dx;
	layerY++;
	generateRecursiveVisNodePos(visualNodes, node->right, xPos, dx, layerY);
	layerY--;
}





///// --- DRAWING FUNCTIONS ---
// Draw a node (a circle with the key as text inside it)
void AVLVisEngine::drawNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualAVLNode& visNode) {
	// Draw circle
	auto nodeCircle = std::make_unique<sf::CircleShape>(nodeCircleRadius);
	nodeCircle->setOrigin({nodeCircle->getRadius(), nodeCircle->getRadius()}); 
	nodeCircle->setFillColor(sf::Color::Transparent);
	nodeCircle->setOutlineColor(normalNodeColor);
	nodeCircle->setOutlineThickness(nodeOutlineThickness);
	nodeCircle->setPosition(visNode.position);
	// Draw key text
	auto nodeKeyText = std::make_unique<sf::Text>(*fontPtr, std::to_string(visNode.key), nodeKeyTextFontSize);
	sf::FloatRect localBounds = nodeKeyText->getLocalBounds();
	nodeKeyText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	nodeKeyText->setFillColor(normalNodeKeyColor);
	nodeKeyText->setPosition(nodeCircle->getPosition());
	nodeKeyText->setPosition(round(nodeKeyText->getPosition()));

	drawableList.push_back(std::move(nodeCircle));
	drawableList.push_back(std::move(nodeKeyText));
}


// Draw the highlight circle (a circle highlighting a node)
void AVLVisEngine::drawHighlightCircle(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f center, bool isFoundNode) {
	auto highlightCircle = std::make_unique<sf::CircleShape>(nodeCircleRadius + highlightCircleThickness / 2);
	highlightCircle->setOrigin({highlightCircle->getRadius(), highlightCircle->getRadius()}); 
	highlightCircle->setFillColor(sf::Color::Transparent);
	highlightCircle->setOutlineColor(isFoundNode ? highlightCircleColor : highlightFoundCircleColor);
	highlightCircle->setOutlineThickness(highlightCircleThickness);
	highlightCircle->setPosition(center);
	drawableList.push_back(std::move(highlightCircle));
}


// Draw tree edges (arrows)
void AVLVisEngine::drawTreeEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const LogicAVLNode* root, std::map<int, VisualAVLNode>& visualNodes) {
	if (!root) return;
	drawTreeEdges(drawableList, root->left, visualNodes);
	drawTreeEdges(drawableList, root->right, visualNodes);
	if (root->left) {
		sf::Vector2f start = visualNodes[root->key].position, end = visualNodes[root->left->key].position;
		drawNodeArrow(drawableList, start, end);
	}
	if (root->right) {
		sf::Vector2f start = visualNodes[root->key].position, end = visualNodes[root->right->key].position;
		drawNodeArrow(drawableList, start, end);
	}
}


void AVLVisEngine::drawStillTree(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::map<int, VisualAVLNode>& visualNodes, LogicAVLTree& logicTree) {
	drawTreeEdges(drawableList, logicTree.root, visualNodes);
	for (const auto& [key, visNode] : visualNodes) {
		drawNode(drawableList, visNode);
	}
}



// Draw lerped node
void AVLVisEngine::drawLerpNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualAVLNode& visNode1, const VisualAVLNode& visNode2) {
	// Draw circle
	auto nodeCircle = std::make_unique<sf::CircleShape>(nodeCircleRadius);
	nodeCircle->setOrigin({nodeCircle->getRadius(), nodeCircle->getRadius()}); 
	nodeCircle->setFillColor(sf::Color::Transparent);
	nodeCircle->setOutlineColor(normalNodeColor);
	nodeCircle->setOutlineThickness(nodeOutlineThickness);
	nodeCircle->setPosition(easeInOutLerp(visNode1.position, visNode2.position, fract(time)));
	// Draw key text
	auto nodeKeyText = std::make_unique<sf::Text>(*fontPtr, std::to_string(visNode1.key), nodeKeyTextFontSize);
	sf::FloatRect localBounds = nodeKeyText->getLocalBounds();
	nodeKeyText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	nodeKeyText->setFillColor(normalNodeKeyColor);
	nodeKeyText->setPosition(nodeCircle->getPosition());
	nodeKeyText->setPosition(round(nodeKeyText->getPosition()));

	drawableList.push_back(std::move(nodeCircle));
	drawableList.push_back(std::move(nodeKeyText));
}

// Draw lerped tree edges (arrows)
void AVLVisEngine::drawLerpTreeEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const LogicAVLNode* root,
	std::map<int, VisualAVLNode>& visualNodes1, std::map<int, VisualAVLNode>& visualNodes2) {
	if (!root) return;
	drawLerpTreeEdges(drawableList, root->left, visualNodes1, visualNodes2);
	drawLerpTreeEdges(drawableList, root->right, visualNodes1, visualNodes2);
	if (root->left) {
		sf::Vector2f start = easeInOutLerp(visualNodes1[root->key].position, visualNodes2[root->key].position, fract(time));
		sf::Vector2f end = easeInOutLerp(visualNodes1[root->left->key].position, visualNodes2[root->left->key].position, fract(time));
		drawNodeArrow(drawableList, start, end);
	}
	if (root->right) {
		sf::Vector2f start = easeInOutLerp(visualNodes1[root->key].position, visualNodes2[root->key].position, fract(time));
		sf::Vector2f end = easeInOutLerp(visualNodes1[root->right->key].position, visualNodes2[root->right->key].position, fract(time));
		drawNodeArrow(drawableList, start, end);
	}
}

// Draw lerped tree (nodes and edges)
void AVLVisEngine::drawLerpTree(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
	std::map<int, VisualAVLNode>& visualNodes1, LogicAVLTree& logicTree1,
	std::map<int, VisualAVLNode>& visualNodes2, LogicAVLTree& logicTree2) {
	drawLerpTreeEdges(drawableList, logicTree2.root, visualNodes1, visualNodes2);
	for (const auto& [key, visNode2] : visualNodes2) {
		drawLerpNode(drawableList, visualNodes1[key], visNode2);
	}
}

// Draw lerped tree when inserting a node
void AVLVisEngine::drawLerpTreeInsertNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
	std::map<int, VisualAVLNode>& visualNodes1, LogicAVLTree& logicTree1,
	std::map<int, VisualAVLNode>& visualNodes2, LogicAVLTree& logicTree2) {
	LogicAVLTree logicTreeBefore = logicTree2;
	std::map<int, VisualAVLNode> visualNodesBefore = visualNodes2;
	for (const auto& [key, visNode1] : visualNodes1) {
		visualNodesBefore[key].position = visNode1.position;
	}
	visualNodesBefore[keyToInsert].position = originPos + newNodeStartPos;
	drawLerpTree(drawableList, visualNodesBefore, logicTreeBefore, visualNodes2, logicTree2);
}





// Helper drawing functions
void AVLVisEngine::drawNodeArrow(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f start, sf::Vector2f end) {
	double radiusAngle = std::atan2(end.y - start.y, end.x - start.x);
	start += sf::Vector2f(nodeCircleRadius * std::cos(radiusAngle), nodeCircleRadius * std::sin(radiusAngle));
	end   -= sf::Vector2f(nodeCircleRadius * std::cos(radiusAngle), nodeCircleRadius * std::sin(radiusAngle));

	float dx = end.x - start.x, dy = end.y - start.y;
	float len = sqrt(dx*dx + dy*dy);
	if (abs(len) < 1e-3) return; // Too small, don't draw

	float ux = dx / len, uy = dy / len;
	float px = -uy, py = ux;
	float height = sqrt(3.0) / 2 * arrowHeadSideLen;
	float baseCenterX = end.x - height * ux;
	float baseCenterY = end.y - height * uy;
	float leftX  = baseCenterX + (arrowHeadSideLen / 2) * px;
	float leftY  = baseCenterY + (arrowHeadSideLen / 2) * py;
	float rightX = baseCenterX - (arrowHeadSideLen / 2) * px;
	float rightY = baseCenterY - (arrowHeadSideLen / 2) * py;

	auto arrowBody = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Lines, 2);
	(*arrowBody)[0].position = start;
	(*arrowBody)[0].color = sf::Color::Black;
	(*arrowBody)[1].position = end;
	(*arrowBody)[1].color = sf::Color::Black;

	auto arrowHead = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Triangles, 3);
	(*arrowHead)[0].position = end;
	(*arrowHead)[0].color = sf::Color::Black;
	(*arrowHead)[1].position = sf::Vector2f(leftX, leftY);
	(*arrowHead)[1].color = sf::Color::Black;
	(*arrowHead)[2].position = sf::Vector2f(rightX, rightY);
	(*arrowHead)[2].color = sf::Color::Black;

	drawableList.push_back(std::move(arrowBody));
	drawableList.push_back(std::move(arrowHead));
}


