#include "UILayout/MainMenu.h"





// REMEMBER:
// Drawing SFML: The center of the window is now (0, 0) coordinates
// Drawing GUI: The top-left of the window is (0, 0) coordinates
// Display main menu screen
void Program::initMainMenuScreen() {
	allowDragCanvas = false;
}



void Program::displayMainMenuScreenSFML() {

}



void Program::displayMainMenuScreenGUI() {
	allowDragCanvas = false;

	// Show the demo window
	// ImGui::ShowDemoWindow();

	// Get the current window size
	sf::Vector2u sfml_window_size = window.getSize();

	ImGui::Begin("Hello, world!",
		nullptr
		// ImGuiWindowFlags_NoCollapse
		// ImGuiWindowFlags_NoBackground
	);
	ImGui::Button("Look at this pretty button");
	// char buf[25];
	// ImGui::InputText("string", buf, IM_COUNTOF(buf));
	ImGui::InputText("string", buf, 25);
	// float f;
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
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
	ImGui::SetNextWindowPos(btnPosition - btnSize / 2U);
	ImGui::Begin("StartBtn",
		nullptr,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoBackground
	);

	if (ImGui::Button("Start", btnSize)) { // clicked
		printf("%s %f\nButton clicked!\n", buf, f);
	}
	ImGui::End();


	btnSize = sf::Vector2u(120, 40);
	btnPosition = sfml_window_size / 2U + sf::Vector2u(0, 60);
	ImGui::SetNextWindowPos(btnPosition - btnSize / 2U);
	ImGui::Begin("SettingsBtn",
		nullptr,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoBackground
	);

	if (ImGui::Button("Settings", btnSize)) { // clicked
		printf("Go to Settings menu.\n");
		programState = ProgramState::SETTINGS_MENU;
	}
	ImGui::End();


	btnSize = sf::Vector2u(120, 40);
	btnPosition = sfml_window_size / 2U + sf::Vector2u(0, 120);
	ImGui::SetNextWindowPos(btnPosition - btnSize / 2U);
	ImGui::Begin("QuitBtn",
		nullptr,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoBackground
	);

	if (ImGui::Button("Quit", btnSize)) { // clicked
		printf("Program exited.\n");
		window.close();
	}
	ImGui::End();


	ImGui::SetNextWindowPos({200, 150});
	ImGui::Begin("BtnWin",
		nullptr,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoBackground
	);

	if (ImGui::Button("OK", {120, 40})) {
		// clicked
		printf("%s %f\nButton clicked!\n", buf, f);
	}
	ImGui::End();
}



void Program::finishMainMenuScreen() {

}
