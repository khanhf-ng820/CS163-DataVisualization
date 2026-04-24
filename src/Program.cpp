#include "Program.h"



Program::Program()
	: window(sf::VideoMode({static_cast<unsigned int>(NORMAL_WIDTH), static_cast<unsigned int>(NORMAL_HEIGHT)}), PROGRAM_WINDOW_NAME
		// , sf::Style::Titlebar | sf::Style::Close
	)
	// , view(sf::FloatRect({0.f, 0.f}, {NORMAL_WIDTH, NORMAL_HEIGHT}))
	, view(window.getDefaultView())
	, textFont(fs::path(ASSET_DIR) / "Roboto_Mono" / "RobotoMono-VariableFont_wght.ttf")
	// , textFont(fs::path(ASSET_DIR) / "Roboto" / "Roboto-VariableFont_wdth,wght.ttf")
	, rng(std::random_device()())
	, visEngine_SLL(window, textFont), visEngine_Hash(&window, &textFont)
	, visEngine_AVL(&window, &textFont), visEngine_Trie(&window, &textFont)
	, visEngine_Dijkstra(1, &window, &textFont, &view)
	, visEngine_MSTPrim(1, &window, &textFont, &view)
{
	window.requestFocus();
	window.setFramerateLimit(FRAMERATE_LIMIT);
	window.setMinimumSize(MINIMUM_WINDOW_SIZE);
	// window.setMaximumSize(sf::Vector2u(1200, 900));
	textFont.setSmooth(true);
	settings.antiAliasingLevel = 8; // Anti aliasing (2 to 16)

	init_imgui_successful = ImGui::SFML::Init(window);
	ImGui::StyleColorsDark(); // Dark theme
	// ImGui::StyleColorsClassic(); // Classic theme

	// -- Styling ImGui windows
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	ioPtr = &io;
	stylePtr = &style;

	// -- Font and font size for ImGui
	std::cerr << "-- Loading fonts...\n";
	ioPtr->Fonts->Clear();
	// 5 sizes each font
	for (int i = 0; i < NUM_FONT_SIZE; i++) {
		ImFont* imguiFont = ioPtr->Fonts->AddFontFromFileTTF((fs::path(ASSET_DIR) / "Roboto" / "Roboto-VariableFont_wdth,wght.ttf").string().c_str(),
			NORMAL_UI_FONT_SIZE * (1 + i * 0.25f));
		assert(imguiFont != nullptr);
		imFonts.push_back(imguiFont);
		if (i == 0)
			std::cerr << "-- Font: " << (fs::path(ASSET_DIR) / "Roboto" / "Roboto-VariableFont_wdth,wght.ttf").string() << " exists\n";
	}
	for (int i = 0; i < NUM_FONT_SIZE; i++) {
		ImFont* imguiFont = ioPtr->Fonts->AddFontFromFileTTF((fs::path(ASSET_DIR) / "Roboto_Mono" / "RobotoMono-VariableFont_wght.ttf").string().c_str(),
			NORMAL_UI_FONT_SIZE * (1 + i * 0.25f));
		assert(imguiFont != nullptr);
		imPseudocodeFonts.push_back(imguiFont);
		if (i == 0)
			std::cerr << "-- Font: " << (fs::path(ASSET_DIR) / "Roboto_Mono" / "RobotoMono-VariableFont_wght.ttf").string() << " exists\n";
	}
	// IMPORTANT for imgui-sfml: Re-create the font texture
	ImGui::SFML::UpdateFontTexture();

	// -- Set default visualization themes (in SFML) for vis engines
	refreshVisThemes();
	// -- Set default pseudocode font in ImGui for vis engines
	refreshImFontForVisEngine();

	// -- Load settings first
	loadSettings();

	// -- Modify the window background color (RGB alpha)
	// style.Colors[ImGuiCol_WindowBg] = ImVec4(0.6f, 0.4f, 0.6f, 0.9f);
	// style.Colors[ImGuiCol_WindowBg] = ImVec4(173.f/255, 216.f/255, 230.f/255, 0.6f);
	// style.Colors[ImGuiCol_PopupBg] = ImVec4(173.f/255, 216.f/255, 230.f/255, 1.f);
	// style.Colors[ImGuiCol_Text] = ImVec4(0.f, 0.f, 0.f, 1.f);
	// Can adjust padding, rounding, borders,...
	// io.FontGlobalScale = 2.0f;

	// -- Initialize sfDrawables map to draw later
	sfDrawables[ProgramState::MAIN_MENU] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::SETTINGS_MENU] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::CHOOSE_DS_MENU] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::VIS_SLL_SCREEN] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::VIS_HASH_SCREEN] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::VIS_AVL_SCREEN] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::VIS_TRIE_SCREEN] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::VIS_MST_PRIM_SCREEN] = std::make_unique<sfLayout>(&window);
	sfDrawables[ProgramState::VIS_DIJKSTRA_SCREEN] = std::make_unique<sfLayout>(&window);

	// -- Initialize sfDrawablesDefaultView map to draw later
	sfDrawablesDefaultView[ProgramState::MAIN_MENU] = std::make_unique<sfLayout>(&window);
	sfDrawablesDefaultView[ProgramState::SETTINGS_MENU] = std::make_unique<sfLayout>(&window);
	sfDrawablesDefaultView[ProgramState::CHOOSE_DS_MENU] = std::make_unique<sfLayout>(&window);
	sfDrawablesDefaultView[ProgramState::VIS_SLL_SCREEN] = std::make_unique<sfLayout>(&window);
	sfDrawablesDefaultView[ProgramState::VIS_HASH_SCREEN] = std::make_unique<sfLayout>(&window);
	sfDrawablesDefaultView[ProgramState::VIS_AVL_SCREEN] = std::make_unique<sfLayout>(&window);
	sfDrawablesDefaultView[ProgramState::VIS_TRIE_SCREEN] = std::make_unique<sfLayout>(&window);
	sfDrawablesDefaultView[ProgramState::VIS_MST_PRIM_SCREEN] = std::make_unique<sfLayout>(&window);
	sfDrawablesDefaultView[ProgramState::VIS_DIJKSTRA_SCREEN] = std::make_unique<sfLayout>(&window);

	// -- Initialize custom data initialization buffers
	customDataSLLBuf[0] = '\0';
	customDataHashBuf[0] = '\0';
	customDataAVLBuf[0] = '\0';
	customDataTrieBuf[0] = '\0';
	customDataMSTPrimBuf[0] = '\0';
	customDataDijkstraBuf[0] = '\0';

	// -- Create and Open data .txt files
	createAndOpen(SLL_DATA_FILEPATH); // SLL
	createAndOpen(HASH_DATA_FILEPATH); // HASH TABLE
	createAndOpen(AVL_DATA_FILEPATH); // AVL
	createAndOpen(TRIE_DATA_FILEPATH); // TRIE
	createAndOpen(GRAPH_DATA_FILEPATH); // GRAPH


	// Resize the sf::View
	resizeView();
}

