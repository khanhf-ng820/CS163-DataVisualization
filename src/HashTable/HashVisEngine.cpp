#include "HashTable/HashVisEngine.h"





HashVisEngine::HashVisEngine(sf::RenderWindow* window, sf::Font* font)
	// *** tableSize FOR TESTING ONLY, WILL DELETE LATER ***
	: tableSize(11), tableModulo(11), windowPtr(window), fontPtr(font)
	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
{
	// *** FOR TESTING ONLY, WILL DELETE LATER ***
	table.resize(tableSize);
	// for (int i = 0; i < tableSize/2; i++)
	// 	table[i] = TableSlot(i, i);
	// for (int i = tableSize/2; i < tableSize; i++)
	// 	table[i] = TableSlot(i);
	for (int i = 0; i < tableSize; i++)
		table[i] = TableSlot(i);
}

HashVisEngine::HashVisEngine(int tableSize, int tableModulo, sf::RenderWindow* window, sf::Font* font)
	: tableSize(tableSize), tableModulo(tableModulo), table(tableSize)
	, windowPtr(window), fontPtr(font)
	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
{
	for (int i = 0; i < tableSize; i++)
		table[i] = TableSlot(i);
}

HashVisEngine::HashVisEngine(int tableSize, int tableModulo, std::mt19937& rng, sf::RenderWindow* window, sf::Font* font)
	: tableSize(tableSize), tableModulo(tableModulo), table(tableSize)
	, windowPtr(window), fontPtr(font)
	, originPos(originPosDisplacement - sf::Vector2f(window->getSize()) / 2.f)
{
	std::uniform_int_distribution<int> distrib(RANDOM_DISTRIB_KEY_MIN, RANDOM_DISTRIB_KEY_MAX);
	for (int i = 0; i < tableSize; i++)
		table[i] = TableSlot(i, distrib(rng));
}

HashVisEngine::HashVisEngine(std::vector<TableSlotInput>& values, int tableModulo, sf::RenderWindow* window, sf::Font* font)
	: HashVisEngine(values.size(), tableModulo, window, font)
{
	for (int i = 0; i < tableSize; i++) {
		table[i] = TableSlot(i, values[i]);
	}
}



///// MAKE SURE TO RESET ALL NECESSARY PROPERTIES
void HashVisEngine::resetParams() {
	curIndex = -1; // Index of slot currently animating

	searchSlotIdx = -1; // Index of slot currently animating

	oldKeySlot = -1; // Old key of slot before changes
	isOldSlotDeleted = false; // Did old slot before changes have deletion marker?

	insertSlotIdx = -1; // Index of inserted slot
	insertKey = -1; // Key to assign/insert to the slot
	// insertVal = -1; // Value to assign/insert to the slot

	removeSlotIdx = -1; // Index of slot to remove
	removeStoppingSlotIdx = -1; // Index of slot to stop at after failing to remove
	// removeVal = -1; // Value to remove from the slot

	highlightSlotIdx = -1; // Index of highlighted slot
	foundSlotIdx = -1; // Index of found slot when searching/updating

	resetAnimParams();
}





// // Initialize table data
// // Empty HashTable
// void HashVisEngine::initHashTableData() {}
// // Randomized HashTable
// void HashVisEngine::initHashTableData(std::mt19937& rng)
// // Specific data HashTable
// void HashVisEngine::initHashTableData(std::vector<int> initData)










// ///// ALGORITHMS /////
// --- SEARCH ---
std::vector<HashAnimStep> HashVisEngine::getEventsSearch(int key) {
	std::vector<HashAnimStep> events;

	std::string description; // String for description of animation step
	description = hashDescriptionString(key);
	events.push_back(HashAnimStep(HashAnimType::NONE, description, {0,1}, -1));

	int hashResult = hashFunc(key);
	int moveSlotSteps = 0;
	for (int i = hashResult; moveSlotSteps < tableSize; i++, i %= tableSize, moveSlotSteps++) {
		description = "Checking key of slot of index " + std::to_string(i);
		if (moveSlotSteps == 0)
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_SLOT, description, {3}, i));
		else
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_SLOT, description, {3,8}, i));

		if (table[i].empty && !table[i].deleted) {
			description = "Found empty slot with no deletion marker.";
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_SLOT, description, {4,5}, i));
			break;
		} else if (table[i].hasKey(key)) {
			// description = "Found slot: key " + std::to_string(key) + ", value " + std::to_string(table[i].key);
			description = "Found slot: key " + std::to_string(key) + ", index " + std::to_string(i);
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_FOUND_SLOT, description, {6,7}, i));
			searchSlotIdx = i; // Index of slot found
			return events;
		}
	}

	events.push_back(HashAnimStep(HashAnimType::NONE, "No such slot found to search -> Stop.", {9,10}, -1));
	return events;
}



