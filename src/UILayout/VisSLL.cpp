#include "UILayout/VisSLL.h"





// REMEMBER:
// Drawing SFML: The center of the window is now (0, 0) coordinates
// Drawing GUI: The top-left of the window is (0, 0) coordinates
// Display vis SLL screen, set up SFML drawables
void Program::initVisSLLScreen() {
	// auto shape = std::make_unique<sf::CircleShape>(101.0f);
	// shape->setFillColor(sf::Color::Green);
	// auto rectangle = std::make_unique<sf::RectangleShape>(sf::Vector2f({NORMAL_WIDTH, NORMAL_HEIGHT}));
	// rectangle->setFillColor(sf::Color::Blue);

	// auto border = std::make_unique<sf::RectangleShape>(sf::Vector2f({NORMAL_WIDTH, NORMAL_HEIGHT}));
	// border->setOrigin({NORMAL_WIDTH / 2.f, NORMAL_HEIGHT / 2.f}); // origin at center
	// border->setPosition({0.f, 0.f}); // position at 0,0
	// border->setFillColor(sf::Color::Transparent);
	// border->setOutlineColor(sf::Color::Red);
	// border->setOutlineThickness(5.f);

	// auto splitCircle = std::make_unique<sf::CircleShape>(60.f);
	// splitCircle->setFillColor(sf::Color::Yellow);
	// // set origin
	// splitCircle->setOrigin({60.f, 60.f}); 
	// // set position
	// splitCircle->setPosition({NORMAL_WIDTH / 2.f, 0.f});

	// auto cornerBox = std::make_unique<sf::RectangleShape>(sf::Vector2f({100.f, 100.f}));
	// cornerBox->setFillColor(sf::Color::Green);
	// // set origin
	// cornerBox->setOrigin({50.f, 50.f});
	// // set position
	// cornerBox->setPosition({NORMAL_WIDTH / 2.f, NORMAL_HEIGHT / 2.f});


	// auto text = std::make_unique<sf::Text>(textFont, "Singly Linked List", 40);
	// text->setFillColor(sf::Color::Black);

	// // Measure unscaled text
	// sf::FloatRect bounds = text->getLocalBounds();

	// // Scale so the width matches your desired width
	// const float targetWidth = NORMAL_WIDTH * 0.625;
	// float scale = targetWidth / bounds.size.x;
	// text->setScale({scale, scale});

	// // Set origin to the visual center
	// text->setOrigin({
	// 	bounds.size.x / 2.f,
	// 	bounds.size.y / 2.f
	// });
	// // Position the center where you want it
	// sf::Vector2u window_size = window.getSize();
	// text->setPosition({0.f, -static_cast<float>(window_size.y) / 4});


	// Push back to vector
	sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables.clear();
	// sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables.push_back(std::move(shape));
	// sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables.push_back(std::move(rectangle));
	// sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables.push_back(std::move(border));
	// sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables.push_back(std::move(splitCircle));
	// sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables.push_back(std::move(cornerBox));
	// sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables.push_back(std::move(text));
	// printf("VisSLL SFML init function called\n"); // DEBUG


}



