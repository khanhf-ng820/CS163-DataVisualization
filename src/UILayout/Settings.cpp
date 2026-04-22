#include "UILayout/Settings.h"





// REMEMBER:
// Drawing SFML: The center of the window is now (0, 0) coordinates
// Drawing GUI: The top-left of the window is (0, 0) coordinates
// Display settings menu screen
void Program::initSettingsMenuScreen() {
	allowDragCanvas = false;
}



void Program::displaySettingsMenuScreenSFML() {

}



void Program::displaySettingsMenuScreenGUI() {
	allowDragCanvas = false;

	// Show the demo window
	// ImGui::ShowDemoWindow();

	// Get the current window size
	sf::Vector2u sfml_window_size = window.getSize();

	// ImGui::Begin("Hello, world!",
	// 	nullptr
	// 	// ImGuiWindowFlags_NoCollapse
	// 	// ImGuiWindowFlags_NoBackground
	// );
	// ImGui::Button("Look at this pretty button");
	// // char buf[25];
	// // ImGui::InputText("string", buf, IM_COUNTOF(buf));
	// ImGui::InputText("string", buf, 25);
	// // float f;
	// ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

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
	// ImGui::End();


	// sf::Vector2u btnSize, btnPosition;
	// btnSize = sf::Vector2u(120, 40);
	// btnPosition = sfml_window_size / 2U;
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
	// 	printf("%s %f\nButton clicked! \n", buf, f);
	// }
	// ImGui::End();


	// btnSize = sf::Vector2u(120, 40);
	// btnPosition = sfml_window_size / 2U + sf::Vector2u(0, 60);
	// ImGui::SetNextWindowPos(btnPosition - btnSize / 2U);
	// ImGui::Begin("SettingsBtn",
	// 	nullptr,
	// 	ImGuiWindowFlags_NoTitleBar |
	// 	ImGuiWindowFlags_NoCollapse |
	// 	ImGuiWindowFlags_NoResize |
	// 	ImGuiWindowFlags_NoMove |
	// 	// ImGuiWindowFlags_NoBackground |
	// 	ImGuiWindowFlags_NoScrollbar
	// );

	// if (ImGui::Button("Settings", btnSize)) { // clicked
	// 	printf("Program exited.\n");
	// 	window.close();
	// }
	// ImGui::End();


	// btnSize = sf::Vector2u(120, 40);
	// btnPosition = sfml_window_size / 2U + sf::Vector2u(0, 120);
	// ImGui::SetNextWindowPos(btnPosition - btnSize / 2U);
	// ImGui::Begin("QuitBtn",
	// 	nullptr,
	// 	ImGuiWindowFlags_NoTitleBar |
	// 	ImGuiWindowFlags_NoCollapse |
	// 	ImGuiWindowFlags_NoResize |
	// 	ImGuiWindowFlags_NoMove |
	// 	// ImGuiWindowFlags_NoBackground |
	// 	ImGuiWindowFlags_NoScrollbar
	// );

	// if (ImGui::Button("Quit", btnSize)) { // clicked
	// 	printf("Program exited.\n");
	// 	window.close();
	// }
	// ImGui::End();



	// sf::Vector2u gui_window_size(400, 500);
	sf::Vector2u gui_window_size(sfml_window_size.x / 2, sfml_window_size.y * 0.75f);
	ImGui::SetNextWindowPos(sfml_window_size / 2U - gui_window_size / 2U);
	ImGui::SetNextWindowSize(gui_window_size, ImGuiCond_Always);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	ImGui::Begin("Settings",
		nullptr,
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove
	);
	ImGui::PopStyleColor();

	if (ImGui::Button("<- Go back")) {
		programState = ProgramState::MAIN_MENU;
		std::cout << "-- Go to main menu." << std::endl;
		resizeView();
	}

	ImGui::Separator();
	ImGui::Text("Window resolution:");
	// ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(173.f/255, 216.f/255, 230.f/255, 1.f));
	if (ImGui::BeginCombo("##resolution_combo", resolutionOptions[current_resolution_item])) { // Pass the "current" item name as the preview
		for (int n = 0; n < IM_ARRAYSIZE(resolutionOptions); n++) {
			bool is_selected = (current_resolution_item == n);
			if (ImGui::Selectable(resolutionOptions[n], is_selected)) {
				current_resolution_item = n;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation)
			if (is_selected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	// ImGui::PopStyleColor();


	ImGui::Separator();
	ImGui::Text("GUI Theme:");
	if (ImGui::BeginCombo("##appTheme_combo", appThemeOptions[current_appTheme_item])) { // Pass the "current" item name as the preview
		for (int n = 0; n < IM_ARRAYSIZE(appThemeOptions); n++) {
			bool is_selected = (current_appTheme_item == n);
			if (ImGui::Selectable(appThemeOptions[n], is_selected)) {
				current_appTheme_item = n;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation)
			if (is_selected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}


	ImGui::Separator();
	ImGui::Text("GUI Font Size:");
	static int ui_size_step = 1;
	static float real_ui_scale = 1 + (ui_size_step - 1) * 0.25f;
	if (ImGui::SliderInt("##UI Font Size", &ui_size_step, 1, 5)) {
		real_ui_scale = 1 + (ui_size_step - 1) * 0.25f;
	}


	ImGui::Separator();
	ImGui::Text("Visualization Theme: ");
	if (ImGui::BeginCombo("##visTheme_combo", visThemeOptions[current_visTheme_item])) { // Pass the "current" item name as the preview
		for (int n = 0; n < IM_ARRAYSIZE(visThemeOptions); n++) {
			bool is_selected = (current_visTheme_item == n);
			if (ImGui::Selectable(visThemeOptions[n], is_selected)) {
				current_visTheme_item = n;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation)
			if (is_selected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}



	ImGui::Separator();
	if (ImGui::Button("Apply All Settings")) {
		window.setSize(resolutionVectors[current_resolution_item]);

		// Setting app GUI theme
		switch (appThemeVectors[current_appTheme_item]) {
		case APP_THEME::LIGHT:
			ImGui::StyleColorsLight(); // Light theme
			break;
		case APP_THEME::DARK:
			ImGui::StyleColorsDark(); // Dark theme
			break;
		case APP_THEME::PURPLE:
			ImGui::StyleColorsClassic(); // Purple theme
			break;
		}

		// Setting vis engine theme
		// switch (visThemeVectors[current_visTheme_item]) {
		// case VIS_THEME::LIGHT: // Light theme
		// 	currentVisTheme = VIS_THEME::LIGHT;
		// 	break;
		// case VIS_THEME::DARK: // Dark theme
		// 	currentVisTheme = VIS_THEME::DARK;
		// 	break;
		// }
		currentVisTheme = visThemeVectors[current_visTheme_item];
		refreshVisThemes();

		// Set UI font size
		// ioPtr->FontGlobalScale = real_ui_scale;
		ioPtr->Fonts->Clear();
		ioPtr->Fonts->AddFontFromFileTTF((fs::path(ASSET_DIR) / "Roboto/Roboto-VariableFont_wdth,wght.ttf").string().c_str(),
			UI_FONT_SIZE * real_ui_scale);

		// IMPORTANT for imgui-sfml: Re-create the font texture
		ImGui::SFML::UpdateFontTexture();
		// Scale all UI elements (paddings, spacing) to match
		// ImGui::GetStyle().ScaleAllSizes(real_ui_scale);



		// Set size for SFML text in default view
		// auto sfmlText = static_cast<sf::Text*>(sfDrawables[ProgramState::MAIN_MENU]->drawables[0].get());
		// sf::FloatRect bounds = titleText->getLocalBounds();
		// sfmlText->setSize(sf::Vector2f(window.getSize()));
		// sfmlText->setOrigin(sf::Vector2f(window.getSize()) / 2.f); // origin at center
	}


	ImGui::End();
}



void Program::finishSettingsMenuScreen() {

}