// --- INSERT ---
void HashVisEngine::insert(int key) {
	int hashResult = hashFunc(key);
	int moveSlotSteps = 0;
	for (int i = hashResult; moveSlotSteps < tableSize; i++, i %= tableSize, moveSlotSteps++) {
		if (table[i].empty) {
			oldKeySlot = table[i].key;
			isOldSlotDeleted = table[i].deleted;
			insertSlotIdx = i;
			insertKey = key;

			table[i].key = key;
			table[i].empty = false;
			table[i].deleted = false;
			return; // Stop after inserting
		}
	}
	insertSlotIdx = -1; // Can't insert
}

std::vector<HashAnimStep> HashVisEngine::getEventsInsert(int key) {
	std::vector<HashAnimStep> events;

	std::string description; // String for description of animation step
	description = hashDescriptionString(key);
	events.push_back(HashAnimStep(HashAnimType::NONE, description, {0,1}, -1));

	int hashResult = hashFunc(key);
	int moveSlotSteps = 0;
	for (int i = hashResult; moveSlotSteps < tableSize; i++, i %= tableSize, moveSlotSteps++) {
		description = "Checking if slot of index " + std::to_string(i) + " is empty";
		if (moveSlotSteps == 0)
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_SLOT, description, {3}, i));
		else
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_SLOT, description, {3,7}, i));

		if (i == insertSlotIdx) {
			description = "Found empty slot: index " + std::to_string(i);
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_SLOT, description, {4}, i));
			description = "Assigning " + std::to_string(key) + " to slot index " + std::to_string(i);
			events.push_back(HashAnimStep(HashAnimType::SET_KEY_TO_SLOT, description, {5,6}, i));
			return events;
		}
	}

	events.push_back(HashAnimStep(HashAnimType::NONE, "No empty slots found -> Cannot insert key.", {8,9}, -1));
	return events;
}



// --- REMOVE ---
void HashVisEngine::remove(int key) {
	int hashResult = hashFunc(key);
	int moveSlotSteps = 0;
	for (int i = hashResult; moveSlotSteps < tableSize; i++, i %= tableSize, moveSlotSteps++) {
		if (table[i].empty && !table[i].deleted) {
			removeSlotIdx = -1; // Can't remove
			removeStoppingSlotIdx = i; // Failed to remove
			return;
		} else if (table[i].hasKey(key)) {
			oldKeySlot = key;
			removeSlotIdx = i;
			removeStoppingSlotIdx = -1; // Success removal

			table[i].key = -1;
			table[i].empty = true;
			table[i].deleted = true;
			return; // Stop after deleting
		}
	}
}

std::vector<HashAnimStep> HashVisEngine::getEventsRemove(int key) {
	std::vector<HashAnimStep> events;

	std::string description; // String for description of animation step
	description = hashDescriptionString(key);
	events.push_back(HashAnimStep(HashAnimType::NONE, description, {0,1}, -1));

	int hashResult = hashFunc(key);
	int moveSlotSteps = 0;
	for (int i = hashResult; moveSlotSteps < tableSize; i++, i %= tableSize, moveSlotSteps++) {
		description = "Checking key of slot of index " + std::to_string(i);
		if (moveSlotSteps == 0)
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_SLOT, description, {3}, i));
		else
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_SLOT, description, {3,9}, i));

		if (i == removeStoppingSlotIdx) {
			if (table[i].empty && !table[i].deleted) {
				description = "Found empty slot with no deletion marker.";
				events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_SLOT, description, {4,5}, i));
			}
			break;
		} else if (i == removeSlotIdx) {
			description = "Found slot: key " + std::to_string(key) + ", index " + std::to_string(i);
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_FOUND_SLOT, description, {6}, i));
			description = "Remove key from node index " + std::to_string(i) + ", add deletion marker.";
			events.push_back(HashAnimStep(HashAnimType::SET_DELETED_TO_SLOT, description, {7,8}, i));
			return events;
		}
	}

	events.push_back(HashAnimStep(HashAnimType::NONE, "No such slot found to remove -> Stop.", {10,11}, -1));
	return events;
}



