#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "sfLayout/sfLayout.h"
#include "SLL/SLLVisEngine.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;



enum class ProgramState {
	MAIN_MENU,
	SETTINGS_MENU,
	CHOOSE_DS_MENU,
	VIS_SLL_SCREEN,
	VIS_HASH_SCREEN,
	VIS_AVL_SCREEN,
	VIS_TRIE_SCREEN,
	VIS_MST_SCREEN,
	VIS_DIJKSTRA_SCREEN
};

struct ScaleInfo {
	float scaleFactor;
	sf::Vector2f uiOffset;
	sf::Vector2f viewSize;
};



class Program {
public:
	Program();
	// Main loop of program
	void mainLoop();
	// Function to update View based on new window size
	void resizeView();

	// Display main menu screen
	void initMainMenuScreen();
	void displayMainMenuScreenSFML();
	void displayMainMenuScreenGUI();
	void finishMainMenuScreen();

	// Display settings menu screen
	void initSettingsMenuScreen();
	void displaySettingsMenuScreenSFML();
	void displaySettingsMenuScreenGUI();
	void finishSettingsMenuScreen();

	// Display "choosing data structure to visualize" menu screen
	void initChooseDSMenuScreen();
	void displayChooseDSMenuScreenSFML();
	void displayChooseDSMenuScreenGUI();
	void finishChooseDSMenuScreen();

	// Display SLL visualization screen
	void initVisSLLScreen();
	void displayVisSLLScreenSFML();
	void displayVisSLLScreenGUI();
	void finishVisSLLScreen();



private:
	// Constants
	const std::string PROGRAM_WINDOW_NAME = "Data Structure Visualizer";
	// Logical resolution
	// const float NORMAL_WIDTH  = 1920.0f;
	// const float NORMAL_HEIGHT = 1080.0f;
	const float NORMAL_WIDTH  = 800.0f;
	const float NORMAL_HEIGHT = 600.0f;
	const unsigned int FRAMERATE_LIMIT = 60;
	const sf::Vector2u MINIMUM_WINDOW_SIZE = {800U, 600U};

	sf::RenderWindow window;
	sf::Clock deltaClock;
	sf::View view; // The app's view
	sf::Font textFont;

	// ImGui global vars
	ImGuiIO* ioPtr;
	ImGuiStyle* stylePtr;

	bool init_successful = true;
	bool draggingCanvas = false; // If mouse is dragging canvas
	bool allowDragCanvas = false; // Allow dragging canvas (remember to set false)
	sf::Vector2f lastWorldPos; // Position of last dragged view


	ProgramState programState = ProgramState::MAIN_MENU;

	// SFML shapes to draw
	std::map<ProgramState, std::unique_ptr<sfLayout>> sfDrawables;

	SLLVisEngine visEngine_SLL;



	char* buf = new char[25];
	float f = 0.36;
	// sf::CircleShape shape;
	// sf::RectangleShape rectangle;
	// sf::RectangleShape border;
	// sf::CircleShape splitCircle;
	// sf::RectangleShape cornerBox;
};