Program::~Program() {
	// Delete everything on the heap
	delete[] buf;
	// delete[] customDataSLLBuf;
	// delete[] customDataHashBuf;
	// delete[] customDataAVLBuf;
	// delete[] customDataTrieBuf;
	// delete[] customDataMSTPrimBuf;
	// delete[] customDataDijkstraBuf;
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
	if (!init_imgui_successful) {
		std::cout << "Dear ImGui initialization unsuccessful!!!" << std::endl;
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
	case ProgramState::VIS_HASH_SCREEN:
		initVisHashScreen();
		break;
	case ProgramState::VIS_AVL_SCREEN:
		initVisAVLScreen();
		break;
	case ProgramState::VIS_TRIE_SCREEN:
		initVisTrieScreen();
		break;
	case ProgramState::VIS_MST_PRIM_SCREEN:
		initVisMSTPrimScreen();
		break;
	case ProgramState::VIS_DIJKSTRA_SCREEN:
		initVisDijkstraScreen();
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
				// window.setView(window.getDefaultView());
				
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
				// Start dragging graph vertex
				else if (mb->button == sf::Mouse::Button::Right &&
					!ImGui::GetIO().WantCaptureMouse) {
					if (programState == ProgramState::VIS_MST_PRIM_SCREEN) {
						draggingGraphVertex = true;
						sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

						visEngine_MSTPrim.getDraggedVertexID(mousePos, view.getCenter(), calculateZoomFactor());
					} else if (programState == ProgramState::VIS_DIJKSTRA_SCREEN) {
						draggingGraphVertex = true;
						sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

						visEngine_Dijkstra.getDraggedVertexID(mousePos, view.getCenter(), calculateZoomFactor());
					}
				}
			}

			// Stop dragging
			if (const auto* mb = event->getIf<sf::Event::MouseButtonReleased>()) {
				if (mb->button == sf::Mouse::Button::Left)
					draggingCanvas = false;
				// Stop dragging graph vertex
				else if (mb->button == sf::Mouse::Button::Right) {
					if (programState == ProgramState::VIS_MST_PRIM_SCREEN) {
						draggingGraphVertex = false;
						visEngine_MSTPrim.resetDraggedVertexID();
					} else if (programState == ProgramState::VIS_DIJKSTRA_SCREEN) {
						draggingGraphVertex = false;
						visEngine_Dijkstra.resetDraggedVertexID();
					}
				}
			}

			// Zoom when mouse is scrolling
			if (const auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>()) {
				if (scroll->wheel == sf::Mouse::Wheel::Vertical) {
					float zoomFactor = (scroll->delta > 0) ? 1/SCALING_FACTOR : SCALING_FACTOR;
					view.zoom(zoomFactor);
					window.setView(view);
				}
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
		// If mouse is dragging graph vertex
		if (draggingGraphVertex) {
			sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
			if (programState == ProgramState::VIS_MST_PRIM_SCREEN) {
				visEngine_MSTPrim.dragVertexByMouse(mousePos, view.getCenter(), calculateZoomFactor());
			} else if (programState == ProgramState::VIS_DIJKSTRA_SCREEN) {
				visEngine_Dijkstra.dragVertexByMouse(mousePos, view.getCenter(), calculateZoomFactor());
			}
			// std::cout << "Dragging node" << std::endl; // DEBUG
		}


		ImGui::SFML::Update(window, deltaClock.restart());

		// Refresh ImFonts for vis engines
		refreshImFontForVisEngine();

		ImGui::PushFont(imFonts[imFontSizeIndex]);

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
		case ProgramState::VIS_HASH_SCREEN:
			displayVisHashScreenGUI();
			break;
		case ProgramState::VIS_AVL_SCREEN:
			displayVisAVLScreenGUI();
			break;
		case ProgramState::VIS_TRIE_SCREEN:
			displayVisTrieScreenGUI();
			break;
		case ProgramState::VIS_MST_PRIM_SCREEN:
			displayVisMSTPrimScreenGUI();
			break;
		case ProgramState::VIS_DIJKSTRA_SCREEN:
			displayVisDijkstraScreenGUI();
			break;
		default:
			break;
		};


		// Refresh vis theme
		refreshVisThemes();


		// window.clear();
		// window.clear(sf::Color(20, 100, 20));
		window.clear(backgroundColor);

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
		case ProgramState::VIS_HASH_SCREEN:
			displayVisHashScreenSFML();
			break;
		case ProgramState::VIS_AVL_SCREEN:
			displayVisAVLScreenSFML();
			break;
		case ProgramState::VIS_TRIE_SCREEN:
			displayVisTrieScreenSFML();
			break;
		case ProgramState::VIS_MST_PRIM_SCREEN:
			displayVisMSTPrimScreenSFML();
			break;
		case ProgramState::VIS_DIJKSTRA_SCREEN:
			displayVisDijkstraScreenSFML();
			break;
		default:
			break;
		};


		ImGui::PopFont();

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
	case ProgramState::VIS_HASH_SCREEN:
		finishVisHashScreen();
		break;
	case ProgramState::VIS_AVL_SCREEN:
		finishVisAVLScreen();
		break;
	case ProgramState::VIS_TRIE_SCREEN:
		finishVisTrieScreen();
		break;
	case ProgramState::VIS_MST_PRIM_SCREEN:
		finishVisMSTPrimScreen();
		break;
	case ProgramState::VIS_DIJKSTRA_SCREEN:
		finishVisDijkstraScreen();
		break;
	default:
		break;
	};
}