// --- UPDATE ---
void HashVisEngine::update(int key, int newKey) {
	int hashResult = hashFunc(key);
	int moveSlotSteps = 0;
	for (int i = hashResult; moveSlotSteps < tableSize; i++, i %= tableSize, moveSlotSteps++) {
		if (table[i].empty && !table[i].deleted) {
			oldSlotRemoval = TableSlot(-1);
			break;
		} else if (table[i].hasKey(key)) {
			oldSlotRemoval = TableSlot(i, key);

			table[i].key = -1;
			table[i].empty = true;
			table[i].deleted = true;
			break; // Stop after deleting
		}
	}

	hashResult = hashFunc(newKey);
	moveSlotSteps = 0;
	for (int i = hashResult; moveSlotSteps < tableSize; i++, i %= tableSize, moveSlotSteps++) {
		if (table[i].empty) {
			oldSlotInsert = TableSlot(i);
			oldSlotInsert.deleted = table[i].deleted;

			table[i].key = newKey;
			table[i].empty = false;
			table[i].deleted = false;
			return; // Stop after inserting
		}
	}
	insertSlotIdx = -1; // Can't insert
}


std::vector<HashAnimStep> HashVisEngine::getEventsUpdate(int key, int newKey) {
	std::vector<HashAnimStep> events;

	// Remove key step
	std::string description; // String for description of animation step
	description = hashDescriptionString(key);
	events.push_back(HashAnimStep(HashAnimType::NONE, description, {0,1}, -1));

	int hashResult = hashFunc(key);
	int moveSlotSteps = 0;
	for (int i = hashResult; moveSlotSteps < tableSize; i++, i %= tableSize, moveSlotSteps++) {
		description = "Checking key of slot of index " + std::to_string(i);
		if (moveSlotSteps == 0)
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_SLOT, description, {3}, i));
		else
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_SLOT, description, {3,9}, i));

		if (i == oldSlotRemoval.index) {
			description = "Found slot: key " + std::to_string(key) + ", index " + std::to_string(i);
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_FOUND_SLOT, description, {6}, i));
			description = "Remove key from node index " + std::to_string(i) + ", add deletion marker.";
			events.push_back(HashAnimStep(HashAnimType::SET_DELETED_TO_SLOT, description, {7,8}, i));
			break;
		}
	}

	// Insert key step
	description = hashDescriptionString(newKey);
	hashResult = hashFunc(newKey);
	events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_SLOT_AFTER_REMOVE, description, {12,13}, hashResult));

	moveSlotSteps = 0;
	for (int i = hashResult; moveSlotSteps < tableSize; i++, i %= tableSize, moveSlotSteps++) {
		description = "Checking if slot of index " + std::to_string(i) + " is empty";
		if (moveSlotSteps == 0)
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_SLOT_AFTER_REMOVE, description, {15}, i));
		else
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_SLOT_AFTER_REMOVE, description, {15,19}, i));

		if (i == oldSlotInsert.index) {
			description = "Found empty slot: index " + std::to_string(i);
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_FOUND_SLOT_AFTER_REMOVE, description, {16}, i));
			description = "Assigning " + std::to_string(newKey) + " to slot index " + std::to_string(i);
			events.push_back(HashAnimStep(HashAnimType::HIGHLIGHT_UPDATED_SLOT, description, {17,18}, i));
			break;
		}
	}

	return events;
}











// Draw nodes: Iterate through linked list and draw nodes
// --- NORMAL | SEARCH MODE ---
void HashVisEngine::addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, HashAnimStep eventHash) {
	for (int idx = 0; idx < tableSize; idx++) {
		sf::Vector2f slotPos = originPos + sf::Vector2f(idx * slotKeyRectSize.x, 0);
		drawSlot(drawableList, idx, table[idx].key, table[idx].empty, table[idx].deleted, slotPos);
	}

	for (int idx = 0; idx < tableSize; idx++) {
		sf::Vector2f slotPos = originPos + sf::Vector2f(idx * slotKeyRectSize.x, 0);
		if (idx == eventHash.curIndex)
			drawHighlightBorder(drawableList, idx, table[idx].key, slotPos, (eventHash.type == HashAnimType::HIGHLIGHT_FOUND_SLOT));
	}
}


