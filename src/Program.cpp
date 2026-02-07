#include "Program.h"



Program::Program()
	: window(sf::VideoMode({static_cast<unsigned int>(GAME_WIDTH), static_cast<unsigned int>(GAME_HEIGHT)}), PROGRAM_WINDOW_NAME)
	// , view(sf::FloatRect({0.f, 0.f}, {GAME_WIDTH, GAME_HEIGHT}))
	, view(window.getDefaultView())
{
	window.requestFocus();
	window.setFramerateLimit(FRAMERATE_LIMIT);
	init_successful = ImGui::SFML::Init(window);
	ImGui::StyleColorsDark();

	// Styling ImGui windows
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	// Modify the window background color (RGB alpha)
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.6f, 0.4f, 0.6f, 0.9f);
	// Can adjust padding, rounding, borders, etc., here.

	resizeView();
}


void Program::mainLoop() {
	if (!init_successful) {
		printf("Dear ImGui initialization unsuccessful!!!\n");
		return; // Initialization unsuccessful
	}

	sf::CircleShape shape(100.0f);
	shape.setFillColor(sf::Color::Green);
	sf::RectangleShape rectangle({GAME_WIDTH, GAME_HEIGHT});
	rectangle.setFillColor(sf::Color::Blue);

	char* buf = new char[25];
	float f;

	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			ImGui::SFML::ProcessEvent(window, *event);

			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			// When window is RESIZED
			else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
				// Update view
				resizeView();
				
				// Note: ImGui usually handles resizing on its own, but we need to update the SFML view
				// so that the window’s default view matches the new size (for UI if needed)
				sf::View defaultView = window.getDefaultView();
				defaultView.setSize({static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)});
				// Don't set viewport to defaultView because we want UI to cover entire window
			}
			// Start dragging
			if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mb->button == sf::Mouse::Button::Left &&
					!ImGui::GetIO().WantCaptureMouse)
				{
					draggingCanvas = true;

					lastWorldPos = window.mapPixelToCoords(
						{mb->position.x, mb->position.y}, view);
				}
			}

			// Stop dragging
			if (const auto* mb = event->getIf<sf::Event::MouseButtonReleased>())
			{
				if (mb->button == sf::Mouse::Button::Left)
					draggingCanvas = false;
			}
		}

		// If mouse is dragging canvas
		if (draggingCanvas)
		{
			sf::Vector2i pixel = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixel, view);

			sf::Vector2f delta = lastWorldPos - worldPos;
			view.move(delta);

			lastWorldPos = window.mapPixelToCoords(pixel, view);
		}

		ImGui::SFML::Update(window, deltaClock.restart());


		// Show the demo window
		// ImGui::ShowDemoWindow();


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



		// window.clear();
		window.clear(sf::Color(20, 20, 20));

		// Use view of app (centered and scaled)
		window.setView(view);

		window.draw(rectangle);
		window.draw(shape);

		// Use default view to draw ImGui GUI
		// ImGui is drawn over entire window instead
		window.setView(window.getDefaultView());
		
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();


	// Delete everything on the heap
	delete[] buf;
}


// Function to update view based on new window resolution
void Program::resizeView() {
	float windowRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
	float gameRatio = GAME_WIDTH / GAME_HEIGHT;
	float sizeX = 1.0f;
	float sizeY = 1.0f;
	float posX = 0.0f;
	float posY = 0.0f;

	// Compare ratios to decide Letterboxing or Pillarboxing
	if (windowRatio >= gameRatio) {
		// Wider -> Pillarboxing
		sizeX = gameRatio / windowRatio;
		posX = (1.0f - sizeX) / 2.0f;
	} else {
		// Taller -> Letterboxing
		sizeY = windowRatio / gameRatio;
		posY = (1.0f - sizeY) / 2.0f;
	}

	// Set Viewport
	// Viewport uses coordinates 0.0 -> 1.0
	view.setSize({GAME_WIDTH, GAME_HEIGHT});
	view.setViewport(sf::FloatRect({posX, posY}, {sizeX, sizeY}));
}
