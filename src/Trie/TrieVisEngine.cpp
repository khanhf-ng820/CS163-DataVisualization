#include "Trie/TrieVisEngine.h"




TrieVisEngine::TrieVisEngine(sf::RenderWindow* window, sf::Font* font)
	: windowPtr(window), fontPtr(font)
	// , normalWindowSize(window->getSize())
	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
{
	initInputBuffers();
}

TrieVisEngine::TrieVisEngine(std::mt19937& rng, sf::RenderWindow* window, sf::Font* font)
	: windowPtr(window), fontPtr(font)
	// , normalWindowSize(window->getSize())
	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
{
	initInputBuffers();
	std::uniform_int_distribution<size_t> size_distrib(TRIE_INIT_RANDOM_MIN_SIZE, TRIE_INIT_RANDOM_MAX_SIZE); // Number of words
	std::uniform_int_distribution<size_t> wordLen_distrib(TRIE_INIT_WORD_MIN_LENGTH, TRIE_INIT_WORD_MAX_LENGTH);
	std::uniform_int_distribution<int> char_distrib(TRIE_RANDOM_DISTRIB_KEY_MIN, TRIE_RANDOM_DISTRIB_KEY_MAX);

	size_t wordCount = size_distrib(rng);
	for (size_t i = 0; i < wordCount; i++) {
		size_t wordLen = wordLen_distrib(rng);
		std::string wordInit(wordLen, 'a');
		for (char& c : wordInit)
			c = static_cast<char>(char_distrib(rng));
		tree.insertWord(wordInit);
	}
}

TrieVisEngine::TrieVisEngine(std::vector<std::string>& words, sf::RenderWindow* window, sf::Font* font)
	: windowPtr(window), fontPtr(font)
	// , normalWindowSize(window->getSize())
	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
{
	initInputBuffers();
	size_t wordCount = words.size();
	for (size_t i = 0; i < wordCount; i++) {
		tree.insertWord(words[i]);
	}
}

// Delete all dynamically allocated memory
TrieVisEngine::~TrieVisEngine() {
	// delete[] wordToSearchInput;
	// delete[] wordToInsertInput;
	// delete[] wordToRemoveInput;
	// delete[] oldWordToUpdateInput;
	// delete[] newWordToUpdateInput;
}



// Reset all properties to get ready for visualize new action
///// MAKE SURE TO RESET ALL NECESSARY PROPERTIES
void TrieVisEngine::resetParams() {
	resetAnimParams();
}






///// --- LOGICAL ALGORITHMS AND EVENTS --- /////
// -- SEARCHING --
std::vector<TrieAnimStep> TrieVisEngine::getEventsSearch(std::string word) {
	std::vector<TrieAnimStep> events;
	oldTreeSnapshots.clear();
	oldTreeSnapshots.push_back(tree);

	events.push_back(TrieAnimStep(TrieAnimType::NONE, "Before searching word: \"" + word + "\"", {0}, 0, 0));
	tree.generateSearchEvents(word, events, oldTreeSnapshots);

	std::cerr << "Done generating insertion events!" << std::endl; // DEBUG
	std::cerr << ", size = " << tree.getSize() << std::endl; // DEBUG

	return events;
}



// -- INSERTION --
std::vector<TrieAnimStep> TrieVisEngine::getEventsInsert(std::string word) {
	std::vector<TrieAnimStep> events;
	oldTreeSnapshots.clear();
	oldTreeSnapshots.push_back(tree);
	unsigned int numWordsBefore = tree.getNumWords();

	events.push_back(TrieAnimStep(TrieAnimType::NONE, "Before inserting word: \"" + word + "\"", {0}, 0, oldTreeSnapshots.size() - 1));
	// Insert node into tree and get animation events
	LogicTrieNode* lastInsertedNode = tree.generateInsertEvents(word, events, oldTreeSnapshots);
	// // Remind to snapshot tree after insertion/rotation
	// tree.snapshotTree(key, events, oldTreeSnapshots);

	std::string descriptionString = (numWordsBefore != tree.getNumWords())
		? ("Finished inserting word: \"" + word + "\"")
		: ("Word \"" + word + "\" already exists, can\'t insert duplicates.");
	events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_FOUND_NODE, descriptionString, {7}, lastInsertedNode->getID(), -1));

	std::cerr << "Done generating insertion events!" << std::endl; // DEBUG
	std::cerr << ", size = " << tree.getSize() << std::endl; // DEBUG

	return events;
}