// --- INSERT MODE ---
void HashVisEngine::addNodeDrawablesInsert(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, HashAnimStep eventHash) {
	for (int idx = 0; idx < tableSize; idx++) {
		sf::Vector2f slotPos = originPos + sf::Vector2f(idx * slotKeyRectSize.x, 0);
		if (idx == insertSlotIdx) {
			if (eventHash.type == HashAnimType::SET_KEY_TO_SLOT) {
				drawSlot(drawableList, idx, 
					table[idx].key, 
					table[idx].empty, table[idx].deleted, slotPos);
			} else {
				drawSlot(drawableList, idx, 
					oldKeySlot, 
					true, isOldSlotDeleted, slotPos);
			}
		} else {
			drawSlot(drawableList, idx, table[idx].key, table[idx].empty, table[idx].deleted, slotPos);
		}
	}

	for (int idx = 0; idx < tableSize; idx++) {
		sf::Vector2f slotPos = originPos + sf::Vector2f(idx * slotKeyRectSize.x, 0);
		if (idx == eventHash.curIndex)
			drawHighlightBorder(drawableList, idx, table[idx].key, slotPos, 
				(eventHash.type == HashAnimType::HIGHLIGHT_FOUND_SLOT
					|| eventHash.type == HashAnimType::SET_KEY_TO_SLOT));
	}
}


// --- REMOVE MODE ---
void HashVisEngine::addNodeDrawablesRemove(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, HashAnimStep eventHash) {
	for (int idx = 0; idx < tableSize; idx++) {
		sf::Vector2f slotPos = originPos + sf::Vector2f(idx * slotKeyRectSize.x, 0);
		if (idx == removeSlotIdx) {
			if (eventHash.type == HashAnimType::SET_DELETED_TO_SLOT) {
				drawSlot(drawableList, idx, 
					table[idx].key, 
					table[idx].empty, table[idx].deleted, slotPos);
			} else {
				drawSlot(drawableList, idx, 
					oldKeySlot, 
					false, false, slotPos);
			}
		} else {
			drawSlot(drawableList, idx, table[idx].key, table[idx].empty, table[idx].deleted, slotPos);
		}
	}

	for (int idx = 0; idx < tableSize; idx++) {
		sf::Vector2f slotPos = originPos + sf::Vector2f(idx * slotKeyRectSize.x, 0);
		if (idx == eventHash.curIndex)
			drawHighlightBorder(drawableList, idx, table[idx].key, slotPos, 
				(eventHash.type == HashAnimType::HIGHLIGHT_FOUND_SLOT
					|| eventHash.type == HashAnimType::SET_DELETED_TO_SLOT));
	}
}


