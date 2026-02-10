#include "Program.h"



Program::Program()
	: window(sf::VideoMode({static_cast<unsigned int>(NORMAL_WIDTH), static_cast<unsigned int>(NORMAL_HEIGHT)}), PROGRAM_WINDOW_NAME
		// , sf::Style::Titlebar | sf::Style::Close
	)
	// , view(sf::FloatRect({0.f, 0.f}, {NORMAL_WIDTH, NORMAL_HEIGHT}))
	, view(window.getDefaultView())
	, textFont(fs::path(ASSET_DIR) / "Roboto_Mono/RobotoMono-VariableFont_wght.ttf")
{
	window.requestFocus();
	window.setFramerateLimit(FRAMERATE_LIMIT);
	window.setMinimumSize(MINIMUM_WINDOW_SIZE);
	// window.setMaximumSize(sf::Vector2u(1200, 900));
	init_successful = ImGui::SFML::Init(window);
	ImGui::StyleColorsDark();

	// Styling ImGui windows
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	// Modify the window background color (RGB alpha)
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.6f, 0.4f, 0.6f, 0.9f);
	// Can adjust padding, rounding, borders,...
	// io.FontGlobalScale = 2.0f;

	resizeView();
}


// Function to update view based on new window resolution
void Program::resizeView() {
	sf::Vector2f windowSize = sf::Vector2f(window.getSize());

	// Calculate amount to scale
	float scaleX = windowSize.x / NORMAL_WIDTH;
	float scaleY = windowSize.y / NORMAL_HEIGHT;

	// Use smaller scale factor
	float scale = std::min(scaleX, scaleY);

	// Set size of view to see the outside
	if (scale > 0.0f) { // avoid div by 0
		view.setSize({windowSize.x / scale, windowSize.y / scale});
	}
	
	// set center of view camera
	view.setCenter({0.0f, 0.0f});
}


void Program::mainLoop() {
	if (!init_successful) {
		printf("Dear ImGui initialization unsuccessful!!!\n");
		return; // Initialization unsuccessful
	}

	// REMEMBER:
	// Drawing SFML: The center of the window is now (0, 0) coordinates
	// Drawing GUI: The top-left of the window is (0, 0) coordinates
	sf::CircleShape shape(100.0f);
	shape.setFillColor(sf::Color::Green);
	sf::RectangleShape rectangle({NORMAL_WIDTH, NORMAL_HEIGHT});
	rectangle.setFillColor(sf::Color::Blue);

	sf::RectangleShape border({NORMAL_WIDTH, NORMAL_HEIGHT});
	border.setOrigin({NORMAL_WIDTH / 2.f, NORMAL_HEIGHT / 2.f}); // origin at center
	border.setPosition({0.f, 0.f}); // position at 0,0
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineColor(sf::Color::Red);
	border.setOutlineThickness(5.f);

	sf::CircleShape splitCircle(60.f);
	splitCircle.setFillColor(sf::Color::Yellow);
	// set origin
	splitCircle.setOrigin({60.f, 60.f}); 
	// set position
	splitCircle.setPosition({NORMAL_WIDTH / 2.f, 0.f});

	sf::RectangleShape cornerBox({100.f, 100.f});
	cornerBox.setFillColor(sf::Color::Green);
	// set origin
	cornerBox.setOrigin({50.f, 50.f});
	// set position
	cornerBox.setPosition({NORMAL_WIDTH / 2.f, NORMAL_HEIGHT / 2.f});


	sf::Text text(textFont, "Data Structure Visualizer", 40);
	text.setFillColor(sf::Color::White);

	// 1. Measure unscaled text
	sf::FloatRect bounds = text.getLocalBounds();

	// 2. Scale so the width matches your desired width
	float targetWidth = 1000.f;
	float scale = targetWidth / bounds.size.x;
	text.setScale({scale, scale});

	// 3. Set origin to the visual center
	text.setOrigin({
		bounds.size.x / 2.f,
		bounds.size.y / 2.f
	});
	// 4. Position the center where you want it
	sf::Vector2u window_size = window.getSize();
	text.setPosition({0.f, -static_cast<float>(window_size.y) / 4});


	// Initialization step (SFML/GUI)
	switch (programState) {
	case ProgramState::MAIN_MENU:
		initMainMenuScreen();
		break;
	case ProgramState::SETTINGS_MENU:
		initSettingsMenuScreen();
		break;
	default:
		break;
	};



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
			if (!allowDragCanvas) continue;
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

		// Get the current window size
		window_size = window.getSize();



		// Display GUI
		switch (programState) {
		case ProgramState::MAIN_MENU:
			displayMainMenuScreenGUI();
			break;
		case ProgramState::SETTINGS_MENU:
			displaySettingsMenuScreenGUI();
			break;
		default:
			break;
		};



		// window.clear();
		// window.clear(sf::Color(20, 100, 20));
		window.clear(sf::Color::Black);

		// Use view of app (centered and scaled)
		window.setView(view);


		// Draw objects
		window.draw(rectangle);
		window.draw(shape);
		window.draw(border);      // Border
		window.draw(splitCircle); // Yellow circle on border
		window.draw(cornerBox);   // Box on border
		window.draw(text);        // Text


		ImGui::SFML::Render(window);
		// Use default view to draw ImGui GUI
		// ImGui is drawn over entire window instead
		window.setView(window.getDefaultView());
		
		window.display();
	}

	ImGui::SFML::Shutdown();


	// Delete everything on the heap
	delete[] buf;
}




// Display test screen (FOR TESTING ONLY)
// void displayTestScreen();

