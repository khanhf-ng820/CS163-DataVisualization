#include "HashTable/HashVisEngine.h"





HashVisEngine::HashVisEngine(sf::RenderWindow* window, sf::Font* font)
	: tableSize(5), windowPtr(window), fontPtr(font)
	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
{
	table.reserve(tableSize);
	// *** FOR TESTING ONLY, WILL DELETE LATER ***
	for (int i = 0; i < tableSize; i++)
		table[i] = TableSlot(i, -i);
}

HashVisEngine::HashVisEngine(int tableSize, sf::RenderWindow* window, sf::Font* font)
	: tableSize(tableSize), table(tableSize), windowPtr(window), fontPtr(font)
	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
{
	for (int i = 0; i < tableSize; i++)
		table[i] = TableSlot(i);
}

HashVisEngine::HashVisEngine(std::vector<int> values, sf::RenderWindow* window, sf::Font* font)
	: tableSize(values.size()), table(values.size()), windowPtr(window), fontPtr(font)
{
	for (int i = 0; i < tableSize; i++)
		table[i] = TableSlot(i);
}


void HashVisEngine::increaseTime() {
	time += dt;
}
void HashVisEngine::decreaseTime() {
	time -= dt;
}
void HashVisEngine::prevStep() {
	targetTime = time - 1;
	targetTime = floor(targetTime);
	targetTime = std::max(targetTime, 0.f);
}
void HashVisEngine::nextStep() {
	targetTime = time + 1;
	targetTime = floor(targetTime);
	targetTime = std::max(targetTime, 0.f);
}
void HashVisEngine::skipToFinalState() {
	time = std::max(100000, static_cast<int>(eventList.size() + 1));
	animPaused = false; // Auto un-pause
}

void HashVisEngine::resetParams() {
	curIndex = -1; // Index of slot currently animating

	searchSlotIdx = -1; // Index of slot currently animating
	insertKey = -1; // Key to assign/insert to the slot
	// insertVal = -1; // Value to assign/insert to the slot
	deleteKey = -1; // Key to delete from the slot
	// deleteVal = -1; // Value to delete from the slot

	highlightSlotIdx = -1; // Index of highlighted slot
	foundSlotIdx = -1; // Index of found slot when searching/updating

	animInProgress = false;
	animStepIndex = 0;
	oldAnimStepIndex = 0;
	time = 0;
}





// Draw nodes: Iterate through linked list and draw nodes
// --- NORMAL | SEARCH | UPDATE MODE ---
void HashVisEngine::addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, HashAnimStep eventHash) {
	for (int idx = 0; idx < tableSize; idx++) {
		sf::Vector2f slotPos = originPos + sf::Vector2f(idx * slotKeyRectSize.x, 0);
		drawSlot(drawableList, idx, table[idx].key, slotPos);
	}
}





void HashVisEngine::createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList) {
	drawableList.clear();


	// If STILL mode, stop here
	if (eventList.size() <= 1) {
		// Display nodes: Iterate through linked list and draw nodes
		addNodeDrawables(drawableList, HashAnimStep());
		return;
	}


	// change visCur and visCurIndex
	animStepIndex = std::min(static_cast<int>(floor(time)), static_cast<int>(eventList.size()) - 1);
	time = std::min(std::max(time, 0.f), static_cast<float>(eventList.size()) - 0.0005f);
	HashAnimStep eventHash = eventList[animStepIndex];
	// if (time == static_cast<float>(eventList.size())) eventHash = eventList.back();
	// Set parameters
	searchSlotIdx = eventHash.searchSlotIdx; // Set searchSlotIdx in the event
	// Less safe: animInProgress = (time != static_cast<float>(eventList.size()) - 0.0005f);
	animInProgress = (abs(time - (static_cast<float>(eventList.size()) - 0.0005f)) > EPSILON);

	if (animStepIndex > oldAnimStepIndex) {
		// if (eventList[oldAnimStepIndex].type == HashAnimType::MOVE_CUR_FORWARD) {
		// 	visCurIndex++;
		// 	visCur = visCur->pNext;
		// }
		oldAnimStepIndex = animStepIndex;
	}


	/*
	// INSERT MODE
	if (visMode == HashVisMode::INSERT_BEG || visMode == HashVisMode::INSERT_END || visMode == HashVisMode::INSERT_K) {
		// Display nodes: Iterate through linked list and draw nodes
		pInsert = ithNode(eventHash.idxInsert);
		idxInsert = eventHash.idxInsert;
		addNodeDrawablesInsert(drawableList, eventHash);
		drawHighlightCodeWindow(eventHash);
	} else if (visMode == HashVisMode::REMOVE_BEG || visMode == HashVisMode::REMOVE_K) {
	// REMOVE MODE
		addNodeDrawablesRemove(drawableList, eventHash);
		drawHighlightCodeWindow(eventHash);
	} else {
		addNodeDrawables(drawableList, eventHash);
		drawHighlightCodeWindow(eventHash);
	}
	*/


	// Display description for algorithm visualization
	auto descriptionText = std::make_unique<sf::Text>(*fontPtr, eventHash.desc, descriptionFontSize);
	descriptionText->setFillColor(sf::Color::Black);
	descriptionText->setPosition(originPos - originPosDisplacement + descriptionTextPos);

	// Display animation step
	/*
	auto curBox = std::make_unique<sf::RectangleShape>(nodeValueRectSize);
	auto pCurText = std::make_unique<sf::Text>(font, "pCur", valueFontSize);
	switch (eventHash.type) {
	case HashAnimType::NONE:
		curBox->setPosition(originPos
			+ sf::Vector2f(0, 100)
			// + static_cast<float>(visCurIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ static_cast<float>(eventHash.curIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);
		pCurText->setPosition(curBox->getPosition());
		break;
	case HashAnimType::CREATE_CUR:
		visCur = pHead;
		visCurIndex = 0;
		
		curBox->setPosition(originPos
			+ sf::Vector2f(0, 100)
			+ static_cast<float>(eventHash.curIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);
		pCurText->setPosition(curBox->getPosition());
		break;
	case HashAnimType::MOVE_CUR_FORWARD:
		curBox->setPosition(originPos
			+ sf::Vector2f(0, 100)
			+ static_cast<float>(eventHash.curIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
			+ lerp(sf::Vector2f(0, 0), sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f), fract(time))
		);
		pCurText->setPosition(curBox->getPosition());
		break;
	default:
		curBox->setPosition(originPos
			+ sf::Vector2f(0, 100)
			+ static_cast<float>(eventHash.curIndex) * sf::Vector2f(nodeRectSize.x + linkArrowLength, 0.f)
		);
		pCurText->setPosition(curBox->getPosition());
		break;
	}
	curBox->setFillColor(sf::Color::Transparent);
	curBox->setOutlineColor(sf::Color::Black);
	curBox->setOutlineThickness(2.f);
	pCurText->setFillColor(sf::Color::Black);
	// pCur arrow
	drawArrow(drawableList,
		curBox->getPosition() + sf::Vector2f(nodeValueRectSize.x/2, 0),
		curBox->getPosition() + sf::Vector2f(nodeValueRectSize.x/2, 0) - sf::Vector2f(0, 100) + sf::Vector2f(0, nodeRectSize.y)
	);
	*/

	drawableList.push_back(std::move(descriptionText));
	// drawableList.push_back(std::move(curBox));
	// drawableList.push_back(std::move(pCurText));

	std::cout << drawableList.size() << ' ' << time << " init done" << std::endl;
}