// --- UPDATE MODE ---
void HashVisEngine::addNodeDrawablesUpdate(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, HashAnimStep eventHash) {
	for (int idx = 0; idx < tableSize; idx++) {
		sf::Vector2f slotPos = originPos + sf::Vector2f(idx * slotKeyRectSize.x, 0);

		if (oldSlotRemoval.index == oldSlotInsert.index) {
			switch (eventHash.type) {
			case HashAnimType::NONE:
			case HashAnimType::HIGHLIGHT_SLOT:
			case HashAnimType::HIGHLIGHT_FOUND_SLOT:
				if (idx == oldSlotRemoval.index)
					drawSlot(drawableList, oldSlotRemoval, slotPos);
				else
					drawSlot(drawableList, idx,
							table[idx].key, table[idx].empty, table[idx].deleted, slotPos);
				break;
			case HashAnimType::SET_DELETED_TO_SLOT:
			case HashAnimType::HIGHLIGHT_SLOT_AFTER_REMOVE:
			case HashAnimType::HIGHLIGHT_FOUND_SLOT_AFTER_REMOVE:
				if (idx == oldSlotRemoval.index)
					drawSlot(drawableList, oldSlotInsert, slotPos);
				else
					drawSlot(drawableList, idx,
							table[idx].key, table[idx].empty, table[idx].deleted, slotPos);
				break;
			case HashAnimType::HIGHLIGHT_UPDATED_SLOT:
				drawSlot(drawableList, idx,
						table[idx].key, table[idx].empty, table[idx].deleted, slotPos);
				break;
			default:
				break;
			}
		} else {
			switch (eventHash.type) {
			case HashAnimType::NONE:
			case HashAnimType::HIGHLIGHT_SLOT:
			case HashAnimType::HIGHLIGHT_FOUND_SLOT:
				if (idx == oldSlotRemoval.index)
					drawSlot(drawableList, oldSlotRemoval, slotPos);
				else if (idx == oldSlotInsert.index)
					drawSlot(drawableList, oldSlotInsert, slotPos);
				else
					drawSlot(drawableList, idx,
							table[idx].key, table[idx].empty, table[idx].deleted, slotPos);
				break;
			case HashAnimType::SET_DELETED_TO_SLOT:
			case HashAnimType::HIGHLIGHT_SLOT_AFTER_REMOVE:
			case HashAnimType::HIGHLIGHT_FOUND_SLOT_AFTER_REMOVE:
				if (idx == oldSlotInsert.index)
					drawSlot(drawableList, oldSlotInsert, slotPos);
				else
					drawSlot(drawableList, idx,
							table[idx].key, table[idx].empty, table[idx].deleted, slotPos);
				break;
			case HashAnimType::HIGHLIGHT_UPDATED_SLOT:
				drawSlot(drawableList, idx,
						table[idx].key, table[idx].empty, table[idx].deleted, slotPos);
				break;
			default:
				break;
			}
		}
	}
	
	for (int idx = 0; idx < tableSize; idx++) {
		if (idx != eventHash.curIndex) continue;

		sf::Vector2f slotPos = originPos + sf::Vector2f(idx * slotKeyRectSize.x, 0);

		if (oldSlotRemoval.index == oldSlotInsert.index) {
			switch (eventHash.type) {
			case HashAnimType::NONE:
			case HashAnimType::HIGHLIGHT_SLOT:
				drawHighlightBorder(drawableList, idx, oldSlotRemoval.key, slotPos, false);
				break;
			case HashAnimType::HIGHLIGHT_FOUND_SLOT:
				drawHighlightBorder(drawableList, idx, oldSlotRemoval.key, slotPos, true);
				break;
			case HashAnimType::SET_DELETED_TO_SLOT:
				drawHighlightBorder(drawableList, idx, oldSlotInsert.key, slotPos, true);
				break;
			case HashAnimType::HIGHLIGHT_SLOT_AFTER_REMOVE:
				drawHighlightBorder(drawableList, idx, oldSlotInsert.key, slotPos, false);
				break;
			case HashAnimType::HIGHLIGHT_FOUND_SLOT_AFTER_REMOVE:
				drawHighlightBorder(drawableList, idx, oldSlotInsert.key, slotPos, true);
				break;
			case HashAnimType::HIGHLIGHT_UPDATED_SLOT:
				drawHighlightBorder(drawableList, idx, table[idx].key, slotPos, true);
				break;
			default:
				break;
			}
		} else {
			switch (eventHash.type) {
			case HashAnimType::NONE:
			case HashAnimType::HIGHLIGHT_SLOT:
				drawHighlightBorder(drawableList, idx, oldSlotRemoval.key, slotPos, false);
				break;
			case HashAnimType::HIGHLIGHT_FOUND_SLOT:
				drawHighlightBorder(drawableList, idx, oldSlotRemoval.key, slotPos, true);
				break;
			case HashAnimType::SET_DELETED_TO_SLOT:
				drawHighlightBorder(drawableList, idx, oldSlotInsert.key, slotPos, true);
				break;
			case HashAnimType::HIGHLIGHT_SLOT_AFTER_REMOVE:
				drawHighlightBorder(drawableList, idx, oldSlotInsert.key, slotPos, false);
				break;
			case HashAnimType::HIGHLIGHT_FOUND_SLOT_AFTER_REMOVE:
				drawHighlightBorder(drawableList, idx, oldSlotInsert.key, slotPos, true);
				break;
			case HashAnimType::HIGHLIGHT_UPDATED_SLOT:
				drawHighlightBorder(drawableList, idx, table[idx].key, slotPos, true);
				break;
			default:
				break;
			}
		}
	}
}