// -- DELETION --
std::vector<TrieAnimStep> TrieVisEngine::getEventsDelete(std::string word) {
	std::vector<TrieAnimStep> events;
	oldTreeSnapshots.clear();
	oldTreeSnapshots.push_back(tree);

	events.push_back(TrieAnimStep(TrieAnimType::NONE, "Before deleting word: \"" + word + "\"", {0}, 0, oldTreeSnapshots.size() -1));
	tree.generateDeleteEvents(word, events, oldTreeSnapshots);

	std::cerr << "Done generating deletion events!" << std::endl; // DEBUG
	std::cerr << ", size = " << tree.getSize() << std::endl; // DEBUG

	return events;
}



// -- UPDATING --
std::vector<TrieAnimStep> TrieVisEngine::getEventsUpdate(std::string oldWord, std::string newWord) {
	std::vector<TrieAnimStep> events;
	oldTreeSnapshots.clear();
	oldTreeSnapshots.push_back(tree);

	// --- Deletion step
	events.push_back(TrieAnimStep(TrieAnimType::NONE, "Before deleting word: \"" + oldWord + "\"", {0}, 0, oldTreeSnapshots.size() -1));
	tree.generateDeleteEvents(oldWord, events, oldTreeSnapshots);

	std::cerr << "Done generating deletion events!" << std::endl; // DEBUG
	std::cerr << ", size = " << tree.getSize() << std::endl; // DEBUG

	for (auto& event : events) {
		event.displayPseudocode = TrieDisplayPseudocode::DELETION;
	}
	unsigned int numDeletionEvents = events.size();


	// --- Insertion step
	unsigned int numWordsBefore = tree.getNumWords();

	oldTreeSnapshots.push_back(tree);
	events.push_back(TrieAnimStep(TrieAnimType::NONE, "Before inserting word: \"" + newWord + "\"", {0}, 0, oldTreeSnapshots.size() - 1));
	// Insert node into tree and get animation events
	LogicTrieNode* lastInsertedNode = tree.generateInsertEvents(newWord, events, oldTreeSnapshots);
	// // Remind to snapshot tree after insertion/rotation
	// tree.snapshotTree(key, events, oldTreeSnapshots);

	std::string descriptionString = (numWordsBefore != tree.getNumWords())
		? ("Finished inserting word: \"" + newWord + "\"")
		: ("Word \"" + newWord + "\" already exists, can\'t insert duplicates.");
	events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_FOUND_NODE, descriptionString, {7}, lastInsertedNode->getID(), -1));

	std::cerr << "Done generating insertion events!" << std::endl; // DEBUG
	std::cerr << ", size = " << tree.getSize() << std::endl; // DEBUG

	events.push_back(TrieAnimStep(TrieAnimType::HIGHLIGHT_FOUND_NODE, "Finished updating operation." , {}, lastInsertedNode->getID(), oldTreeSnapshots.size() -1));

	for (int i = numDeletionEvents; i < events.size(); i++) {
		events[i].displayPseudocode = TrieDisplayPseudocode::INSERTION;
	}

	return events;
}










// Draw nodes: Iterate through linked list and draw nodes
// --- NORMAL | SEARCH MODE ---
void TrieVisEngine::addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, TrieAnimStep eventTrie) {
	generateAllVisNodePos(visualNodesCur, tree);

	drawStillTree(drawableList, visualNodesCur, tree);

	// Draw highlighting circle
	switch (eventTrie.type) {
	case TrieAnimType::HIGHLIGHT_NODE:
		drawHighlightCircle(drawableList, visualNodesCur[eventTrie.curID].position, false);
		break;
	case TrieAnimType::HIGHLIGHT_FOUND_NODE:
		drawHighlightCircle(drawableList, visualNodesCur[eventTrie.curID].position, true);
		break;
	case TrieAnimType::MOVE_HIGHLIGHT_DOWN:
		if (tree.getNodeID(eventTrie.curID) && tree.getNodeID(eventTrie.curID)->getChild(eventTrie.charLink))
			drawHighlightCircle(drawableList,
				easeInOutLerp(visualNodesCur[eventTrie.curID].position, 
							  visualNodesCur[tree.getNodeID(eventTrie.curID)->getChild(eventTrie.charLink)->getID()].position, 
							  fract(time)),
				false);
		else
			drawHighlightCircle(drawableList, visualNodesCur[eventTrie.curID].position, false);
		break;
	case TrieAnimType::NONE:
	default:
		break;
	}
}





