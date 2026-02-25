#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "utils-readData.h"
#include "sfLayout/sfLayout.h"
#include "SLL/SLLVisEngine.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include <random>
#include <chrono>

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
	~Program();
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

	// Random number generator
	std::mt19937 rng;

	bool init_imgui_successful = true;
	bool draggingCanvas = false; // If mouse is dragging canvas
	bool allowDragCanvas = false; // Allow dragging canvas (remember to set false)
	sf::Vector2f lastWorldPos; // Position of last dragged view


	// Initializing data structure from files
	bool invalidDataFromFile = false; // To print error messages when invalid data


	ProgramState programState = ProgramState::MAIN_MENU;

	// SFML shapes to draw
	std::map<ProgramState, std::unique_ptr<sfLayout>> sfDrawables;

	SLLVisEngine visEngine_SLL;



	constexpr static size_t CUSTOM_DATA_BUF_SIZE = 512;

	char* buf = new char[25];
	float f = 0.36;
	char* customDataSLLbuf = new char[CUSTOM_DATA_BUF_SIZE];
	char* customDataHashbuf = new char[CUSTOM_DATA_BUF_SIZE];
	char* customDataAVLbuf = new char[CUSTOM_DATA_BUF_SIZE];
	char* customDataTriebuf = new char[CUSTOM_DATA_BUF_SIZE];
	char* customDataMSTbuf = new char[CUSTOM_DATA_BUF_SIZE];
	char* customDataDijkstrabuf = new char[CUSTOM_DATA_BUF_SIZE];

	inline const static fs::path SLL_DATA_FILEPATH = fs::path(DATA_DIR) / "SLL.txt";
	inline const static fs::path HASH_DATA_FILEPATH = fs::path(DATA_DIR) / "HashTable.txt";
	inline const static fs::path AVL_DATA_FILEPATH = fs::path(DATA_DIR) / "AVL.txt";
	inline const static fs::path TRIE_DATA_FILEPATH = fs::path(DATA_DIR) / "Trie.txt";
	inline const static fs::path GRAPH_DATA_FILEPATH = fs::path(DATA_DIR) / "Graph.txt";

	std::ifstream SLL_dataFile, hashTable_dataFile, AVL_dataFile, trie_dataFile, graph_dataFile;

	// sf::CircleShape shape;
	// sf::RectangleShape rectangle;
	// sf::RectangleShape border;
	// sf::CircleShape splitCircle;
	// sf::RectangleShape cornerBox;


	// Open data structure .txt files
	void createAndOpen(const fs::path dataFilePath);

	// Initialize data structures (if returns false, don't go to visualization menu screen)
	bool initSLL(const int dataInitOption);
	bool initHashTable(const int dataInitOption);
	bool initAVL(const int dataInitOption);
	bool initTrie(const int dataInitOption);
	bool initGraph(const int dataInitOption);
};
