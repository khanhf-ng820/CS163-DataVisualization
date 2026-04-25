#include "UILayout/VisTrie.h"





// REMEMBER:
// Drawing SFML: The center of the window is now (0, 0) coordinates
// Drawing GUI: The top-left of the window is (0, 0) coordinates
// Clear SFML drawables
void Program::initVisTrieScreen() {
	// Push back to vector
	sfDrawables[ProgramState::VIS_TRIE_SCREEN]->drawables.clear();
	sfDrawablesDefaultView[ProgramState::VIS_TRIE_SCREEN]->drawables.clear();
	// printf("VisTrie SFML init function called\n"); // DEBUG
}



// Display vis Trie Tree screen, set up SFML drawables
void Program::displayVisTrieScreenSFML() {
	switch (visEngine_Trie.visMode) {
	// ----- NO MODE (STILL MODE) -----
	case TrieVisMode::NONE:
		visEngine_Trie.eventList = std::vector<TrieAnimStep>();
		visEngine_Trie.createDrawables(
			sfDrawables[ProgramState::VIS_TRIE_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_TRIE_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_TRIE_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_TRIE_SCREEN]->displayAll();

		if (!visEngine_Trie.animPaused)
			visEngine_Trie.increaseTime();
		break;
	// ----- SEARCH MODE -----
	case TrieVisMode::SEARCH:
		// visEngine_Trie.eventList = visEngine_Trie.getEventsSearch(visEngine_Trie.keyToSearch);
		visEngine_Trie.createDrawables(
			sfDrawables[ProgramState::VIS_TRIE_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_TRIE_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_TRIE_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_TRIE_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_Trie.animPaused) {
			if (visEngine_Trie.time < visEngine_Trie.targetTime) {
				visEngine_Trie.increaseTime();
				visEngine_Trie.time = std::min(visEngine_Trie.time, visEngine_Trie.targetTime);
			} else if (visEngine_Trie.time > visEngine_Trie.targetTime) {
				visEngine_Trie.decreaseTime();
				visEngine_Trie.time = std::max(visEngine_Trie.time, visEngine_Trie.targetTime);
			}
		} else {
			visEngine_Trie.increaseTime();
		}
		break;
	// ----- INSERT MODE -----
	case TrieVisMode::INSERT:
		// visEngine_Trie.eventList = visEngine_Trie.getEventsInsert(visEngine_Trie.keyToInsert);
		visEngine_Trie.createDrawables(
			sfDrawables[ProgramState::VIS_TRIE_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_TRIE_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_TRIE_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_TRIE_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_Trie.animPaused) {
			if (visEngine_Trie.time < visEngine_Trie.targetTime) {
				visEngine_Trie.increaseTime();
				visEngine_Trie.time = std::min(visEngine_Trie.time, visEngine_Trie.targetTime);
			} else if (visEngine_Trie.time > visEngine_Trie.targetTime) {
				visEngine_Trie.decreaseTime();
				visEngine_Trie.time = std::max(visEngine_Trie.time, visEngine_Trie.targetTime);
			}
		} else {
			visEngine_Trie.increaseTime();
		}
		break;
	// ----- REMOVE MODE -----
	case TrieVisMode::REMOVE:
		// visEngine_Trie.eventList = visEngine_Trie.getEventsRemove(visEngine_Trie.keyToRemove);
		visEngine_Trie.createDrawables(
			sfDrawables[ProgramState::VIS_TRIE_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_TRIE_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_TRIE_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_TRIE_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_Trie.animPaused) {
			if (visEngine_Trie.time < visEngine_Trie.targetTime) {
				visEngine_Trie.increaseTime();
				visEngine_Trie.time = std::min(visEngine_Trie.time, visEngine_Trie.targetTime);
			} else if (visEngine_Trie.time > visEngine_Trie.targetTime) {
				visEngine_Trie.decreaseTime();
				visEngine_Trie.time = std::max(visEngine_Trie.time, visEngine_Trie.targetTime);
			}
		} else {
			visEngine_Trie.increaseTime();
		}
		break;
	// ----- UPDATE MODE -----
	case TrieVisMode::UPDATE:
		// visEngine_Trie.eventList = visEngine_Trie.getEventsUpdate(visEngine_Trie.oldKeyToUpdate, visEngine_Trie.newKeyToUpdate);
		visEngine_Trie.createDrawables(
			sfDrawables[ProgramState::VIS_TRIE_SCREEN]->drawables,
			sfDrawablesDefaultView[ProgramState::VIS_TRIE_SCREEN]->drawables
		);
		// Draw all drawables in both views (zoomable view and window's default view)
		window.setView(view);
		sfDrawables[ProgramState::VIS_TRIE_SCREEN]->displayAll();
		window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
		sfDrawablesDefaultView[ProgramState::VIS_TRIE_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_Trie.animPaused) {
			if (visEngine_Trie.time < visEngine_Trie.targetTime) {
				visEngine_Trie.increaseTime();
				visEngine_Trie.time = std::min(visEngine_Trie.time, visEngine_Trie.targetTime);
			} else if (visEngine_Trie.time > visEngine_Trie.targetTime) {
				visEngine_Trie.decreaseTime();
				visEngine_Trie.time = std::max(visEngine_Trie.time, visEngine_Trie.targetTime);
			}
		} else {
			visEngine_Trie.increaseTime();
		}
		break;
	default:
		break;
	}


	// std::cout << sfDrawables[ProgramState::VIS_TRIE_SCREEN]->drawables.size() << std::endl;
	// printf("VisTrieTable SFML function called\n"); // DEBUG
}



void Program::displayVisTrieScreenGUI() {
	allowDragCanvas = true;

	// Show the demo window
	// ImGui::ShowDemoWindow();

	// Get the current window size
	sf::Vector2u sfml_window_size = window.getSize();

	ImGui::Begin("Trie Tree Menu",
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
	ImGui::SliderFloat("Animation Speed", &visEngine_Trie.dt, 0.001f, 0.499f);

	ImGui::BeginDisabled(!visEngine_Trie.animPaused);
	if (ImGui::Button("Previous Step")) {
		visEngine_Trie.prevStep();
	}
	ImGui::EndDisabled();
	ImGui::SameLine();
	if (ImGui::Button(visEngine_Trie.animPaused ? "Play" : "Pause")) {
		visEngine_Trie.animPaused = !visEngine_Trie.animPaused;
		visEngine_Trie.targetTime = visEngine_Trie.time;
	}
	ImGui::SameLine();
	ImGui::BeginDisabled(!visEngine_Trie.animPaused);
	if (ImGui::Button("Next Step")) {
		visEngine_Trie.nextStep();
	}
	ImGui::EndDisabled();
	ImGui::SameLine();
	ImGui::BeginDisabled(!visEngine_Trie.animPaused);
	if (ImGui::Button("Skip to Final")) {
		visEngine_Trie.skipToFinalState();
	}
	ImGui::EndDisabled();

	ImGui::Separator();


	// -- SEARCH OPERATION --
	ImGui::BeginDisabled(visEngine_Trie.animInProgress);
	ImGui::Text("Enter word to search (lowercase a-z):");
	// float f;
	// ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
	ImGui::InputText("Word to search", visEngine_Trie.wordToSearchInput, 
		sizeof(visEngine_Trie.wordToSearchInput),
		ImGuiInputTextFlags_CallbackCharFilter,
		FilterCallbackLowercaseAZ);

	if (ImGui::Button("Search")) {
		visEngine_Trie.wordToSearch = visEngine_Trie.wordToSearchInput;
		visEngine_Trie.visMode = TrieVisMode::SEARCH;

		visEngine_Trie.resetParams();
		visEngine_Trie.animPaused = false; // Auto un-pause

		// Generate events
		visEngine_Trie.eventList = visEngine_Trie.getEventsSearch(visEngine_Trie.wordToSearch);
		std::cout << "search Trie tree cool, " << visEngine_Trie.eventList.size() << " events" << std::endl; // DEBUG
	}
	ImGui::EndDisabled();

	ImGui::Separator();


	// -- INSERT OPERATION --
	ImGui::BeginDisabled(visEngine_Trie.animInProgress);
	ImGui::Text("Enter word to insert (lowercase a-z):");
	ImGui::InputText("Word to insert", visEngine_Trie.wordToInsertInput, 
		sizeof(visEngine_Trie.wordToInsertInput),
		ImGuiInputTextFlags_CallbackCharFilter,
		FilterCallbackLowercaseAZ);

	if (ImGui::Button("Insert")) {
		visEngine_Trie.wordToInsert = visEngine_Trie.wordToInsertInput;
		visEngine_Trie.visMode = TrieVisMode::INSERT;

		visEngine_Trie.resetParams();
		visEngine_Trie.animPaused = false; // Auto un-pause

		// visEngine_Trie.insert(visEngine_Trie.wordToInsert);
		// Generate events
		visEngine_Trie.eventList = visEngine_Trie.getEventsInsert(visEngine_Trie.wordToInsert);
		std::cout << "insert Trie tree cool" << std::endl; // DEBUG
	}
	ImGui::EndDisabled();

	ImGui::Separator();


	// -- REMOVE OPERATION --
	ImGui::BeginDisabled(visEngine_Trie.animInProgress);
	ImGui::Text("Enter word to remove (lowercase a-z):");
	ImGui::InputText("Word to remove", visEngine_Trie.wordToRemoveInput, 
		sizeof(visEngine_Trie.wordToRemoveInput),
		ImGuiInputTextFlags_CallbackCharFilter,
		FilterCallbackLowercaseAZ);

	if (ImGui::Button("Remove")) {
		visEngine_Trie.wordToRemove = visEngine_Trie.wordToRemoveInput;
		visEngine_Trie.visMode = TrieVisMode::REMOVE;

		visEngine_Trie.resetParams();
		visEngine_Trie.animPaused = false; // Auto un-pause

		// Generate events
		visEngine_Trie.eventList = visEngine_Trie.getEventsDelete(visEngine_Trie.wordToRemove);
		std::cout << "remove Trie tree cool" << std::endl; // DEBUG
	}
	ImGui::EndDisabled();

	ImGui::Separator();


	// -- UPDATE OPERATION --
	ImGui::BeginDisabled(visEngine_Trie.animInProgress);
	ImGui::Text("Enter words to update (lowercase a-z):");
	ImGui::InputText("Old word", visEngine_Trie.oldWordToUpdateInput, 
		sizeof(visEngine_Trie.oldWordToUpdateInput),
		ImGuiInputTextFlags_CallbackCharFilter,
		FilterCallbackLowercaseAZ);
	ImGui::InputText("New word", visEngine_Trie.newWordToUpdateInput, 
		sizeof(visEngine_Trie.newWordToUpdateInput),
		ImGuiInputTextFlags_CallbackCharFilter,
		FilterCallbackLowercaseAZ);

	bool updatable = visEngine_Trie.tree.wordExists(std::string(visEngine_Trie.oldWordToUpdateInput));
	ImGui::BeginDisabled(!updatable);
	if (ImGui::Button("Update")) {
		visEngine_Trie.oldWordToUpdate = visEngine_Trie.oldWordToUpdateInput;
		visEngine_Trie.newWordToUpdate = visEngine_Trie.newWordToUpdateInput;
		visEngine_Trie.visMode = TrieVisMode::UPDATE;

		visEngine_Trie.resetParams();
		visEngine_Trie.animPaused = false; // Auto un-pause

		// Generate events
		// visEngine_Trie.update(visEngine_Trie.oldWordToUpdate, visEngine_Trie.newWordToUpdate);
		visEngine_Trie.eventList = visEngine_Trie.getEventsUpdate(visEngine_Trie.oldWordToUpdate, visEngine_Trie.newWordToUpdate);
		std::cout << "update Trie tree cool" << std::endl; // DEBUG
	}
	ImGui::EndDisabled();
	ImGui::EndDisabled();



	ImGui::End();
}



void Program::finishVisTrieScreen() {

}