// --- INSERT MODE ---
void TrieVisEngine::addNodeDrawablesInsert(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, TrieAnimStep eventTrie) {
	groupsOldVisualNodes.clear();
	size_t numOfOldTreeSnapshots = oldTreeSnapshots.size();
	groupsOldVisualNodes.resize(numOfOldTreeSnapshots);

	// Generate all visual nodes, new and old
	generateAllVisNodePos(visualNodesCur, tree);
	for (int i = 0; i < numOfOldTreeSnapshots; i++) {
		generateAllVisNodePos(groupsOldVisualNodes[i], oldTreeSnapshots[i]);
	}
	std::cerr << "numOfOldTreeSnapshots = " << numOfOldTreeSnapshots << ", "; // DEBUG

	// Find old visual nodes and old tree snapshot
	std::map<int, VisualTrieNode>& oldVisualNodes =
		(eventTrie.oldTreeSnapshotIndex == -1) ? visualNodesCur : groupsOldVisualNodes[eventTrie.oldTreeSnapshotIndex];
	LogicTrie& oldTreeSnapshot =
		(eventTrie.oldTreeSnapshotIndex == -1) ? tree : oldTreeSnapshots[eventTrie.oldTreeSnapshotIndex];

	// Draw the tree
	switch (eventTrie.type) {
	case TrieAnimType::INSERT_NODE:
		// Node insertion animation
		drawLerpTreeInsertNode(drawableList,
			groupsOldVisualNodes[eventTrie.oldTreeSnapshotIndex - 1],
			oldTreeSnapshots[eventTrie.oldTreeSnapshotIndex - 1],
			oldVisualNodes, oldTreeSnapshot, 
			eventTrie.curID
		);
		break;
	default:
		drawStillTree(drawableList, oldVisualNodes, oldTreeSnapshot);
	}

	// Draw highlighting circle
	switch (eventTrie.type) {
	case TrieAnimType::HIGHLIGHT_NODE:
		drawHighlightCircle(drawableList, oldVisualNodes[eventTrie.curID].position, false);
		break;
	case TrieAnimType::HIGHLIGHT_FOUND_NODE:
	// case TrieAnimType::INSERT_NODE: // Highlight inserted node when at inserting event
		drawHighlightCircle(drawableList, oldVisualNodes[eventTrie.curID].position, true);
		break;
	case TrieAnimType::MOVE_HIGHLIGHT_DOWN:
		if (oldTreeSnapshot.getNodeID(eventTrie.curID) && oldTreeSnapshot.getNodeID(eventTrie.curID)->getChild(eventTrie.charLink)) {
			drawHighlightCircle(drawableList,
				easeInOutLerp(oldVisualNodes[eventTrie.curID].position, 
							  oldVisualNodes[oldTreeSnapshot.getNodeID(eventTrie.curID)->getChild(eventTrie.charLink)->getID()].position, 
							  fract(time)),
				false);
		} else {
			drawHighlightCircle(drawableList, oldVisualNodes[eventTrie.curID].position, false);
		}
		break;
	case TrieAnimType::NONE:
	default:
		break;
	}
}





// --- DELETE MODE ---
void TrieVisEngine::addNodeDrawablesDelete(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, TrieAnimStep eventTrie) {
	groupsOldVisualNodes.clear();
	size_t numOfOldTreeSnapshots = oldTreeSnapshots.size();
	groupsOldVisualNodes.resize(numOfOldTreeSnapshots);

	// Generate all visual nodes, new and old
	generateAllVisNodePos(visualNodesCur, tree);
	for (int i = 0; i < numOfOldTreeSnapshots; i++) {
		generateAllVisNodePos(groupsOldVisualNodes[i], oldTreeSnapshots[i]);
	}
	std::cerr << "numOfOldTreeSnapshots = " << numOfOldTreeSnapshots << ", "; // DEBUG

	// Find old visual nodes and old tree snapshot
	std::map<int, VisualTrieNode>& oldVisualNodes =
		(eventTrie.oldTreeSnapshotIndex == -1) ? visualNodesCur : groupsOldVisualNodes[eventTrie.oldTreeSnapshotIndex];
	LogicTrie& oldTreeSnapshot =
		(eventTrie.oldTreeSnapshotIndex == -1) ? tree : oldTreeSnapshots[eventTrie.oldTreeSnapshotIndex];

	// Draw the tree
	switch (eventTrie.type) {
	case TrieAnimType::DELETE_LEAF_NODE:
		// Node deletion animation
		drawLerpTreeDeleteNode(drawableList,
			groupsOldVisualNodes[eventTrie.oldTreeSnapshotIndex - 1],
			oldTreeSnapshots[eventTrie.oldTreeSnapshotIndex - 1],
			oldVisualNodes, oldTreeSnapshot,
			eventTrie.curID
		);
		break;
	default:
		drawStillTree(drawableList, oldVisualNodes, oldTreeSnapshot);
	}

	// Draw highlighting circle
	switch (eventTrie.type) {
	case TrieAnimType::HIGHLIGHT_NODE:
		drawHighlightCircle(drawableList, oldVisualNodes[eventTrie.curID].position, false);
		break;
	case TrieAnimType::HIGHLIGHT_FOUND_NODE:
		drawHighlightCircle(drawableList, oldVisualNodes[eventTrie.curID].position, true);
		break;
	case TrieAnimType::MOVE_HIGHLIGHT_DOWN:
		if (oldTreeSnapshot.getNodeID(eventTrie.curID) && oldTreeSnapshot.getNodeID(eventTrie.curID)->getChild(eventTrie.charLink)) {
			drawHighlightCircle(drawableList,
				easeInOutLerp(oldVisualNodes[eventTrie.curID].position, 
							  oldVisualNodes[oldTreeSnapshot.getNodeID(eventTrie.curID)->getChild(eventTrie.charLink)->getID()].position, 
							  fract(time)),
				false);
		} else {
			drawHighlightCircle(drawableList, oldVisualNodes[eventTrie.curID].position, false);
		}
		break;
	case TrieAnimType::NONE:
	default:
		break;
	}
}





