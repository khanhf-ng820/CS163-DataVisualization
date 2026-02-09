#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;



enum class ProgramState {
	MAIN_MENU,
	SETTINGS_MENU,
	CHOOSING_DS_MENU
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

	// Display test screen (FOR TESTING ONLY)
	void initTestScreen();
	void displayTestScreenSFML();
	void displayTestScreenGUI();
	void finishTestScreen();

	// Display main menu screen
	void initMainMenuScreen();
	void displayMainMenuScreenSFML();
	void displayMainMenuScreenGUI();
	void finishMainMenuScreen();



private:
	// Constants
	const std::string PROGRAM_WINDOW_NAME = "Data Structure Visualizer";
	// Logical resolution
	const float NORMAL_WIDTH = 1920.0f;
	const float NORMAL_HEIGHT = 1080.0f;
	const unsigned int FRAMERATE_LIMIT = 60;

	sf::RenderWindow window;
	sf::Clock deltaClock;
	sf::View view; // The app's view
	sf::Font textFont;
	bool init_successful = true;

	bool draggingCanvas = false; // If mouse is dragging canvas
	bool allowDragCanvas = false; // Allow dragging canvas (remember to set false)
	sf::Vector2f lastWorldPos; // Position of last dragged view


	ProgramState programState = ProgramState::MAIN_MENU;



	char* buf = new char[25];
	float f = 0.36;
	// sf::CircleShape shape;
	// sf::RectangleShape rectangle;
	// sf::RectangleShape border;
	// sf::CircleShape splitCircle;
	// sf::RectangleShape cornerBox;
};