// --- Create DRAWABLES to draw later ---
void HashVisEngine::createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::vector<std::unique_ptr<sf::Drawable>>& drawableListDefaultView) {
	refreshOriginPos();
	drawableList.clear();
	drawableListDefaultView.clear();


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
	animInProgress = (abs(time - (static_cast<float>(eventList.size()) - 0.0005f)) > EPSILON_TIME);

	if (animStepIndex > oldAnimStepIndex) {
		// if (eventList[oldAnimStepIndex].type == HashAnimType::MOVE_CUR_FORWARD) {
		// 	visCurIndex++;
		// 	visCur = visCur->pNext;
		// }
		oldAnimStepIndex = animStepIndex;
	}



	if (visMode == HashVisMode::INSERT) {
		// INSERT MODE
		addNodeDrawablesInsert(drawableList, eventHash);
		drawPseudocodeWindow(eventHash);
	} else if (visMode == HashVisMode::REMOVE) {
		// REMOVE MODE
		addNodeDrawablesRemove(drawableList, eventHash);
		drawPseudocodeWindow(eventHash);
	} else if (visMode == HashVisMode::UPDATE) {
		// UPDATE MODE
		addNodeDrawablesUpdate(drawableList, eventHash);
		drawPseudocodeWindow(eventHash);
	} else {
		addNodeDrawables(drawableList, eventHash);
		drawPseudocodeWindow(eventHash);
	}



	// Display description for algorithm visualization
	auto descriptionText = std::make_unique<sf::Text>(*fontPtr, eventHash.desc, descriptionFontSize);
	descriptionText->setFillColor(normalSlotColor);
	descriptionText->setPosition(descriptionTextPos);
	descriptionText->setPosition(round(descriptionText->getPosition()));

	drawableListDefaultView.push_back(std::move(descriptionText));


	std::cout << drawableList.size() << ' ' << time << " init done" << std::endl; // DEBUG
}