// --- UPDATE MODE ---
void TrieVisEngine::addNodeDrawablesUpdate(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, TrieAnimStep eventTrie) {
	groupsOldVisualNodes.clear();
	size_t numOfOldTreeSnapshots = oldTreeSnapshots.size();
	groupsOldVisualNodes.resize(numOfOldTreeSnapshots);

	// Generate all visual nodes, new and old
	generateAllVisNodePos(visualNodesCur, tree);
	for (int i = 0; i < numOfOldTreeSnapshots; i++) {
		generateAllVisNodePos(groupsOldVisualNodes[i], oldTreeSnapshots[i]);
	}
	std::cerr << "numOfOldTreeSnapshots = " << numOfOldTreeSnapshots << ", "; // DEBUG

	// Find old visual nodes and old tree snapshot
	std::map<int, VisualTrieNode>& oldVisualNodes =
		(eventTrie.oldTreeSnapshotIndex == -1) ? visualNodesCur : groupsOldVisualNodes[eventTrie.oldTreeSnapshotIndex];
	LogicTrie& oldTreeSnapshot =
		(eventTrie.oldTreeSnapshotIndex == -1) ? tree : oldTreeSnapshots[eventTrie.oldTreeSnapshotIndex];

	// Draw the tree
	switch (eventTrie.type) {
	case TrieAnimType::INSERT_NODE:
		// Node insertion animation
		drawLerpTreeInsertNode(drawableList,
			groupsOldVisualNodes[eventTrie.oldTreeSnapshotIndex - 1],
			oldTreeSnapshots[eventTrie.oldTreeSnapshotIndex - 1],
			oldVisualNodes, oldTreeSnapshot, 
			eventTrie.curID
		);
		break;
	case TrieAnimType::DELETE_LEAF_NODE:
		// Node deletion animation
		drawLerpTreeDeleteNode(drawableList,
			groupsOldVisualNodes[eventTrie.oldTreeSnapshotIndex - 1],
			oldTreeSnapshots[eventTrie.oldTreeSnapshotIndex - 1],
			oldVisualNodes, oldTreeSnapshot,
			eventTrie.curID
		);
		break;
	default:
		drawStillTree(drawableList, oldVisualNodes, oldTreeSnapshot);
	}

	// Draw highlighting circle
	switch (eventTrie.type) {
	case TrieAnimType::HIGHLIGHT_NODE:
		drawHighlightCircle(drawableList, oldVisualNodes[eventTrie.curID].position, false);
		break;
	case TrieAnimType::HIGHLIGHT_FOUND_NODE:
		drawHighlightCircle(drawableList, oldVisualNodes[eventTrie.curID].position, true);
		break;
	case TrieAnimType::MOVE_HIGHLIGHT_DOWN:
		if (oldTreeSnapshot.getNodeID(eventTrie.curID) && oldTreeSnapshot.getNodeID(eventTrie.curID)->getChild(eventTrie.charLink)) {
			drawHighlightCircle(drawableList,
				easeInOutLerp(oldVisualNodes[eventTrie.curID].position, 
							  oldVisualNodes[oldTreeSnapshot.getNodeID(eventTrie.curID)->getChild(eventTrie.charLink)->getID()].position, 
							  fract(time)),
				false);
		} else {
			drawHighlightCircle(drawableList, oldVisualNodes[eventTrie.curID].position, false);
		}
		break;
	case TrieAnimType::NONE:
	default:
		break;
	}
}





