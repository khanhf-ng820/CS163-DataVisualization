#include "UILayout/VisDijkstra.h"





// REMEMBER:
// Drawing SFML: The center of the window is now (0, 0) coordinates
// Drawing GUI: The top-left of the window is (0, 0) coordinates
// Clear SFML drawables
void Program::initVisDijkstraScreen() {
	// Push back to vector
	sfDrawables[ProgramState::VIS_DIJKSTRA_SCREEN]->drawables.clear();
	sfDrawablesDefaultView[ProgramState::VIS_DIJKSTRA_SCREEN]->drawables.clear();
	// printf("VisDijkstra SFML init function called\n"); // DEBUG
}



// Display vis Dijkstra Tree screen, set up SFML drawables
void Program::displayVisDijkstraScreenSFML() {
	switch (visEngine_Dijkstra.visMode) {
	// ----- NO MODE (STILL MODE) -----
	case DijkstraVisMode::NONE:
		visEngine_Dijkstra.eventList = std::vector<DijkstraAnimStep>();
		visEngine_Dijkstra.createDrawables(
			sfDrawables[ProgramState::VIS_DIJKSTRA_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_DIJKSTRA_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_DIJKSTRA_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_DIJKSTRA_SCREEN]->displayAll();

		if (!visEngine_Dijkstra.animPaused)
			visEngine_Dijkstra.increaseTime();
		break;
	// ----- DIJKSTRA MODE -----
	case DijkstraVisMode::DIJKSTRA:
		// visEngine_Dijkstra.eventList = visEngine_Dijkstra.getEventsSearch(visEngine_Dijkstra.startVertexID);
		visEngine_Dijkstra.createDrawables(
			sfDrawables[ProgramState::VIS_DIJKSTRA_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_DIJKSTRA_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_DIJKSTRA_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_DIJKSTRA_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_Dijkstra.animPaused) {
			if (visEngine_Dijkstra.time < visEngine_Dijkstra.targetTime) {
				visEngine_Dijkstra.increaseTime();
				visEngine_Dijkstra.time = std::min(visEngine_Dijkstra.time, visEngine_Dijkstra.targetTime);
			} else if (visEngine_Dijkstra.time > visEngine_Dijkstra.targetTime) {
				visEngine_Dijkstra.decreaseTime();
				visEngine_Dijkstra.time = std::max(visEngine_Dijkstra.time, visEngine_Dijkstra.targetTime);
			}
		} else {
			visEngine_Dijkstra.increaseTime();
		}
		break;
	default:
		break;
	}


	// std::cout << sfDrawables[ProgramState::VIS_DIJKSTRA_SCREEN]->drawables.size() << std::endl;
	// printf("VisDijkstraTable SFML function called\n"); // DEBUG
}



void Program::displayVisDijkstraScreenGUI() {
	allowDragCanvas = true;

	// Show the demo window
	// ImGui::ShowDemoWindow();

	// Get the current window size
	sf::Vector2u sfml_window_size = window.getSize();

	ImGui::Begin("Dijkstra Menu",
		nullptr
		// ImGuiWindowFlags_NoCollapse
		// ImGuiWindowFlags_NoBackground
	);
	// -- GO BACK TO MAIN MENU BUTTON
	if (ImGui::Button("<- Back to Main Menu")) {
		programState = ProgramState::MAIN_MENU;
		resizeView();
	}
	ImGui::SameLine();
	// - RESET VIEW BUTTON
	if (ImGui::Button("Reset View")) {
		resizeView();
	}
	// -- SPEED/PAUSE/STEP MENU
	ImGui::SliderFloat("Animation Speed", &visEngine_Dijkstra.dt, 0.001f, 0.499f);

	ImGui::BeginDisabled(!visEngine_Dijkstra.animPaused);
	if (ImGui::Button("Previous Step")) {
		visEngine_Dijkstra.prevStep();
	}
	ImGui::EndDisabled();
	ImGui::SameLine();
	if (ImGui::Button(visEngine_Dijkstra.animPaused ? "Play" : "Pause")) {
		visEngine_Dijkstra.animPaused = !visEngine_Dijkstra.animPaused;
		visEngine_Dijkstra.targetTime = visEngine_Dijkstra.time;
	}
	ImGui::SameLine();
	ImGui::BeginDisabled(!visEngine_Dijkstra.animPaused);
	if (ImGui::Button("Next Step")) {
		visEngine_Dijkstra.nextStep();
	}
	ImGui::EndDisabled();
	ImGui::SameLine();
	ImGui::BeginDisabled(!visEngine_Dijkstra.animPaused);
	if (ImGui::Button("Skip to Final")) {
		visEngine_Dijkstra.skipToFinalState();
	}
	ImGui::EndDisabled();

	ImGui::Separator();



	// -- RUN DIJKSTRA OPERATION --
	ImGui::BeginDisabled(visEngine_Dijkstra.animInProgress);
	ImGui::Text("Enter starting vertex:");
	if (ImGui::InputInt("Start vertex", &visEngine_Dijkstra.startVertexIDInput)) {
		visEngine_Dijkstra.startVertexIDInput = std::clamp(visEngine_Dijkstra.startVertexIDInput, 
			0, 
			static_cast<int>(visEngine_Dijkstra.graph.getNumVertex()) - 1);
	}
	// float f;
	// ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

	if (ImGui::Button("Run Dijkstra\'s algorithm")) {
		visEngine_Dijkstra.startVertexID = visEngine_Dijkstra.startVertexIDInput;
		visEngine_Dijkstra.visMode = DijkstraVisMode::DIJKSTRA;

		visEngine_Dijkstra.resetParams();
		visEngine_Dijkstra.animPaused = false; // Auto un-pause

		// Generate events
		visEngine_Dijkstra.eventList = visEngine_Dijkstra.getEventsDijkstra(visEngine_Dijkstra.startVertexID);
		std::cout << "run Dijkstra cool, " << visEngine_Dijkstra.eventList.size() << " events" << std::endl; // DEBUG
	}
	ImGui::EndDisabled();

	ImGui::Separator();


	// // -- INSERT OPERATION --
	// ImGui::BeginDisabled(visEngine_Dijkstra.animInProgress);
	// ImGui::Text("Enter key to insert:");
	// ImGui::InputInt("Key to insert", &visEngine_Dijkstra.keyToInsertInput);

	// if (ImGui::Button("Insert")) {
	// 	visEngine_Dijkstra.keyToInsert = visEngine_Dijkstra.keyToInsertInput;
	// 	visEngine_Dijkstra.visMode = DijkstraVisMode::INSERT;

	// 	visEngine_Dijkstra.resetParams();
	// 	visEngine_Dijkstra.animPaused = false; // Auto un-pause

	// 	// visEngine_Dijkstra.insert(visEngine_Dijkstra.keyToInsert);
	// 	// Generate events
	// 	visEngine_Dijkstra.eventList = visEngine_Dijkstra.getEventsInsert(visEngine_Dijkstra.keyToInsert);
	// 	std::cout << "insert Dijkstra tree cool" << std::endl; // DEBUG
	// }
	// ImGui::EndDisabled();

	// ImGui::Separator();


	// // -- REMOVE OPERATION --
	// ImGui::BeginDisabled(visEngine_Dijkstra.animInProgress);
	// ImGui::Text("Enter key of slot to remove:");
	// ImGui::InputInt("Key to remove", &visEngine_Dijkstra.keyToRemoveInput);

	// if (ImGui::Button("Remove")) {
	// 	visEngine_Dijkstra.keyToRemove = visEngine_Dijkstra.keyToRemoveInput;
	// 	visEngine_Dijkstra.visMode = DijkstraVisMode::REMOVE;

	// 	visEngine_Dijkstra.resetParams();
	// 	visEngine_Dijkstra.animPaused = false; // Auto un-pause

	// 	// Generate events
	// 	visEngine_Dijkstra.eventList = visEngine_Dijkstra.getEventsDelete(visEngine_Dijkstra.keyToRemove);
	// 	std::cout << "remove Dijkstra tree cool" << std::endl; // DEBUG
	// }
	// ImGui::EndDisabled();

	// ImGui::Separator();


	// // -- UPDATE OPERATION --
	// ImGui::BeginDisabled(visEngine_Dijkstra.animInProgress);
	// ImGui::Text("Enter keys to update:");
	// ImGui::InputInt("Old key", &visEngine_Dijkstra.oldKeyToUpdateInput);
	// ImGui::InputInt("New key", &visEngine_Dijkstra.newKeyToUpdateInput);

	// bool updatable = (visEngine_Dijkstra.tree.getNodeKey(visEngine_Dijkstra.oldKeyToUpdateInput) != nullptr);
	// ImGui::BeginDisabled(!updatable);
	// if (ImGui::Button("Update")) {
	// 	visEngine_Dijkstra.keyToRemove = visEngine_Dijkstra.oldKeyToUpdateInput;
	// 	visEngine_Dijkstra.keyToInsert = visEngine_Dijkstra.newKeyToUpdateInput;
	// 	visEngine_Dijkstra.visMode = DijkstraVisMode::UPDATE;

	// 	visEngine_Dijkstra.resetParams();
	// 	visEngine_Dijkstra.animPaused = false; // Auto un-pause

	// 	// Generate events
	// 	// visEngine_Dijkstra.update(visEngine_Dijkstra.keyToRemove, visEngine_Dijkstra.keyToInsert);
	// 	visEngine_Dijkstra.eventList = visEngine_Dijkstra.getEventsUpdate(visEngine_Dijkstra.keyToRemove, visEngine_Dijkstra.keyToInsert);
	// 	std::cout << "update Dijkstra tree cool" << std::endl; // DEBUG
	// }
	// ImGui::EndDisabled();
	// ImGui::EndDisabled();



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



void Program::finishVisDijkstraScreen() {

}
