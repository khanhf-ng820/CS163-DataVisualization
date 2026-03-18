#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Themes/Themes.h"
#include "utils/readData.hpp"
#include "sfLayout/sfLayout.h"
#include "SLL/SLLVisEngine.h"
#include "HashTable/HashVisEngine.h"

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

	// Display Hash Table visualization screen
	void initVisHashScreen();
	void displayVisHashScreenSFML();
	void displayVisHashScreenGUI();
	void finishVisHashScreen();

	// Display AVL visualization screen
	void initVisAVLScreen() {};
	void displayVisAVLScreenSFML() {};
	void displayVisAVLScreenGUI() {};
	void finishVisAVLScreen() {};

	// Display Trie visualization screen
	void initVisTrieScreen() {};
	void displayVisTrieScreenSFML() {};
	void displayVisTrieScreenGUI() {};
	void finishVisTrieScreen() {};

	// Display MST visualization screen
	void initVisMSTScreen() {};
	void displayVisMSTScreenSFML() {};
	void displayVisMSTScreenGUI() {};
	void finishVisMSTScreen() {};

	// Display Dijkstra visualization screen
	void initVisDijkstraScreen() {};
	void displayVisDijkstraScreenSFML() {};
	void displayVisDijkstraScreenGUI() {};
	void finishVisDijkstraScreen() {};



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
	const float SCALING_FACTOR = 1.1; // When zooming

	// SFML global vars
	sf::RenderWindow window;
	sf::Clock deltaClock;
	sf::View view; // The app's view
	sf::ContextSettings settings;
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

	SLLVisEngine visEngine_SLL; // Engine for visualizing SLL
	HashVisEngine visEngine_Hash; // Engine for visualizing Hash Table



	constexpr static size_t CUSTOM_DATA_BUF_SIZE = 512;

	///// Input buffers for ImGui /////
	char* buf = new char[25];
	float f = 0.36;

	/// Input buffers for settings
	const char* resolutionOptions[6]                  = { "800×600", "1920×1080", "1366×768", "1440×900", "1280×720", "1024×768" }; // Removed 2560×1440
	const std::vector<sf::Vector2u> resolutionVectors = { {800,600}, {1920,1080}, {1366,768}, {1440,900}, {1280,720}, {1024,768} };
	const char* appThemeOptions[3]               = { "Light", "Dark", "Classic" };
	const std::vector<APP_THEME> appThemeVectors = { APP_THEME::LIGHT, APP_THEME::DARK, APP_THEME::CLASSIC };
	int current_resolution_item = 0;
	int current_appTheme_item = 1; // Default is Dark mode

	unsigned int initHashTableSizeBuf = 10;
	unsigned int initHashTableModuloBuf = 10;
	constexpr static unsigned int MAX_INIT_HASHTABLE_SIZE = 128;
	constexpr static unsigned int MAX_INIT_HASHTABLE_MODULO = 128;
	const std::string SIZE_INPUT_WARNING_STRING   = "Table Size (min. 2, max. " + std::to_string(MAX_INIT_HASHTABLE_SIZE) + ")";
	const std::string MODULO_INPUT_WARNING_STRING = "Modulo M (min. 2, max. " + std::to_string(MAX_INIT_HASHTABLE_MODULO) + ")";

	char* customDataSLLbuf      = new char[CUSTOM_DATA_BUF_SIZE];
	char* customDataHashbuf     = new char[CUSTOM_DATA_BUF_SIZE];
	char* customDataAVLbuf      = new char[CUSTOM_DATA_BUF_SIZE];
	char* customDataTriebuf     = new char[CUSTOM_DATA_BUF_SIZE];
	char* customDataMSTbuf      = new char[CUSTOM_DATA_BUF_SIZE];
	char* customDataDijkstrabuf = new char[CUSTOM_DATA_BUF_SIZE];



	inline const static fs::path SLL_DATA_FILEPATH = fs::path(DATA_DIR) / "SLL.txt";
	inline const static fs::path HASH_DATA_FILEPATH = fs::path(DATA_DIR) / "HashTable.txt";
	inline const static fs::path AVL_DATA_FILEPATH = fs::path(DATA_DIR) / "AVL.txt";
	inline const static fs::path TRIE_DATA_FILEPATH = fs::path(DATA_DIR) / "Trie.txt";
	inline const static fs::path GRAPH_DATA_FILEPATH = fs::path(DATA_DIR) / "Graph.txt";

	std::ifstream SLL_dataFile, hashTable_dataFile, AVL_dataFile, trie_dataFile, graph_dataFile;



	// Open data structure .txt files
	void createAndOpen(const fs::path dataFilePath);

	// Initialize data structures (if returns false, don't go to visualization menu screen)
	bool initSLL(const int dataInitOption);
	bool initHashTable(const int dataInitOption);
	bool initAVL(const int dataInitOption);
	bool initTrie(const int dataInitOption);
	bool initGraph(const int dataInitOption);
};