// Create AND display ImGui window to highlight source code (pseudocode)
void TrieVisEngine::drawPseudocodeWindow(TrieAnimStep eventTrie) {
	ImGui::Begin("Pseudocode", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::PushFont(pseudocodeFont);

	switch (visMode) {
	case TrieVisMode::SEARCH:
		for (int i = 0; i < TRIE_CODE_SEARCH.size(); i++) {
			bool highlightLine = vecContains(eventTrie.highlightCodeLineIndex, i);
			if (highlightLine)
				ImGui::PushStyleColor(ImGuiCol_Text, highlightCodeColor);
			ImGui::Text("%s", TRIE_CODE_SEARCH[i].c_str());
			if (highlightLine)
				ImGui::PopStyleColor();
		}
		break;
	case TrieVisMode::UPDATE:
		switch (eventTrie.displayPseudocode) {
		case TrieDisplayPseudocode::DELETION:
			for (int i = 0; i < TRIE_CODE_DELETE.size(); i++) {
				bool highlightLine = vecContains(eventTrie.highlightCodeLineIndex, i);
				if (highlightLine)
					ImGui::PushStyleColor(ImGuiCol_Text, highlightCodeColor);
				ImGui::Text("%s", TRIE_CODE_DELETE[i].c_str());
				if (highlightLine)
					ImGui::PopStyleColor();
			}
			break;
		case TrieDisplayPseudocode::INSERTION:
		default:
			for (int i = 0; i < TRIE_CODE_INSERT.size(); i++) {
				bool highlightLine = vecContains(eventTrie.highlightCodeLineIndex, i);
				if (highlightLine)
					ImGui::PushStyleColor(ImGuiCol_Text, highlightCodeColor);
				ImGui::Text("%s", TRIE_CODE_INSERT[i].c_str());
				if (highlightLine)
					ImGui::PopStyleColor();
			}
			break;
		}
		break;
	case TrieVisMode::INSERT:
		for (int i = 0; i < TRIE_CODE_INSERT.size(); i++) {
			bool highlightLine = vecContains(eventTrie.highlightCodeLineIndex, i);
			if (highlightLine)
				ImGui::PushStyleColor(ImGuiCol_Text, highlightCodeColor);
			ImGui::Text("%s", TRIE_CODE_INSERT[i].c_str());
			if (highlightLine)
				ImGui::PopStyleColor();
		}
		break;
	case TrieVisMode::REMOVE:
		for (int i = 0; i < TRIE_CODE_DELETE.size(); i++) {
			bool highlightLine = vecContains(eventTrie.highlightCodeLineIndex, i);
			if (highlightLine)
				ImGui::PushStyleColor(ImGuiCol_Text, highlightCodeColor);
			ImGui::Text("%s", TRIE_CODE_DELETE[i].c_str());
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










// Draw nodes and links, depending on eventList
void TrieVisEngine::createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::vector<std::unique_ptr<sf::Drawable>>& drawableListDefaultView) {
	refreshOriginPos(); // Refresh properties when window size changes
	drawableList.clear();
	drawableListDefaultView.clear();


	// If STILL mode, stop here
	if (eventList.size() <= 1) {
		// Display nodes: Iterate through linked list and draw nodes
		addNodeDrawables(drawableList, TrieAnimStep());
		return;
	}


	// change visCur and visCurIndex
	animStepIndex = std::min(static_cast<int>(floor(time)), static_cast<int>(eventList.size()) - 1);
	time = std::min(std::max(time, 0.f), static_cast<float>(eventList.size()) - 0.0005f);
	TrieAnimStep eventTrie = eventList[animStepIndex];
	// if (time == static_cast<float>(eventList.size())) eventTrie = eventList.back();
	// Set parameters
	// searchSlotIdx = eventTrie.searchSlotIdx; // Set searchSlotIdx in the event
	// Less safe: animInProgress = (time != static_cast<float>(eventList.size()) - 0.0005f);
	animInProgress = (abs(time - (static_cast<float>(eventList.size()) - 0.0005f)) > EPSILON_TIME);

	if (animStepIndex > oldAnimStepIndex) {
		// if (eventList[oldAnimStepIndex].type == TrieAnimType::MOVE_CUR_FORWARD) {
		// 	visCurIndex++;
		// 	visCur = visCur->pNext;
		// }
		oldAnimStepIndex = animStepIndex;
	}



	if (visMode == TrieVisMode::INSERT) {
		// INSERT MODE
		addNodeDrawablesInsert(drawableList, eventTrie);
		drawPseudocodeWindow(eventTrie);
	} else if (visMode == TrieVisMode::REMOVE) {
		// REMOVE MODE
		addNodeDrawablesDelete(drawableList, eventTrie);
		drawPseudocodeWindow(eventTrie);
	} else if (visMode == TrieVisMode::UPDATE) {
		// UPDATE MODE
		addNodeDrawablesUpdate(drawableList, eventTrie);
		drawPseudocodeWindow(eventTrie);
	} else {
		// SEARCH MODE
		addNodeDrawables(drawableList, eventTrie);
		drawPseudocodeWindow(eventTrie);
	}



	// Display description for algorithm visualization
	auto descriptionText = std::make_unique<sf::Text>(*fontPtr, eventTrie.description, descriptionFontSize);
	descriptionText->setFillColor(normalNodeColor);
	descriptionText->setPosition(descriptionTextPos);
	descriptionText->setPosition(round(descriptionText->getPosition()));

	drawableListDefaultView.push_back(std::move(descriptionText));


	std::cout << drawableList.size() << ' ' << time << " init done" << std::endl; // DEBUG
}












// Set correct positions for ALL VISUAL nodes
// Uses inorder positioning
void TrieVisEngine::generateAllVisNodePos(std::map<int, VisualTrieNode>& visualNodes, LogicTrie& logicTree) {
	generateAllVisNodePosXHelper(visualNodes, logicTree, logicTree.root);
	generateAllVisNodePosYHelper(visualNodes, logicTree, logicTree.root);
}


void TrieVisEngine::generateAllVisNodePosXHelper(std::map<int, VisualTrieNode>& visualNodes, LogicTrie& logicTree, LogicTrieNode* root) {
	visualNodes.clear();
	unsigned int size = logicTree.countLeaf();
	float xPos = canvasLeftMargin;
	float dx = (normalWindowSize.x - 2 * canvasLeftMargin) / (size > 1 ? size-1 : 1);
	// Prevent nodes overlapping
	if (dx < 2 * nodeCircleRadius) dx = 2 * nodeCircleRadius;

	generateRecursiveVisNodePosX(visualNodes, root, xPos, dx);
}

void TrieVisEngine::generateRecursiveVisNodePosX(std::map<int, VisualTrieNode>& visualNodes, LogicTrieNode* node, float& xPos, float dx) {
	if (!node) return;

	for (int i = 0; i < TRIE_ALPHABET_SIZE; i++)
		generateRecursiveVisNodePosX(visualNodes, node->children[i], xPos, dx);
	float nodePosX = 0;
	if (!node->isLeaf()) {
		unsigned int childrenCnt = 0;
		for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
			if (!node->children[i]) continue;
			nodePosX += visualNodes[node->children[i]->getID()].position.x;
			childrenCnt++;
		}
		nodePosX /= childrenCnt;
	} else {
		nodePosX = originPos.x + xPos;
	}
	visualNodes[node->getID()] = VisualTrieNode(node->getID(), node->key, node->isEndOfWord, 
		sf::Vector2f(nodePosX, originPos.y)
	);
	if (node->isLeaf())
		xPos += dx;
}


void TrieVisEngine::generateAllVisNodePosYHelper(std::map<int, VisualTrieNode>& visualNodes, LogicTrie& logicTree, LogicTrieNode* root) {
	// visualNodes.clear();
	unsigned int size = logicTree.countLeaf();
	int layerY = 0;

	generateRecursiveVisNodePosY(visualNodes, root, layerY);
}

void TrieVisEngine::generateRecursiveVisNodePosY(std::map<int, VisualTrieNode>& visualNodes, LogicTrieNode* node, int& layerY) {
	if (!node) return;

	visualNodes[node->getID()].position.y += layerY * nodeLayerSpacing;
	layerY++;
	for (int i = 0; i < TRIE_ALPHABET_SIZE; i++)
		generateRecursiveVisNodePosY(visualNodes, node->children[i], layerY);
	layerY--;
}






///// --- DRAWING FUNCTIONS ---
// Draw a node (a circle with the key as text inside it)
void TrieVisEngine::drawNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualTrieNode& visNode) {
	// Draw circle
	auto nodeCircle = std::make_unique<sf::CircleShape>(nodeCircleRadius);
	nodeCircle->setOrigin({nodeCircle->getRadius(), nodeCircle->getRadius()}); 
	nodeCircle->setFillColor(visNode.isEndOfWord ? normalNodeEOW_BGColor : sf::Color::Transparent);
	nodeCircle->setOutlineColor(normalNodeColor);
	nodeCircle->setOutlineThickness(nodeOutlineThickness);
	nodeCircle->setPosition(visNode.position);
	// Draw key text
	auto nodeKeyText = std::make_unique<sf::Text>(*fontPtr, std::string(1, visNode.key), nodeKeyTextFontSize);
	sf::FloatRect localBounds = nodeKeyText->getLocalBounds();
	nodeKeyText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	nodeKeyText->setFillColor(normalNodeKeyColor);
	nodeKeyText->setPosition(nodeCircle->getPosition());
	nodeKeyText->setPosition(round(nodeKeyText->getPosition()));
	// // Draw height text
	// auto nodeHeightText = std::make_unique<sf::Text>(*fontPtr, std::to_string(visNode.height), nodeHeightTextFontSize);
	// localBounds = nodeHeightText->getLocalBounds();
	// nodeHeightText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	// nodeHeightText->setFillColor(normalNodeHeightColor);
	// nodeHeightText->setPosition(nodeCircle->getPosition() + sf::Vector2f(nodeCircleRadius, -nodeCircleRadius));
	// nodeHeightText->setPosition(round(nodeHeightText->getPosition()));

	drawableList.push_back(std::move(nodeCircle));
	drawableList.push_back(std::move(nodeKeyText));
	// drawableList.push_back(std::move(nodeHeightText));
}


// Draw the highlight circle (a circle highlighting a node)
void TrieVisEngine::drawHighlightCircle(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f center, bool isFoundNode) {
	auto highlightCircle = std::make_unique<sf::CircleShape>(nodeCircleRadius + highlightCircleThickness / 2);
	highlightCircle->setOrigin({highlightCircle->getRadius(), highlightCircle->getRadius()}); 
	highlightCircle->setFillColor(sf::Color::Transparent);
	highlightCircle->setOutlineColor(isFoundNode ? highlightCircleColor : highlightFoundCircleColor);
	highlightCircle->setOutlineThickness(highlightCircleThickness);
	highlightCircle->setPosition(center);
	drawableList.push_back(std::move(highlightCircle));
}


// Draw tree edges (arrows)
void TrieVisEngine::drawTreeEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const LogicTrieNode* root, std::map<int, VisualTrieNode>& visualNodes) {
	if (!root) return;
	for (int i = 0; i < TRIE_ALPHABET_SIZE; i++)
		drawTreeEdges(drawableList, root->children[i], visualNodes);
	for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
		if (root->children[i]) {
			sf::Vector2f start = visualNodes[root->getID()].position, end = visualNodes[root->children[i]->getID()].position;
			drawNodeArrow(drawableList, start, end);
		}
	}
}


