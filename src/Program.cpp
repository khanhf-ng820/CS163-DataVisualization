#include "Program.h"



Program::Program()
	: window(sf::VideoMode({static_cast<unsigned int>(GAME_WIDTH), static_cast<unsigned int>(GAME_HEIGHT)}), "Data Structure Visualizer")
{
	window.requestFocus();
	window.setFramerateLimit(FRAMERATE_LIMIT);
	init_successful = ImGui::SFML::Init(window);
}


void Program::mainLoop() {
	if (!init_successful) return; // Initialization unsuccessful

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	char* buf = new char[25];
	float f;

	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			ImGui::SFML::ProcessEvent(window, *event);

			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());


		// Show the demo window
		// ImGui::ShowDemoWindow();


		ImGui::Begin("Hello, world!",
			nullptr,
			ImGuiWindowFlags_NoCollapse
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


		window.clear();
		window.draw(shape);
		
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();

	// Delete everything
	delete[] buf;
}