// Display test screen (FOR TESTING ONLY)
// void displayTestScreen();






// Returns the view's zoom factor (zoom in < 1, zoom out > 1)
float Program::calculateZoomFactor() {
	sf::Vector2f currentSize = view.getSize();
	return currentSize.x / window.getSize().x;
}





// Set vis theme for engines
void Program::setLightVisTheme() {
	backgroundColor = sf::Color::White;
	titleColor = sf::Color::Black;
	// --- MAKE SURE ALL DATA STRUCTURES ARE SET ---
	visEngine_SLL.setVisTheme(VIS_THEME::LIGHT);
	visEngine_Hash.setVisTheme(VIS_THEME::LIGHT);
	visEngine_AVL.setVisTheme(VIS_THEME::LIGHT);
	visEngine_Trie.setVisTheme(VIS_THEME::LIGHT);
	visEngine_MSTPrim.setVisTheme(VIS_THEME::LIGHT);
	visEngine_Dijkstra.setVisTheme(VIS_THEME::LIGHT);
}

void Program::setDarkVisTheme() {
	backgroundColor = sf::Color(0x101010FF);
	titleColor = sf::Color::White;
	// --- MAKE SURE ALL DATA STRUCTURES ARE SET ---
	visEngine_SLL.setVisTheme(VIS_THEME::DARK);
	visEngine_Hash.setVisTheme(VIS_THEME::DARK);
	visEngine_AVL.setVisTheme(VIS_THEME::DARK);
	visEngine_Trie.setVisTheme(VIS_THEME::DARK);
	visEngine_MSTPrim.setVisTheme(VIS_THEME::DARK);
	visEngine_Dijkstra.setVisTheme(VIS_THEME::DARK);
}

