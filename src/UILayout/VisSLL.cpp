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
	case SLLVisMode::NONE:
		visEngine_SLL.createDrawables(
			sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables, 
			std::vector<SLLAnimStep>()
		);
		sfDrawables[ProgramState::VIS_SLL_SCREEN]->displayAll();
		visEngine_SLL.increaseTime();
		break;
	case SLLVisMode::SEARCH:
		visEngine_SLL.createDrawables(
			sfDrawables[ProgramState::VIS_SLL_SCREEN]->drawables, 
			visEngine_SLL.getEventsSearch(visEngine_SLL.valToSearch)
		);
		sfDrawables[ProgramState::VIS_SLL_SCREEN]->displayAll();
		visEngine_SLL.increaseTime();
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

	ImGui::Begin("Singly Linked List",
		nullptr
		// ImGuiWindowFlags_NoCollapse
		// ImGuiWindowFlags_NoBackground
	);
	// ImGui::Button("Look at this pretty button"); // useless button
	// char buf[25];
	// ImGui::InputText("string", buf, IM_COUNTOF(buf));
	ImGui::Text("Enter value to search:");
	ImGui::InputInt("Value to search", &visEngine_SLL.valToSearch);
	// float f;
	// ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

	if (ImGui::Button("Search")) {
		visEngine_SLL.visMode = SLLVisMode::SEARCH;
		visEngine_SLL.resetParams();
	}

	const char* items[] = { "Option 1", "Option 2", "Option 3", "Option 4" };
	static int current_item = 0;
	if (ImGui::BeginCombo("##mycombo", items[current_item])) { // Pass the "current" item name as the preview
		for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
			bool is_selected = (current_item == n);
			if (ImGui::Selectable(items[n], is_selected)) {
				current_item = n;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation)
			if (is_selected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
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
