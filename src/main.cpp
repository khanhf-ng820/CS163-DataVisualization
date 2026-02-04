#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>



int main() {
	sf::RenderWindow window(sf::VideoMode({640, 480}), "Data Structure Visualizer");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Clock deltaClock;
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


		ImGui::Begin("Hello, world!");
		ImGui::Button("Look at this pretty button");
		char* buf = new char[25];
		// ImGui::InputText("string", buf, IM_COUNTOF(buf));
		ImGui::InputText("string", buf, 25);
		float f;
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
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
			printf("Button clicked!\n");
		}

		ImGui::End();


		window.clear();
		window.draw(shape);
		
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}
