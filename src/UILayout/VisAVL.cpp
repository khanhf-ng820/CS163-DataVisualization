#include "UILayout/VisAVL.h"





// REMEMBER:
// Drawing SFML: The center of the window is now (0, 0) coordinates
// Drawing GUI: The top-left of the window is (0, 0) coordinates
// Clear SFML drawables
void Program::initVisAVLScreen() {
	// Push back to vector
	sfDrawables[ProgramState::VIS_AVL_SCREEN]->drawables.clear();
	sfDrawablesDefaultView[ProgramState::VIS_AVL_SCREEN]->drawables.clear();
	// printf("VisAVL SFML init function called\n"); // DEBUG
}



// Display vis AVL Tree screen, set up SFML drawables
void Program::displayVisAVLScreenSFML() {
	switch (visEngine_AVL.visMode) {
	// ----- NO MODE (STILL MODE) -----
	case AVLVisMode::NONE:
		visEngine_AVL.eventList = std::vector<AVLAnimStep>();
		visEngine_AVL.createDrawables(
			sfDrawables[ProgramState::VIS_AVL_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_AVL_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_AVL_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_AVL_SCREEN]->displayAll();

		if (!visEngine_AVL.animPaused)
			visEngine_AVL.increaseTime();
		break;
	// ----- SEARCH MODE -----
	case AVLVisMode::SEARCH:
		// visEngine_AVL.eventList = visEngine_AVL.getEventsSearch(visEngine_AVL.keyToSearch);
		visEngine_AVL.createDrawables(
			sfDrawables[ProgramState::VIS_AVL_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_AVL_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_AVL_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_AVL_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_AVL.animPaused) {
			if (visEngine_AVL.time < visEngine_AVL.targetTime) {
				visEngine_AVL.increaseTime();
				visEngine_AVL.time = std::min(visEngine_AVL.time, visEngine_AVL.targetTime);
			} else if (visEngine_AVL.time > visEngine_AVL.targetTime) {
				visEngine_AVL.decreaseTime();
				visEngine_AVL.time = std::max(visEngine_AVL.time, visEngine_AVL.targetTime);
			}
		} else {
			visEngine_AVL.increaseTime();
		}
		break;
	// ----- INSERT MODE -----
	case AVLVisMode::INSERT:
		// visEngine_AVL.eventList = visEngine_AVL.getEventsInsert(visEngine_AVL.keyToInsert);
		visEngine_AVL.createDrawables(
			sfDrawables[ProgramState::VIS_AVL_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_AVL_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_AVL_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_AVL_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_AVL.animPaused) {
			if (visEngine_AVL.time < visEngine_AVL.targetTime) {
				visEngine_AVL.increaseTime();
				visEngine_AVL.time = std::min(visEngine_AVL.time, visEngine_AVL.targetTime);
			} else if (visEngine_AVL.time > visEngine_AVL.targetTime) {
				visEngine_AVL.decreaseTime();
				visEngine_AVL.time = std::max(visEngine_AVL.time, visEngine_AVL.targetTime);
			}
		} else {
			visEngine_AVL.increaseTime();
		}
		break;
	// ----- REMOVE MODE -----
	case AVLVisMode::REMOVE:
		// visEngine_AVL.eventList = visEngine_AVL.getEventsRemove(visEngine_AVL.keyToRemove);
		visEngine_AVL.createDrawables(
			sfDrawables[ProgramState::VIS_AVL_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_AVL_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_AVL_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_AVL_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_AVL.animPaused) {
			if (visEngine_AVL.time < visEngine_AVL.targetTime) {
				visEngine_AVL.increaseTime();
				visEngine_AVL.time = std::min(visEngine_AVL.time, visEngine_AVL.targetTime);
			} else if (visEngine_AVL.time > visEngine_AVL.targetTime) {
				visEngine_AVL.decreaseTime();
				visEngine_AVL.time = std::max(visEngine_AVL.time, visEngine_AVL.targetTime);
			}
		} else {
			visEngine_AVL.increaseTime();
		}
		break;
	// ----- UPDATE MODE -----
	case AVLVisMode::UPDATE:
		// visEngine_AVL.eventList = visEngine_AVL.getEventsUpdate(visEngine_AVL.oldKeyToUpdate, visEngine_AVL.newKeyToUpdate);
		visEngine_AVL.createDrawables(
			sfDrawables[ProgramState::VIS_AVL_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_AVL_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_AVL_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_AVL_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_AVL.animPaused) {
			if (visEngine_AVL.time < visEngine_AVL.targetTime) {
				visEngine_AVL.increaseTime();
				visEngine_AVL.time = std::min(visEngine_AVL.time, visEngine_AVL.targetTime);
			} else if (visEngine_AVL.time > visEngine_AVL.targetTime) {
				visEngine_AVL.decreaseTime();
				visEngine_AVL.time = std::max(visEngine_AVL.time, visEngine_AVL.targetTime);
			}
		} else {
			visEngine_AVL.increaseTime();
		}
		break;
	default:
		break;
	}


	// std::cout << sfDrawables[ProgramState::VIS_AVL_SCREEN]->drawables.size() << std::endl;
	// printf("VisAVLTable SFML function called\n"); // DEBUG
}



void Program::displayVisAVLScreenGUI() {
	allowDragCanvas = true;

	// Show the demo window
	// ImGui::ShowDemoWindow();

	// Get the current window size
	sf::Vector2u sfml_window_size = window.getSize();

	ImGui::Begin("AVL Tree Menu",
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
	ImGui::SliderFloat("Animation Speed", &visEngine_AVL.dt, 0.001f, 0.499f);

	// ImGui::BeginDisabled(!visEngine_AVL.animPaused);
	if (ImGui::Button("Skip to Start")) {
		visEngine_AVL.skipToStartState();
	}
	// ImGui::EndDisabled();
	ImGui::SameLine();
	ImGui::BeginDisabled(!visEngine_AVL.animPaused);
	if (ImGui::Button("Previous Step")) {
		visEngine_AVL.prevStep();
	}
	ImGui::EndDisabled();
	ImGui::SameLine();
	if (ImGui::Button(visEngine_AVL.animPaused ? "Play" : "Pause")) {
		visEngine_AVL.animPaused = !visEngine_AVL.animPaused;
		visEngine_AVL.targetTime = visEngine_AVL.time;
	}
	ImGui::SameLine();
	ImGui::BeginDisabled(!visEngine_AVL.animPaused);
	if (ImGui::Button("Next Step")) {
		visEngine_AVL.nextStep();
	}
	ImGui::EndDisabled();
	ImGui::SameLine();
	// ImGui::BeginDisabled(!visEngine_AVL.animPaused);
	if (ImGui::Button("Skip to Final")) {
		visEngine_AVL.skipToFinalState();
	}
	// ImGui::EndDisabled();

	ImGui::Separator();



	// -- SEARCH OPERATION --
	ImGui::BeginDisabled(visEngine_AVL.animInProgress);
	ImGui::Text("Enter key to search:");
	ImGui::InputInt("Key to search", &visEngine_AVL.keyToSearchInput);
	// float f;
	// ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

	if (ImGui::Button("Search")) {
		visEngine_AVL.keyToSearch = visEngine_AVL.keyToSearchInput;
		visEngine_AVL.visMode = AVLVisMode::SEARCH;

		visEngine_AVL.resetParams();
		visEngine_AVL.animPaused = false; // Auto un-pause

		// Generate events
		visEngine_AVL.eventList = visEngine_AVL.getEventsSearch(visEngine_AVL.keyToSearch);
		std::cout << "search AVL tree cool, " << visEngine_AVL.eventList.size() << " events" << std::endl; // DEBUG
	}
	ImGui::EndDisabled();

	ImGui::Separator();


	// -- INSERT OPERATION --
	ImGui::BeginDisabled(visEngine_AVL.animInProgress);
	ImGui::Text("Enter key to insert:");
	ImGui::InputInt("Key to insert", &visEngine_AVL.keyToInsertInput);

	if (ImGui::Button("Insert")) {
		visEngine_AVL.keyToInsert = visEngine_AVL.keyToInsertInput;
		visEngine_AVL.visMode = AVLVisMode::INSERT;

		visEngine_AVL.resetParams();
		visEngine_AVL.animPaused = false; // Auto un-pause

		// visEngine_AVL.insert(visEngine_AVL.keyToInsert);
		// Generate events
		visEngine_AVL.eventList = visEngine_AVL.getEventsInsert(visEngine_AVL.keyToInsert);
		std::cout << "insert AVL tree cool" << std::endl; // DEBUG
	}
	ImGui::EndDisabled();

	ImGui::Separator();


	// -- REMOVE OPERATION --
	ImGui::BeginDisabled(visEngine_AVL.animInProgress);
	ImGui::Text("Enter key to remove:");
	ImGui::InputInt("Key to remove", &visEngine_AVL.keyToRemoveInput);

	if (ImGui::Button("Remove")) {
		visEngine_AVL.keyToRemove = visEngine_AVL.keyToRemoveInput;
		visEngine_AVL.visMode = AVLVisMode::REMOVE;

		visEngine_AVL.resetParams();
		visEngine_AVL.animPaused = false; // Auto un-pause

		// Generate events
		visEngine_AVL.eventList = visEngine_AVL.getEventsDelete(visEngine_AVL.keyToRemove);
		std::cout << "remove AVL tree cool" << std::endl; // DEBUG
	}
	ImGui::EndDisabled();

	ImGui::Separator();


	// -- UPDATE OPERATION --
	ImGui::BeginDisabled(visEngine_AVL.animInProgress);
	ImGui::Text("Enter keys to update:");
	ImGui::InputInt("Old key", &visEngine_AVL.oldKeyToUpdateInput);
	ImGui::InputInt("New key", &visEngine_AVL.newKeyToUpdateInput);

	bool updatable = (visEngine_AVL.tree.getNodeKey(visEngine_AVL.oldKeyToUpdateInput) != nullptr);
	ImGui::BeginDisabled(!updatable);
	if (ImGui::Button("Update")) {
		visEngine_AVL.keyToRemove = visEngine_AVL.oldKeyToUpdateInput;
		visEngine_AVL.keyToInsert = visEngine_AVL.newKeyToUpdateInput;
		visEngine_AVL.visMode = AVLVisMode::UPDATE;

		visEngine_AVL.resetParams();
		visEngine_AVL.animPaused = false; // Auto un-pause

		// Generate events
		// visEngine_AVL.update(visEngine_AVL.keyToRemove, visEngine_AVL.keyToInsert);
		visEngine_AVL.eventList = visEngine_AVL.getEventsUpdate(visEngine_AVL.keyToRemove, visEngine_AVL.keyToInsert);
		std::cout << "update AVL tree cool" << std::endl; // DEBUG
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



void Program::finishVisAVLScreen() {

}
