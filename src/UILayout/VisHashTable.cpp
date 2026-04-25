#include "UILayout/VisHashTable.h"





// REMEMBER:
// Drawing SFML: The center of the window is now (0, 0) coordinates
// Drawing GUI: The top-left of the window is (0, 0) coordinates
// Clear SFML drawables
void Program::initVisHashScreen() {
	// Push back to vector
	sfDrawables[ProgramState::VIS_HASH_SCREEN]->drawables.clear();
	sfDrawablesDefaultView[ProgramState::VIS_HASH_SCREEN]->drawables.clear();
	// printf("VisHash SFML init function called\n"); // DEBUG
}



// Display vis Hash Table screen, set up SFML drawables
void Program::displayVisHashScreenSFML() {
	switch (visEngine_Hash.visMode) {
	// ----- NO MODE (STILL MODE) -----
	case HashVisMode::NONE:
		visEngine_Hash.eventList = std::vector<HashAnimStep>();
		visEngine_Hash.createDrawables(
			sfDrawables[ProgramState::VIS_HASH_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_HASH_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_HASH_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_HASH_SCREEN]->displayAll();

		if (!visEngine_Hash.animPaused)
			visEngine_Hash.increaseTime();
		break;
	// ----- SEARCH MODE -----
	case HashVisMode::SEARCH:
		visEngine_Hash.eventList = visEngine_Hash.getEventsSearch(visEngine_Hash.keyToSearch);
		visEngine_Hash.createDrawables(
			sfDrawables[ProgramState::VIS_HASH_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_HASH_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_HASH_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_HASH_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_Hash.animPaused) {
			if (visEngine_Hash.time < visEngine_Hash.targetTime) {
				visEngine_Hash.increaseTime();
				visEngine_Hash.time = std::min(visEngine_Hash.time, visEngine_Hash.targetTime);
			} else if (visEngine_Hash.time > visEngine_Hash.targetTime) {
				visEngine_Hash.decreaseTime();
				visEngine_Hash.time = std::max(visEngine_Hash.time, visEngine_Hash.targetTime);
			}
		} else {
			visEngine_Hash.increaseTime();
		}
		break;
	// ----- INSERT MODE -----
	case HashVisMode::INSERT:
		visEngine_Hash.eventList = visEngine_Hash.getEventsInsert(visEngine_Hash.keyToInsert);
		visEngine_Hash.createDrawables(
			sfDrawables[ProgramState::VIS_HASH_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_HASH_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_HASH_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_HASH_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_Hash.animPaused) {
			if (visEngine_Hash.time < visEngine_Hash.targetTime) {
				visEngine_Hash.increaseTime();
				visEngine_Hash.time = std::min(visEngine_Hash.time, visEngine_Hash.targetTime);
			} else if (visEngine_Hash.time > visEngine_Hash.targetTime) {
				visEngine_Hash.decreaseTime();
				visEngine_Hash.time = std::max(visEngine_Hash.time, visEngine_Hash.targetTime);
			}
		} else {
			visEngine_Hash.increaseTime();
		}
		break;
	// ----- REMOVE MODE -----
	case HashVisMode::REMOVE:
		visEngine_Hash.eventList = visEngine_Hash.getEventsRemove(visEngine_Hash.keyToRemove);
		visEngine_Hash.createDrawables(
			sfDrawables[ProgramState::VIS_HASH_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_HASH_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_HASH_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_HASH_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_Hash.animPaused) {
			if (visEngine_Hash.time < visEngine_Hash.targetTime) {
				visEngine_Hash.increaseTime();
				visEngine_Hash.time = std::min(visEngine_Hash.time, visEngine_Hash.targetTime);
			} else if (visEngine_Hash.time > visEngine_Hash.targetTime) {
				visEngine_Hash.decreaseTime();
				visEngine_Hash.time = std::max(visEngine_Hash.time, visEngine_Hash.targetTime);
			}
		} else {
			visEngine_Hash.increaseTime();
		}
		break;
	// ----- UPDATE MODE -----
	case HashVisMode::UPDATE:
		visEngine_Hash.eventList = visEngine_Hash.getEventsUpdate(visEngine_Hash.oldKeyToUpdate, visEngine_Hash.newKeyToUpdate);
		visEngine_Hash.createDrawables(
			sfDrawables[ProgramState::VIS_HASH_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_HASH_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_HASH_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_HASH_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_Hash.animPaused) {
			if (visEngine_Hash.time < visEngine_Hash.targetTime) {
				visEngine_Hash.increaseTime();
				visEngine_Hash.time = std::min(visEngine_Hash.time, visEngine_Hash.targetTime);
			} else if (visEngine_Hash.time > visEngine_Hash.targetTime) {
				visEngine_Hash.decreaseTime();
				visEngine_Hash.time = std::max(visEngine_Hash.time, visEngine_Hash.targetTime);
			}
		} else {
			visEngine_Hash.increaseTime();
		}
		break;
	default:
		break;
	}


	// std::cout << sfDrawables[ProgramState::VIS_HASH_SCREEN]->drawables.size() << std::endl;
	// printf("VisHashTable SFML function called\n"); // DEBUG
}



void Program::displayVisHashScreenGUI() {
	allowDragCanvas = true;

	// Show the demo window
	// ImGui::ShowDemoWindow();

	// Get the current window size
	sf::Vector2u sfml_window_size = window.getSize();

	ImGui::Begin("Hash Table Menu",
		nullptr
		// ImGuiWindowFlags_NoCollapse
		// ImGuiWindowFlags_NoBackground
	);
	// -- GO BACK TO MAIN MENU BUTTON
	if (ImGui::Button("<= Back to Main Menu")) {
		programState = ProgramState::MAIN_MENU;
		resizeView();
	}
	ImGui::SameLine();
	// - RESET VIEW BUTTON
	if (ImGui::Button("Reset View")) {
		resizeView();
	}

	// -- SPEED/PAUSE/STEP MENU
	ImGui::SliderFloat("Animation Speed", &visEngine_Hash.dt, 0.001f, 0.499f);

	// ImGui::BeginDisabled(!visEngine_Hash.animPaused);
	if (ImGui::Button("Skip to Start")) {
		visEngine_Hash.skipToStartState();
	}
	// ImGui::EndDisabled();
	ImGui::SameLine();
	ImGui::BeginDisabled(!visEngine_Hash.animPaused);
	if (ImGui::Button("Previous Step")) {
		visEngine_Hash.prevStep();
	}
	ImGui::EndDisabled();
	ImGui::SameLine();
	if (ImGui::Button(visEngine_Hash.animPaused ? "Play" : "Pause")) {
		visEngine_Hash.animPaused = !visEngine_Hash.animPaused;
		visEngine_Hash.targetTime = visEngine_Hash.time;
	}
	ImGui::SameLine();
	ImGui::BeginDisabled(!visEngine_Hash.animPaused);
	if (ImGui::Button("Next Step")) {
		visEngine_Hash.nextStep();
	}
	ImGui::EndDisabled();
	ImGui::SameLine();
	// ImGui::BeginDisabled(!visEngine_Hash.animPaused);
	if (ImGui::Button("Skip to Final")) {
		visEngine_Hash.skipToFinalState();
	}
	// ImGui::EndDisabled();

	ImGui::Separator();


	// -- SEARCH OPERATION --
	ImGui::BeginDisabled(visEngine_Hash.animInProgress);
	ImGui::Text("Enter key of slot to search:");
	ImGui::InputInt("Key to search", &visEngine_Hash.keyToSearchInput);
	// float f;
	// ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

	if (ImGui::Button("Search")) {
		visEngine_Hash.keyToSearch = visEngine_Hash.keyToSearchInput;
		visEngine_Hash.visMode = HashVisMode::SEARCH;
		visEngine_Hash.resetParams();
		visEngine_Hash.animPaused = false; // Auto un-pause
	}
	ImGui::EndDisabled();

	ImGui::Separator();


	// -- INSERT OPERATION --
	ImGui::BeginDisabled(visEngine_Hash.animInProgress);
	ImGui::Text("Enter key to insert:");
	ImGui::InputInt("Key to insert", &visEngine_Hash.keyToInsertInput);

	if (ImGui::Button("Insert")) {
		visEngine_Hash.keyToInsert = visEngine_Hash.keyToInsertInput;
		visEngine_Hash.visMode = HashVisMode::INSERT;

		visEngine_Hash.resetParams();
		visEngine_Hash.animPaused = false; // Auto un-pause

		visEngine_Hash.insert(visEngine_Hash.keyToInsert);
		std::cout << "insert hash table cool" << std::endl; // DEBUG
	}
	ImGui::EndDisabled();

	ImGui::Separator();


	// -- REMOVE OPERATION --
	ImGui::BeginDisabled(visEngine_Hash.animInProgress);
	ImGui::Text("Enter key of slot to remove:");
	ImGui::InputInt("Key to remove", &visEngine_Hash.keyToRemoveInput);

	if (ImGui::Button("Remove")) {
		visEngine_Hash.keyToRemove = visEngine_Hash.keyToRemoveInput;
		visEngine_Hash.visMode = HashVisMode::REMOVE;

		visEngine_Hash.resetParams();
		visEngine_Hash.animPaused = false; // Auto un-pause

		visEngine_Hash.remove(visEngine_Hash.keyToRemove);
		std::cout << "remove hash table cool" << std::endl; // DEBUG
	}
	ImGui::EndDisabled();

	ImGui::Separator();


	// -- UPDATE OPERATION --
	ImGui::BeginDisabled(visEngine_Hash.animInProgress);
	ImGui::Text("Enter keys to update:");
	ImGui::InputInt("Old key", &visEngine_Hash.oldKeyToUpdateInput);
	ImGui::InputInt("New key", &visEngine_Hash.newKeyToUpdateInput);

	bool updatable = visEngine_Hash.isUpdatable(visEngine_Hash.oldKeyToUpdateInput, 
												visEngine_Hash.newKeyToUpdateInput);
	ImGui::BeginDisabled(!updatable);
	if (ImGui::Button("Update")) {
		visEngine_Hash.oldKeyToUpdate = visEngine_Hash.oldKeyToUpdateInput;
		visEngine_Hash.newKeyToUpdate = visEngine_Hash.newKeyToUpdateInput;
		visEngine_Hash.visMode = HashVisMode::UPDATE;

		visEngine_Hash.resetParams();
		visEngine_Hash.animPaused = false; // Auto un-pause

		visEngine_Hash.update(visEngine_Hash.oldKeyToUpdate, visEngine_Hash.newKeyToUpdate);
		std::cout << "update hash table cool" << std::endl; // DEBUG
	}
	ImGui::EndDisabled();
	ImGui::EndDisabled();



	// const char* items[] = { "Option 1", "Option 2", "Option 3", "Option 4" };
	// static int current_item = 0;
	// if (ImGui::BeginCombo("##mycombo", items[current_item])) { // Pass the "current" item name as the preview
	// 	for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
	// 		bool is_selected = (current_item == n);
	// 		if (ImGui::Selectable(items[n], is_selected)) {
	// 			current_item = n;
	// 		}

	// 		// Set the initial focus when opening the combo (scrolling + keyboard navigation)
	// 		if (is_selected) {
	// 			ImGui::SetItemDefaultFocus();
	// 		}
	// 	}
	// 	ImGui::EndCombo();
	// }
	ImGui::End();
}



void Program::finishVisHashScreen() {

}
