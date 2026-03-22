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






// Draw nodes: Iterate through linked list and draw nodes
// --- NORMAL | SEARCH MODE ---
void AVLVisEngine::addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, AVLAnimStep eventAVL) {
	// for (int idx = 0; idx < tableSize; idx++) {
	// 	sf::Vector2f slotPos = originPos + sf::Vector2f(idx * slotKeyRectSize.x, 0);
	// 	drawSlot(drawableList, idx, table[idx].key, table[idx].empty, table[idx].deleted, slotPos);
	// }
	// for (int idx = 0; idx < tableSize; idx++) {
	// 	sf::Vector2f slotPos = originPos + sf::Vector2f(idx * slotKeyRectSize.x, 0);
	// 	if (idx == eventAVL.curIndex)
	// 		drawHighlightBorder(drawableList, idx, table[idx].key, slotPos, (eventAVL.type == AVLAnimType::HIGHLIGHT_FOUND_SLOT));
	// }

	refreshAllVisNodePos(visualNodesCur, tree.root);
	for (const auto& [key, visNode] : visualNodesCur) {
		drawNode(drawableList, visNode);
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
	nodeCircle->setOutlineThickness(1);
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


