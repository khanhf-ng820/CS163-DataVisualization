#include "Program.h"



Program::Program()
	: window(sf::VideoMode({static_cast<unsigned int>(NORMAL_WIDTH), static_cast<unsigned int>(NORMAL_HEIGHT)}), PROGRAM_WINDOW_NAME
		// , sf::Style::Titlebar | sf::Style::Close
	)
	// , view(sf::FloatRect({0.f, 0.f}, {NORMAL_WIDTH, NORMAL_HEIGHT}))
	, view(window.getDefaultView())
	, textFont(fs::path(ASSET_DIR) / "Roboto_Mono/RobotoMono-VariableFont_wght.ttf")
	, visEngine_SLL(window, textFont)
{
	window.requestFocus();
	window.setFramerateLimit(FRAMERATE_LIMIT);
	window.setMinimumSize(MINIMUM_WINDOW_SIZE);
	// window.setMaximumSize(sf::Vector2u(1200, 900));

	init_successful = ImGui::SFML::Init(window);
	ImGui::StyleColorsDark();
	// ImGui::StyleColorsClassic();

	// Styling ImGui windows
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	ioPtr = &io;
	stylePtr = &style;
	// Modify the window background color (RGB alpha)
	// style.Colors[ImGuiCol_WindowBg] = ImVec4(0.6f, 0.4f, 0.6f, 0.9f);
	// style.Colors[ImGuiCol_WindowBg] = ImVec4(173.f/255, 216.f/255, 230.f/255, 0.6f);
	// style.Colors[ImGuiCol_PopupBg] = ImVec4(173.f/255, 216.f/255, 230.f/255, 1.f);
	// style.Colors[ImGuiCol_Text] = ImVec4(0.f, 0.f, 0.f, 1.f);
	// Can adjust padding, rounding, borders,...
	// io.FontGlobalScale = 2.0f;

	// Initialize sfDrawables map to draw later
	sfDrawables[ProgramState::MAIN_MENU] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::SETTINGS_MENU] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::CHOOSE_DS_MENU] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::VIS_SLL_SCREEN] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::VIS_HASH_SCREEN] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::VIS_AVL_SCREEN] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::VIS_TRIE_SCREEN] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::VIS_MST_SCREEN] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::VIS_DIJKSTRA_SCREEN] = std::make_unique<sfLayout>(&window);

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
	sf::Vector2u window_size = window.getSize();



	// Initialization step (SFML/GUI)
	switch (programState) {
	case ProgramState::MAIN_MENU:
		initMainMenuScreen();
		break;
	case ProgramState::SETTINGS_MENU:
		initSettingsMenuScreen();
		break;
	case ProgramState::CHOOSE_DS_MENU:
		initChooseDSMenuScreen();
		break;
	case ProgramState::VIS_SLL_SCREEN:
		initVisSLLScreen();
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
			if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mb->button == sf::Mouse::Button::Left &&
					!ImGui::GetIO().WantCaptureMouse) {
					draggingCanvas = true;

					lastWorldPos = window.mapPixelToCoords(
						{mb->position.x, mb->position.y}, view);
				}
			}

			// Stop dragging
			if (const auto* mb = event->getIf<sf::Event::MouseButtonReleased>()) {
				if (mb->button == sf::Mouse::Button::Left)
					draggingCanvas = false;
			}
		}

		// If mouse is dragging canvas
		if (draggingCanvas) {
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
		case ProgramState::CHOOSE_DS_MENU:
			displayChooseDSMenuScreenGUI();
			break;
		case ProgramState::VIS_SLL_SCREEN:
			displayVisSLLScreenGUI();
			break;
		default:
			break;
		};



		// window.clear();
		// window.clear(sf::Color(20, 100, 20));
		window.clear(sf::Color::White);

		// Use view of app (centered and scaled)
		window.setView(view);


		// Display SFML
		switch (programState) {
		case ProgramState::MAIN_MENU:
			displayMainMenuScreenSFML();
			break;
		case ProgramState::SETTINGS_MENU:
			displaySettingsMenuScreenSFML();
			break;
		case ProgramState::CHOOSE_DS_MENU:
			displayChooseDSMenuScreenSFML();
			break;
		case ProgramState::VIS_SLL_SCREEN:
			displayVisSLLScreenSFML();
			break;
		default:
			break;
		};


		ImGui::SFML::Render(window);
		// Use default view to draw ImGui GUI
		// ImGui is drawn over entire window instead
		window.setView(window.getDefaultView());
		
		window.display();
	}

	ImGui::SFML::Shutdown();



	// Finish program
	switch (programState) {
	case ProgramState::MAIN_MENU:
		finishMainMenuScreen();
		break;
	case ProgramState::SETTINGS_MENU:
		finishSettingsMenuScreen();
		break;
	case ProgramState::CHOOSE_DS_MENU:
		finishChooseDSMenuScreen();
		break;
	case ProgramState::VIS_SLL_SCREEN:
		finishVisSLLScreen();
		break;
	default:
		break;
	};


	// Delete everything on the heap
	delete[] buf;
}




// Display test screen (FOR TESTING ONLY)
// void displayTestScreen();

