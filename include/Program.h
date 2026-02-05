#pragma once
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <string>



enum class ProgramState {
	MAIN_MENU,
	CHOOSING_DS_MENU
};



class Program {
public:
	Program();
	// Main loop of program
	void mainLoop();

private:
	// Constants
	const std::string PROGRAM_WINDOW_NAME = "Data Structure Visualizer";
	// Logical resolution
	const float GAME_WIDTH = 1920.0f;
	const float GAME_HEIGHT = 1080.0f;
	const unsigned int FRAMERATE_LIMIT = 60;

	sf::RenderWindow window;
	sf::Clock deltaClock;
	bool init_successful = true;

	ProgramState pgState;
};