void TrieVisEngine::drawStillTree(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::map<int, VisualTrieNode>& visualNodes, LogicTrie& logicTree) {
	drawTreeEdges(drawableList, logicTree.root, visualNodes);
	for (const auto& [key, visNode] : visualNodes) {
		drawNode(drawableList, visNode);
	}
}



// Draw lerped node
void TrieVisEngine::drawLerpNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualTrieNode& visNode1, const VisualTrieNode& visNode2) {
	// Draw circle
	auto nodeCircle = std::make_unique<sf::CircleShape>(nodeCircleRadius);
	nodeCircle->setOrigin({nodeCircle->getRadius(), nodeCircle->getRadius()}); 
	nodeCircle->setFillColor(visNode1.isEndOfWord ? normalNodeEOW_BGColor : sf::Color::Transparent);
	nodeCircle->setOutlineColor(normalNodeColor);
	nodeCircle->setOutlineThickness(nodeOutlineThickness);
	nodeCircle->setPosition(easeInOutLerp(visNode1.position, visNode2.position, fract(time)));
	// Draw key text
	auto nodeKeyText = std::make_unique<sf::Text>(*fontPtr, std::string(1, visNode1.key), nodeKeyTextFontSize);
	sf::FloatRect localBounds = nodeKeyText->getLocalBounds();
	nodeKeyText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	nodeKeyText->setFillColor(normalNodeKeyColor);
	nodeKeyText->setPosition(nodeCircle->getPosition());
	nodeKeyText->setPosition(round(nodeKeyText->getPosition()));
	// // Draw height text
	// auto nodeHeightText = std::make_unique<sf::Text>(*fontPtr, std::to_string(visNode.height), nodeHeightTextFontSize);
	// localBounds = nodeHeightText->getLocalBounds();
	// nodeHeightText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	// nodeHeightText->setFillColor(normalNodeHeightColor);
	// nodeHeightText->setPosition(nodeCircle->getPosition() + sf::Vector2f(nodeCircleRadius, -nodeCircleRadius));
	// nodeHeightText->setPosition(round(nodeHeightText->getPosition()));

	drawableList.push_back(std::move(nodeCircle));
	drawableList.push_back(std::move(nodeKeyText));
	// drawableList.push_back(std::move(nodeHeightText));
}