void Program::displayVisSLLScreenSFML() {
	switch (visEngine_SLL.visMode) {
	// NONE MODE (STILL MODE)
	case SLLVisMode::NONE:
		visEngine_SLL.eventList = std::vector<SLLAnimStep>();
		visEngine_SLL.createDrawables(
			sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables
		);
		sfDrawables[ProgramState::VIS_SLL_SCREEN]->displayAll();
		if (!visEngine_SLL.animPaused) visEngine_SLL.increaseTime();
		break;
	// SEARCH MODE
	case SLLVisMode::SEARCH:
		visEngine_SLL.eventList = visEngine_SLL.getEventsSearch(visEngine_SLL.valToSearch);
		visEngine_SLL.createDrawables(
			sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables
		);
		sfDrawables[ProgramState::VIS_SLL_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_SLL.animPaused) {
			if (visEngine_SLL.time < visEngine_SLL.targetTime) {
				visEngine_SLL.increaseTime();
				visEngine_SLL.time = std::min(visEngine_SLL.time, visEngine_SLL.targetTime);
			} else if (visEngine_SLL.time > visEngine_SLL.targetTime) {
				visEngine_SLL.decreaseTime();
				visEngine_SLL.time = std::max(visEngine_SLL.time, visEngine_SLL.targetTime);
			}
		} else {
			visEngine_SLL.increaseTime();
		}
		break;
	// INSERT BEGINNING MODE
	case SLLVisMode::INSERT_BEG:
		visEngine_SLL.eventList = visEngine_SLL.getEventsInsert(visEngine_SLL.valToInsert, visEngine_SLL.idxToInsert);
		visEngine_SLL.createDrawables(
			sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables
		);
		sfDrawables[ProgramState::VIS_SLL_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_SLL.animPaused) {
			if (visEngine_SLL.time < visEngine_SLL.targetTime) {
				visEngine_SLL.increaseTime();
				visEngine_SLL.time = std::min(visEngine_SLL.time, visEngine_SLL.targetTime);
			} else if (visEngine_SLL.time > visEngine_SLL.targetTime) {
				visEngine_SLL.decreaseTime();
				visEngine_SLL.time = std::max(visEngine_SLL.time, visEngine_SLL.targetTime);
			}
		} else {
			visEngine_SLL.increaseTime();
		}
		break;
	// INSERT END MODE
	case SLLVisMode::INSERT_END:
		visEngine_SLL.eventList = visEngine_SLL.getEventsInsert(visEngine_SLL.valToInsert, visEngine_SLL.idxToInsert);
		visEngine_SLL.createDrawables(
			sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables
		);
		sfDrawables[ProgramState::VIS_SLL_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_SLL.animPaused) {
			if (visEngine_SLL.time < visEngine_SLL.targetTime) {
				visEngine_SLL.increaseTime();
				visEngine_SLL.time = std::min(visEngine_SLL.time, visEngine_SLL.targetTime);
			} else if (visEngine_SLL.time > visEngine_SLL.targetTime) {
				visEngine_SLL.decreaseTime();
				visEngine_SLL.time = std::max(visEngine_SLL.time, visEngine_SLL.targetTime);
			}
		} else {
			visEngine_SLL.increaseTime();
		}
		break;
	// INSERT K-TH NODE MODE
	case SLLVisMode::INSERT_K:
		visEngine_SLL.eventList = visEngine_SLL.getEventsInsert(visEngine_SLL.valToInsert, visEngine_SLL.idxToInsert);
		visEngine_SLL.createDrawables(
			sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables
		);
		sfDrawables[ProgramState::VIS_SLL_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_SLL.animPaused) {
			if (visEngine_SLL.time < visEngine_SLL.targetTime) {
				visEngine_SLL.increaseTime();
				visEngine_SLL.time = std::min(visEngine_SLL.time, visEngine_SLL.targetTime);
			} else if (visEngine_SLL.time > visEngine_SLL.targetTime) {
				visEngine_SLL.decreaseTime();
				visEngine_SLL.time = std::max(visEngine_SLL.time, visEngine_SLL.targetTime);
			}
		} else {
			visEngine_SLL.increaseTime();
		}
		break;
	// UPDATE MODE
	case SLLVisMode::UPDATE:
		visEngine_SLL.eventList = visEngine_SLL.getEventsUpdate(visEngine_SLL.valToUpdate, visEngine_SLL.idxToUpdate);
		visEngine_SLL.createDrawables(
			sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables
		);
		sfDrawables[ProgramState::VIS_SLL_SCREEN]->displayAll();

		// If not paused, just increase / decrease time
		if (visEngine_SLL.animPaused) {
			if (visEngine_SLL.time < visEngine_SLL.targetTime) {
				visEngine_SLL.increaseTime();
				visEngine_SLL.time = std::min(visEngine_SLL.time, visEngine_SLL.targetTime);
			} else if (visEngine_SLL.time > visEngine_SLL.targetTime) {
				visEngine_SLL.decreaseTime();
				visEngine_SLL.time = std::max(visEngine_SLL.time, visEngine_SLL.targetTime);
			}
		} else {
			visEngine_SLL.increaseTime();
		}
		break;
	default:
		break;
	}


	// initVisSLLScreen();
	// std::cout << sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables.size() << std::endl;
	// printf("VisSLL SFML function called\n"); // DEBUG
}