// Create AND display ImGui window to highlight source code (pseudocode)
void HashVisEngine::drawPseudocodeWindow(HashAnimStep eventHash) {
	ImGui::Begin("Pseudocode", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::PushFont(pseudocodeFont);

	switch (visMode) {
	case HashVisMode::SEARCH:
		for (int i = 0; i < HASH_TABLE_CODE_SEARCH.size(); i++) {
			bool highlightLine = vecContains(eventHash.highlightLineIndex, i);
			if (highlightLine)
				ImGui::PushStyleColor(ImGuiCol_Text, highlightCodeColor);
			ImGui::Text("%s", HASH_TABLE_CODE_SEARCH[i].c_str());
			if (highlightLine)
				ImGui::PopStyleColor();
		}
		break;
	case HashVisMode::UPDATE:
		for (int i = 0; i < HASH_TABLE_CODE_UPDATE.size(); i++) {
			bool highlightLine = vecContains(eventHash.highlightLineIndex, i);
			if (highlightLine)
				ImGui::PushStyleColor(ImGuiCol_Text, highlightCodeColor);
			ImGui::Text("%s", HASH_TABLE_CODE_UPDATE[i].c_str());
			if (highlightLine)
				ImGui::PopStyleColor();
		}
		break;
	case HashVisMode::INSERT:
		for (int i = 0; i < HASH_TABLE_CODE_INSERT.size(); i++) {
			bool highlightLine = vecContains(eventHash.highlightLineIndex, i);
			if (highlightLine)
				ImGui::PushStyleColor(ImGuiCol_Text, highlightCodeColor);
			ImGui::Text("%s", HASH_TABLE_CODE_INSERT[i].c_str());
			if (highlightLine)
				ImGui::PopStyleColor();
		}
		break;
	case HashVisMode::REMOVE:
		for (int i = 0; i < HASH_TABLE_CODE_REMOVE.size(); i++) {
			bool highlightLine = vecContains(eventHash.highlightLineIndex, i);
			if (highlightLine)
				ImGui::PushStyleColor(ImGuiCol_Text, highlightCodeColor);
			ImGui::Text("%s", HASH_TABLE_CODE_REMOVE[i].c_str());
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











int HashVisEngine::hashFunc(int key) {
	return ((key % tableModulo) + tableModulo) % tableModulo;
}


///// Helper methods
std::string HashVisEngine::hashDescriptionString(int key) {
	return "Hashing: h(" + std::to_string(key) + ") = " 
		+ std::to_string(key) + " mod " + std::to_string(tableModulo) 
		+ " = " + std::to_string(hashFunc(key));
}

bool HashVisEngine::containsKey(int key) {
	int hashResult = hashFunc(key);
	int moveSlotSteps = 0;
	for (int i = hashResult; moveSlotSteps < tableSize; i++, i %= tableSize, moveSlotSteps++) {
		if (table[i].empty && !table[i].deleted)
			break;
		if (table[i].hasKey(key))
			return true;
	}
	return false;
}

bool HashVisEngine::isFull() {
	for (const TableSlot& slot : table) {
		if (slot.empty)
			return false;
	}
	return true;
}

bool HashVisEngine::isUpdatable(int oldKey, int newKey) {
	return containsKey(oldKey);
}




void HashVisEngine::refreshOriginPos() {
	originPos = originPosDisplacement - sf::Vector2f(normalWindowSize) / 2.f;
}



///// Methods for drawing SFML
void HashVisEngine::drawSlot(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, 
	int slotIndex, int key, bool empty, bool deleted, sf::Vector2f topLeftPos) const {
	/*
	// Draw Rect for VALUE of slot
	auto valRect = std::make_unique<sf::RectangleShape>(slotValRectSize);
	valRect->setFillColor(sf::Color::Transparent);
	valRect->setOutlineColor(normalSlotColor);
	valRect->setOutlineThickness(1);
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
	keyRect->setOutlineThickness(1);
	keyRect->setPosition(topLeftPos);

	// Draw Text for KEY of slot
	auto keyText = std::make_unique<sf::Text>(*fontPtr, 
		deleted ? "<deleted>" : (empty ? "" : std::to_string(key)), 
		keyFontSize);
	if (deleted) { // Prevent "<deleted>" text from overflowing
		sf::FloatRect localBounds = keyText->getLocalBounds();
		float scale = slotKeyRectSize.x / localBounds.size.x;
		keyText->setCharacterSize(round(scale * keyFontSize));
	}
	sf::FloatRect localBounds = keyText->getLocalBounds();
	keyText->setOrigin({localBounds.position.x + localBounds.size.x / 2.f, localBounds.position.y + localBounds.size.y / 2.f});
	keyText->setFillColor(normalSlotKeyColor);
	keyText->setPosition(keyRect->getPosition() + slotKeyRectSize / 2.f);
	keyText->setPosition(round(keyText->getPosition()));

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

void HashVisEngine::drawSlot(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, TableSlot& slot, sf::Vector2f topLeftPos) const {
	drawSlot(drawableList, slot.index, slot.key, slot.empty, slot.deleted, topLeftPos);
}



void HashVisEngine::drawHighlightBorder(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, int slotIndex, int key, sf::Vector2f topLeftPos, bool isFoundSlot) const {
	auto highlightBorder = std::make_unique<sf::RectangleShape>(slotKeyRectSize);
	highlightBorder->setFillColor(sf::Color::Transparent);
	highlightBorder->setOutlineColor(isFoundSlot ? highlightFoundSlotColor : highlightSlotColor);
	highlightBorder->setOutlineThickness(5.f);
	highlightBorder->setPosition(topLeftPos);
	drawableList.push_back(std::move(highlightBorder));
}





// Set vis themes
void HashVisEngine::setVisTheme(VIS_THEME visTheme) {
	switch (visTheme) {
	case VIS_THEME::LIGHT:
		setLightVisTheme();
		break;
	case VIS_THEME::DARK:
		setDarkVisTheme();
		break;
	}
}

void HashVisEngine::setLightVisTheme() {
	normalSlotColor         = lightNormalSlotColor;
	normalSlotValueColor    = lightNormalSlotValueColor;
	normalSlotKeyColor      = lightNormalSlotKeyColor;
	normalSlotIndexColor    = lightNormalSlotIndexColor;
	highlightSlotColor      = lightHighlightSlotColor;
	highlightFoundSlotColor = lightHighlightFoundSlotColor;
}

void HashVisEngine::setDarkVisTheme() {
	normalSlotColor         = darkNormalSlotColor;
	normalSlotValueColor    = darkNormalSlotValueColor;
	normalSlotKeyColor      = darkNormalSlotKeyColor;
	normalSlotIndexColor    = darkNormalSlotIndexColor;
	highlightSlotColor      = darkHighlightSlotColor;
	highlightFoundSlotColor = darkHighlightFoundSlotColor;
}