// Draw lerped tree edges (arrows)
void TrieVisEngine::drawLerpTreeEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const LogicTrieNode* root,
	std::map<int, VisualTrieNode>& visualNodes1, std::map<int, VisualTrieNode>& visualNodes2) {
	if (!root) return;
	for (int i = 0; i < TRIE_ALPHABET_SIZE; i++)
		drawLerpTreeEdges(drawableList, root->children[i], visualNodes1, visualNodes2);
	for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
		if (!root->children[i]) continue;
		sf::Vector2f start = easeInOutLerp(visualNodes1[root->getID()].position, visualNodes2[root->getID()].position, fract(time));
		sf::Vector2f end = easeInOutLerp(visualNodes1[root->children[i]->getID()].position, 
										 visualNodes2[root->children[i]->getID()].position, 
										 fract(time));
		drawNodeArrow(drawableList, start, end);
	}
}

// Draw lerped tree (nodes and edges)
void TrieVisEngine::drawLerpTree(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
	std::map<int, VisualTrieNode>& visualNodes1, LogicTrie& logicTree1,
	std::map<int, VisualTrieNode>& visualNodes2, LogicTrie& logicTree2) {
	drawLerpTreeEdges(drawableList, logicTree2.root, visualNodes1, visualNodes2);
	for (const auto& [ID, visNode2] : visualNodes2) {
		drawLerpNode(drawableList, visualNodes1[ID], visNode2);
	}
}