void Program::refreshVisThemes() {
	switch (currentVisTheme) {
	case VIS_THEME::LIGHT:
		setLightVisTheme();
		break;
	case VIS_THEME::DARK:
		setDarkVisTheme();
		break;
	};
}

void Program::refreshImFontForVisEngine() {
	// --- MAKE SURE ALL DATA STRUCTURES ARE SET ---
	visEngine_SLL.pseudocodeFont = imPseudocodeFonts[imFontSizeIndex];
	visEngine_Hash.pseudocodeFont = imPseudocodeFonts[imFontSizeIndex];
	visEngine_AVL.pseudocodeFont = imPseudocodeFonts[imFontSizeIndex];
	visEngine_Trie.pseudocodeFont = imPseudocodeFonts[imFontSizeIndex];
	visEngine_MSTPrim.pseudocodeFont = imPseudocodeFonts[imFontSizeIndex];
	visEngine_Dijkstra.pseudocodeFont = imPseudocodeFonts[imFontSizeIndex];
}





// Load settings into Program
void Program::loadSettings() {
	Settings read = SettingsReader::readSettings(); // If fails, return default settings
	current_resolution_item = read.resolutionItemIndex;
	current_appTheme_item = read.appThemeItemIndex; // Default is Dark mode
	current_visTheme_item = read.visThemeItemIndex; // Default is Light mode
	imFontSizeIndex = read.imFontSizeIndex; // (SETTINGS) for ImGui fonts

	// Clamping values
	current_resolution_item = std::clamp(current_resolution_item, 0, static_cast<int>(resolutionVectors.size()) - 1);
	current_appTheme_item = std::clamp(current_appTheme_item, 0, static_cast<int>(appThemeVectors.size()) - 1);
	current_visTheme_item = std::clamp(current_visTheme_item, 0, static_cast<int>(visThemeVectors.size()) - 1);
	imFontSizeIndex = std::clamp(imFontSizeIndex, 0, static_cast<int>(imFonts.size()) - 1);


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
	currentVisTheme = visThemeVectors[current_visTheme_item];
	refreshVisThemes();

	refreshImFontForVisEngine();

	// Set ImGui buffer
	imFontSizeIndexSlider = imFontSizeIndex;
}

// Save settings in Program into .cfg file
void Program::saveSettings() {
	Settings settingsInProgram(current_resolution_item, current_appTheme_item, current_visTheme_item, imFontSizeIndex);
	SettingsReader::saveSettings(settingsInProgram);
}