std::vector<HashAnimStep> HashVisEngine::getEventsSearch(int key) {
	std::vector<HashAnimStep> events;

	std::string description; // String for description of animation step
	description = "Hashing: h(" + std::to_string(key) + ") = " + std::to_string(hashFunc(key));
	events.push_back(HashAnimStep(HashAnimType::NONE, description, {}, -1));

	int hashResult = hashFunc(key);
	int moveSlotSteps = 0;
	for (int i = hashResult; moveSlotSteps < tableSize; i++, i %= tableSize, moveSlotSteps++) {
		description = "Checking slot of index " + std::to_string(i);
		events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_SLOT, description, {}, i));
		
		if (table[i].key == key) {
			description = "Found slot: key " + std::to_string(key) + ", value " + std::to_string(table[i].key);
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_FOUND_SLOT, description, {}, i));
			return events;
		}
	}

	events.push_back(HashAnimStep(HashAnimType::NONE, "No such slot found -> Stop.", {}, -1));
	return events;
}












int HashVisEngine::hashFunc(int key) {
	return ((key % tableSize) + tableSize) % tableSize;
}


void HashVisEngine::drawSlot(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, int slotIndex, int key, sf::Vector2f topLeftPos) const {
	/*
	// Draw Rect for VALUE of slot
	auto valRect = std::make_unique<sf::RectangleShape>(slotValRectSize);
	valRect->setFillColor(sf::Color::Transparent);
	valRect->setOutlineColor(normalSlotColor);
	valRect->setOutlineThickness(2.f);
	valRect->setPosition(topLeftPos);
	// Draw Text for VALUE of slot
	auto valueText = std::make_unique<sf::Text>(*font, std::to_string(value), valueFontSize);
	sf::FloatRect localBounds = valueText->getLocalBounds();
	valueText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	valueText->setFillColor(normalSlotValueColor);
	valueText->setPosition(valRect->getPosition() + slotValRectSize / 2.f);
	*/
	// Draw Rect for KEY of slot
	auto keyRect = std::make_unique<sf::RectangleShape>(slotKeyRectSize);
	keyRect->setFillColor(sf::Color::Transparent);
	keyRect->setOutlineColor(normalSlotColor);
	keyRect->setOutlineThickness(2.f);
	keyRect->setPosition(topLeftPos
		// + sf::Vector2f(0, slotValRectSize.y)
	);
	// Draw Text for KEY of slot
	auto keyText = std::make_unique<sf::Text>(*fontPtr, std::to_string(key), keyFontSize);
	sf::FloatRect localBounds = keyText->getLocalBounds();
	keyText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	keyText->setFillColor(normalSlotKeyColor);
	keyText->setPosition(keyRect->getPosition() + slotKeyRectSize / 2.f);

	// Draw Text for INDEX of slot
	auto indexText = std::make_unique<sf::Text>(*fontPtr, std::to_string(slotIndex), indexFontSize);
	localBounds = indexText->getLocalBounds();
	indexText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	indexText->setFillColor(normalSlotIndexColor);
	indexText->setPosition(keyRect->getPosition()
		+ sf::Vector2f(slotKeyRectSize.x / 2.f, slotKeyRectSize.y + slotIdxTextSpacing)
	);


	// drawableList.push_back(std::move(valRect));
	// drawableList.push_back(std::move(valText));
	drawableList.push_back(std::move(keyRect));
	drawableList.push_back(std::move(keyText));
	drawableList.push_back(std::move(indexText));
}