// Draw lerped tree when inserting a node
void TrieVisEngine::drawLerpTreeInsertNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
	std::map<int, VisualTrieNode>& visualNodes1, LogicTrie& logicTree1,
	std::map<int, VisualTrieNode>& visualNodes2, LogicTrie& logicTree2,
	uint64_t nodeInsertID) {
	LogicTrie logicTreeBefore = logicTree2;
	std::map<int, VisualTrieNode> visualNodesBefore = visualNodes2;
	for (const auto& [ID, visNode1] : visualNodes1) {
		visualNodesBefore[ID].position = visNode1.position;
	}
	visualNodesBefore[nodeInsertID].position = originPos + newNodeStartPos;
	drawLerpTree(drawableList, visualNodesBefore, logicTreeBefore, visualNodes2, logicTree2);
}

// Draw lerped tree when deleting a node
void TrieVisEngine::drawLerpTreeDeleteNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
	std::map<int, VisualTrieNode>& visualNodes1, LogicTrie& logicTree1,
	std::map<int, VisualTrieNode>& visualNodes2, LogicTrie& logicTree2,
	uint64_t nodeRemoveID) {
	LogicTrie logicTreeBefore = logicTree2;
	std::map<int, VisualTrieNode> visualNodesBefore = visualNodes2;
	for (const auto& [ID, visNode1] : visualNodes1) {
		if (ID != nodeRemoveID)
			visualNodesBefore[ID].position = visNode1.position;
	}
	// visualNodesBefore[nodeRemoveID].position = originPos + newNodeStartPos;
	drawLerpTree(drawableList, visualNodesBefore, logicTreeBefore, visualNodes2, logicTree2);
}





// Helper drawing functions
void TrieVisEngine::drawNodeArrow(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f start, sf::Vector2f end) {
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
	(*arrowBody)[0].color = normalNodeArrowColor;
	(*arrowBody)[1].position = end;
	(*arrowBody)[1].color = normalNodeArrowColor;

	auto arrowHead = std::make_unique<sf::VertexArray>(sf::PrimitiveType::Triangles, 3);
	(*arrowHead)[0].position = end;
	(*arrowHead)[0].color = normalNodeArrowColor;
	(*arrowHead)[1].position = sf::Vector2f(leftX, leftY);
	(*arrowHead)[1].color = normalNodeArrowColor;
	(*arrowHead)[2].position = sf::Vector2f(rightX, rightY);
	(*arrowHead)[2].color = normalNodeArrowColor;

	drawableList.push_back(std::move(arrowBody));
	drawableList.push_back(std::move(arrowHead));
}





void TrieVisEngine::initInputBuffers() {
	wordToSearchInput[0] = '\0';
	wordToInsertInput[0] = '\0';
	wordToRemoveInput[0] = '\0';
	oldWordToUpdateInput[0] = '\0';
	newWordToUpdateInput[0] = '\0';
}

void TrieVisEngine::refreshOriginPos() {
	originPos = originPosDisplacement - sf::Vector2f(normalWindowSize) / 2.f;
}





// Set vis themes
void TrieVisEngine::setVisTheme(VIS_THEME visTheme) {
	switch (visTheme) {
	case VIS_THEME::LIGHT:
		setLightVisTheme();
		break;
	case VIS_THEME::DARK:
		setDarkVisTheme();
		break;
	}
}

void TrieVisEngine::setLightVisTheme() {
	normalNodeColor           = lightNormalNodeColor;
	normalNodeKeyColor        = lightNormalNodeKeyColor;
	normalNodeArrowColor      = lightNormalNodeArrowColor;
	normalNodeEOW_BGColor     = lightNormalNodeEOW_BGColor;
	highlightCircleColor      = lightHighlightCircleColor;
	highlightFoundCircleColor = lightHighlightFoundCircleColor;
}

void TrieVisEngine::setDarkVisTheme() {
	normalNodeColor           = darkNormalNodeColor;
	normalNodeKeyColor        = darkNormalNodeKeyColor;
	normalNodeArrowColor      = darkNormalNodeArrowColor;
	normalNodeEOW_BGColor     = darkNormalNodeEOW_BGColor;
	highlightCircleColor      = darkHighlightCircleColor;
	highlightFoundCircleColor = darkHighlightFoundCircleColor;
}