void Program::displayVisSLLScreenGUI() {
	allowDragCanvas = true;

	// Show the demo window
	// ImGui::ShowDemoWindow();

	// Get the current window size
	sf::Vector2u sfml_window_size = window.getSize();

	ImGui::Begin("Singly Linked List Menu",
		nullptr
		// ImGuiWindowFlags_NoCollapse
		// ImGuiWindowFlags_NoBackground
	);
	// -- GO BACK BUTTON
	if (ImGui::Button("Back to Main Menu")) {
		programState = ProgramState::MAIN_MENU;
		resizeView();
	}
	// -- SPEED/PAUSE/STEP MENU
	ImGui::SliderFloat("Animation Speed", &visEngine_SLL.dt, 0.001f, 0.499f);

	ImGui::BeginDisabled(!visEngine_SLL.animPaused);
	if (ImGui::Button("Previous Step")) {
		visEngine_SLL.prevStep();
	}
	ImGui::EndDisabled();
	ImGui::SameLine();
	if (ImGui::Button("Pause/Unpause")) {
		visEngine_SLL.animPaused = !visEngine_SLL.animPaused;
		visEngine_SLL.targetTime = visEngine_SLL.time;
	}
	ImGui::SameLine();
	ImGui::BeginDisabled(!visEngine_SLL.animPaused);
	if (ImGui::Button("Next Step")) {
		visEngine_SLL.nextStep();
	}
	ImGui::EndDisabled();
	if (visEngine_SLL.animPaused) {
		ImGui::SameLine();
		ImGui::Text("Paused");
	}

	ImGui::Separator();

	// -- SEARCH OPERATION --
	ImGui::BeginDisabled(visEngine_SLL.animInProgress);
	ImGui::Text("Enter value to search:");
	ImGui::InputInt("Value to search", &visEngine_SLL.valToSearchInput);
	// float f;
	// ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

	if (ImGui::Button("Search")) {
		visEngine_SLL.valToSearch = visEngine_SLL.valToSearchInput;
		visEngine_SLL.visMode = SLLVisMode::SEARCH;
		visEngine_SLL.resetParams();
		visEngine_SLL.animPaused = false;
	}
	ImGui::EndDisabled();

	ImGui::Separator();

	// -- INSERT OPERATION --
	ImGui::BeginDisabled(visEngine_SLL.animInProgress);
	ImGui::Text("Enter value to insert:");
	ImGui::InputInt("Value to insert", &visEngine_SLL.valToInsertInput);
	ImGui::InputInt("Index to insert", &visEngine_SLL.idxToInsertInput);

	bool idxOutOfRange = !(visEngine_SLL.idxToInsertInput >= 0 && visEngine_SLL.idxToInsertInput <= visEngine_SLL.size);
	if (idxOutOfRange) {
		if (visEngine_SLL.size > 0)
			ImGui::Text("Index must be between 0 and %d.", visEngine_SLL.size);
		else
			ImGui::Text("Index must be 0.");
	}
	ImGui::BeginDisabled(idxOutOfRange);
	if (ImGui::Button("Insert")) {
		visEngine_SLL.valToInsert = visEngine_SLL.valToInsertInput;
		visEngine_SLL.idxToInsert = visEngine_SLL.idxToInsertInput;
		if (visEngine_SLL.idxToInsert == 0) {
			visEngine_SLL.visMode = SLLVisMode::INSERT_BEG;
		} else if (visEngine_SLL.idxToInsert == visEngine_SLL.size) {
			visEngine_SLL.visMode = SLLVisMode::INSERT_END;
		} else {
			visEngine_SLL.visMode = SLLVisMode::INSERT_K;
		}
		visEngine_SLL.resetParams();
		visEngine_SLL.animPaused = false;

		visEngine_SLL.insert(visEngine_SLL.valToInsert, visEngine_SLL.idxToInsert);
		printf("insert cool"); // DEBUG
	}
	ImGui::EndDisabled();
	ImGui::EndDisabled();

	ImGui::Separator();

	// -- UPDATE OPERATION --
	ImGui::BeginDisabled(visEngine_SLL.animInProgress);
	ImGui::Text("Enter value to update:");
	ImGui::InputInt("Value to update", &visEngine_SLL.valToUpdateInput);
	ImGui::InputInt("Index to update", &visEngine_SLL.idxToUpdateInput);

	idxOutOfRange = !(visEngine_SLL.idxToUpdateInput >= 0 && visEngine_SLL.idxToUpdateInput <= visEngine_SLL.size);
	if (idxOutOfRange) {
		if (visEngine_SLL.size > 0)
			ImGui::Text("Index must be between 0 and %d.", visEngine_SLL.size);
		else
			ImGui::Text("Index must be 0.");
	}
	ImGui::BeginDisabled(idxOutOfRange);
	if (ImGui::Button("Update")) {
		visEngine_SLL.valToUpdate = visEngine_SLL.valToUpdateInput;
		visEngine_SLL.idxToUpdate = visEngine_SLL.idxToUpdateInput;
		visEngine_SLL.visMode = SLLVisMode::UPDATE;
		visEngine_SLL.resetParams();
		visEngine_SLL.animPaused = false;

		visEngine_SLL.update(visEngine_SLL.valToUpdate, visEngine_SLL.idxToUpdate);
		printf("update cool"); // DEBUG
	}
	ImGui::EndDisabled();
	ImGui::EndDisabled();

	ImGui::Separator();

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


	sf::Vector2u btnSize, btnPosition;
	btnSize = sf::Vector2u(120, 40);
	btnPosition = sfml_window_size / 2U;
	// ImGui::SetNextWindowPos(btnPosition - btnSize / 2U);
	// ImGui::Begin("StartBtn",
	// 	nullptr,
	// 	ImGuiWindowFlags_NoTitleBar |
	// 	ImGuiWindowFlags_NoCollapse |
	// 	ImGuiWindowFlags_NoResize |
	// 	ImGuiWindowFlags_NoMove |
	// 	// ImGuiWindowFlags_NoBackground |
	// 	ImGuiWindowFlags_NoScrollbar
	// );

	// if (ImGui::Button("Start", btnSize)) { // clicked
	// 	printf("%s %f\nButton clicked!\n", buf, f);
	// 	printf("-- Data structure selection menu.\n");
	// 	// programState = ProgramState::CHOOSE_DS_MENU;
	// }
	// ImGui::End();
}



void Program::finishVisSLLScreen() {

}
