#include "UILayout/VisMSTPrim.h"





// REMEMBER:
// Drawing SFML: The center of the window is now (0, 0) coordinates
// Drawing GUI: The top-left of the window is (0, 0) coordinates
// Clear SFML drawables
void Program::initVisMSTPrimScreen() {
	// Push back to vector
	sfDrawables[ProgramState::VIS_MST_PRIM_SCREEN]->drawables.clear();
	sfDrawablesDefaultView[ProgramState::VIS_MST_PRIM_SCREEN]->drawables.clear();
	// printf("VisMSTPrim SFML init function called\n"); // DEBUG
}



// Display vis MSTPrim Tree screen, set up SFML drawables
void Program::displayVisMSTPrimScreenSFML() {
	switch (visEngine_MSTPrim.visMode) {
	// ----- NO MODE (STILL MODE) -----
	case PrimVisMode::NONE:
		visEngine_MSTPrim.eventList = std::vector<PrimAnimStep>();
		visEngine_MSTPrim.createDrawables(
			sfDrawables[ProgramState::VIS_MST_PRIM_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_MST_PRIM_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_MST_PRIM_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_MST_PRIM_SCREEN]->displayAll();

		if (!visEngine_MSTPrim.animPaused)
			visEngine_MSTPrim.increaseTime();
		break;
	// ----- MST_PRIM MODE -----
	case PrimVisMode::MST_PRIM:
		// visEngine_MSTPrim.eventList = visEngine_MSTPrim.getEventsSearch(visEngine_MSTPrim.startVertexID);
		visEngine_MSTPrim.createDrawables(
			sfDrawables[ProgramState::VIS_MST_PRIM_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_MST_PRIM_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_MST_PRIM_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_MST_PRIM_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_MSTPrim.animPaused) {
			if (visEngine_MSTPrim.time < visEngine_MSTPrim.targetTime) {
				visEngine_MSTPrim.increaseTime();
				visEngine_MSTPrim.time = std::min(visEngine_MSTPrim.time, visEngine_MSTPrim.targetTime);
			} else if (visEngine_MSTPrim.time > visEngine_MSTPrim.targetTime) {
				visEngine_MSTPrim.decreaseTime();
				visEngine_MSTPrim.time = std::max(visEngine_MSTPrim.time, visEngine_MSTPrim.targetTime);
			}
		} else {
			visEngine_MSTPrim.increaseTime();
		}
		break;
	default:
		break;
	}
	// visEngine_MSTPrim.graph.printAdjList(); // DEBUG
	// // DEBUG
	// std::cerr << "sfDrawables[ProgramState::VIS_MST_PRIM_SCREEN].drawables.size() = " << sfDrawables[ProgramState::VIS_MST_PRIM_SCREEN]->drawables.size() << std::endl;
	// std::cerr << "sfDrawablesDefaultView[ProgramState::VIS_MST_PRIM_SCREEN].drawables.size() = " << sfDrawablesDefaultView[ProgramState::VIS_MST_PRIM_SCREEN]->drawables.size ()<< std::endl;


	// std::cout << sfDrawables[ProgramState::VIS_MST_PRIM_SCREEN]->drawables.size() << std::endl;
	// printf("VisMSTPrimTable SFML function called\n"); // DEBUG
}



void Program::displayVisMSTPrimScreenGUI() {
	allowDragCanvas = true;

	// Show the demo window
	// ImGui::ShowDemoWindow();

	// Get the current window size
	sf::Vector2u sfml_window_size = window.getSize();

	ImGui::Begin("Prim MST Menu",
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
	ImGui::SliderFloat("Animation Speed", &visEngine_MSTPrim.dt, 0.001f, 0.499f);

	ImGui::BeginDisabled(!visEngine_MSTPrim.animPaused);
	if (ImGui::Button("Skip to Start")) {
		visEngine_MSTPrim.skipToStartState();
	}
	ImGui::EndDisabled();
	ImGui::SameLine();
	ImGui::BeginDisabled(!visEngine_MSTPrim.animPaused);
	if (ImGui::Button("Previous Step")) {
		visEngine_MSTPrim.prevStep();
	}
	ImGui::EndDisabled();
	ImGui::SameLine();
	if (ImGui::Button(visEngine_MSTPrim.animPaused ? "Play" : "Pause")) {
		visEngine_MSTPrim.animPaused = !visEngine_MSTPrim.animPaused;
		visEngine_MSTPrim.targetTime = visEngine_MSTPrim.time;
	}
	ImGui::SameLine();
	ImGui::BeginDisabled(!visEngine_MSTPrim.animPaused);
	if (ImGui::Button("Next Step")) {
		visEngine_MSTPrim.nextStep();
	}
	ImGui::EndDisabled();
	ImGui::SameLine();
	ImGui::BeginDisabled(!visEngine_MSTPrim.animPaused);
	if (ImGui::Button("Skip to Final")) {
		visEngine_MSTPrim.skipToFinalState();
	}
	ImGui::EndDisabled();

	ImGui::Separator();



	ImGui::Text("Hold right-click on a vertex to drag it.");

	// -- RUN MST_PRIM OPERATION --
	ImGui::BeginDisabled(visEngine_MSTPrim.animInProgress);
	ImGui::Text("Enter starting vertex:");
	if (ImGui::InputInt("Start vertex", &visEngine_MSTPrim.startVertexIDInput)) {
		visEngine_MSTPrim.startVertexIDInput = std::clamp(visEngine_MSTPrim.startVertexIDInput, 
			0, 
			static_cast<int>(visEngine_MSTPrim.graph.getNumVertex()) - 1);
	}
	// float f;
	// ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

	if (ImGui::Button("Run Prim\'s algorithm")) {
		visEngine_MSTPrim.startVertexID = visEngine_MSTPrim.startVertexIDInput;
		visEngine_MSTPrim.visMode = PrimVisMode::MST_PRIM;

		visEngine_MSTPrim.resetParams();
		visEngine_MSTPrim.animPaused = false; // Auto un-pause

		// Generate events
		visEngine_MSTPrim.eventList = visEngine_MSTPrim.getEventsPrim(visEngine_MSTPrim.startVertexID);
		std::cout << "run MSTPrim cool, " << visEngine_MSTPrim.eventList.size() << " events" << std::endl; // DEBUG
	}
	ImGui::EndDisabled();

	ImGui::Separator();


	// // -- INSERT OPERATION --
	// ImGui::BeginDisabled(visEngine_MSTPrim.animInProgress);
	// ImGui::Text("Enter key to insert:");
	// ImGui::InputInt("Key to insert", &visEngine_MSTPrim.keyToInsertInput);

	// if (ImGui::Button("Insert")) {
	// 	visEngine_MSTPrim.keyToInsert = visEngine_MSTPrim.keyToInsertInput;
	// 	visEngine_MSTPrim.visMode = PrimVisMode::INSERT;

	// 	visEngine_MSTPrim.resetParams();
	// 	visEngine_MSTPrim.animPaused = false; // Auto un-pause

	// 	// visEngine_MSTPrim.insert(visEngine_MSTPrim.keyToInsert);
	// 	// Generate events
	// 	visEngine_MSTPrim.eventList = visEngine_MSTPrim.getEventsInsert(visEngine_MSTPrim.keyToInsert);
	// 	std::cout << "insert MSTPrim tree cool" << std::endl; // DEBUG
	// }
	// ImGui::EndDisabled();

	// ImGui::Separator();


	// // -- REMOVE OPERATION --
	// ImGui::BeginDisabled(visEngine_MSTPrim.animInProgress);
	// ImGui::Text("Enter key of slot to remove:");
	// ImGui::InputInt("Key to remove", &visEngine_MSTPrim.keyToRemoveInput);

	// if (ImGui::Button("Remove")) {
	// 	visEngine_MSTPrim.keyToRemove = visEngine_MSTPrim.keyToRemoveInput;
	// 	visEngine_MSTPrim.visMode = PrimVisMode::REMOVE;

	// 	visEngine_MSTPrim.resetParams();
	// 	visEngine_MSTPrim.animPaused = false; // Auto un-pause

	// 	// Generate events
	// 	visEngine_MSTPrim.eventList = visEngine_MSTPrim.getEventsDelete(visEngine_MSTPrim.keyToRemove);
	// 	std::cout << "remove MSTPrim tree cool" << std::endl; // DEBUG
	// }
	// ImGui::EndDisabled();

	// ImGui::Separator();


	// // -- UPDATE OPERATION --
	// ImGui::BeginDisabled(visEngine_MSTPrim.animInProgress);
	// ImGui::Text("Enter keys to update:");
	// ImGui::InputInt("Old key", &visEngine_MSTPrim.oldKeyToUpdateInput);
	// ImGui::InputInt("New key", &visEngine_MSTPrim.newKeyToUpdateInput);

	// bool updatable = (visEngine_MSTPrim.tree.getNodeKey(visEngine_MSTPrim.oldKeyToUpdateInput) != nullptr);
	// ImGui::BeginDisabled(!updatable);
	// if (ImGui::Button("Update")) {
	// 	visEngine_MSTPrim.keyToRemove = visEngine_MSTPrim.oldKeyToUpdateInput;
	// 	visEngine_MSTPrim.keyToInsert = visEngine_MSTPrim.newKeyToUpdateInput;
	// 	visEngine_MSTPrim.visMode = PrimVisMode::UPDATE;

	// 	visEngine_MSTPrim.resetParams();
	// 	visEngine_MSTPrim.animPaused = false; // Auto un-pause

	// 	// Generate events
	// 	// visEngine_MSTPrim.update(visEngine_MSTPrim.keyToRemove, visEngine_MSTPrim.keyToInsert);
	// 	visEngine_MSTPrim.eventList = visEngine_MSTPrim.getEventsUpdate(visEngine_MSTPrim.keyToRemove, visEngine_MSTPrim.keyToInsert);
	// 	std::cout << "update MSTPrim tree cool" << std::endl; // DEBUG
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



void Program::finishVisMSTPrimScreen() {

}
