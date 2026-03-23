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






// Draw nodes: Iterate through linked list and draw nodes
// --- NORMAL | SEARCH MODE ---
void AVLVisEngine::addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, AVLAnimStep eventAVL) {
	refreshAllVisNodePos(visualNodesCur, tree.root);
	drawTreeEdges(drawableList, tree.root, visualNodesCur);
	for (const auto& [key, visNode] : visualNodesCur) {
		drawNode(drawableList, visNode);
	}
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



	// if (visMode == AVLVisMode::INSERT) {
	// 	// INSERT MODE
	// 	addNodeDrawablesInsert(drawableList, eventAVL);
	// 	drawPseudocodeWindow(eventAVL);
	// } else if (visMode == AVLVisMode::REMOVE) {
	// 	// REMOVE MODE
	// 	addNodeDrawablesRemove(drawableList, eventAVL);
	// 	drawPseudocodeWindow(eventAVL);
	// } else if (visMode == AVLVisMode::UPDATE) {
	// 	// UPDATE MODE
	// 	addNodeDrawablesUpdate(drawableList, eventAVL);
	// 	drawPseudocodeWindow(eventAVL);
	// } else {
		addNodeDrawables(drawableList, eventAVL);
		// drawPseudocodeWindow(eventAVL);
	// }



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
void AVLVisEngine::refreshAllVisNodePos(std::map<int, VisualAVLNode>& visualNodes, LogicAVLNode* root) {
	visualNodes.clear();
	unsigned int size = tree.getSize();
	float xPos = canvasLeftMargin;
	float dx = (windowPtr->getSize().x - 2 * canvasLeftMargin) / (size > 1 ? size-1 : 1);
	int layerY = 0;
	// Prevent nodes overlapping
	if (dx < 2 * nodeCircleRadius) dx = 2 * nodeCircleRadius;

	refreshRecursiveVisNodePos(visualNodes, root, xPos, dx, layerY);
}


void AVLVisEngine::refreshRecursiveVisNodePos(std::map<int, VisualAVLNode>& visualNodes, LogicAVLNode* node, float& xPos, float dx, int& layerY) {
	if (!node) return;
	layerY++;
	refreshRecursiveVisNodePos(visualNodes, node->left, xPos, dx, layerY);
	layerY--;
	visualNodes[node->key] = VisualAVLNode(node->key,
		sf::Vector2f(originPos.x + xPos, originPos.y + layerY * nodeLayerSpacing)
	);
	xPos += dx;
	layerY++;
	refreshRecursiveVisNodePos(visualNodes, node->right, xPos, dx, layerY);
	layerY--;
}





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


// Draw tree edges
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


