#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

extern "C" {
	#include "tinyfiledialogs/tinyfiledialogs.h"
}

#include "Themes/Themes.h"
#include "utils/readSettings.h"
#include "utils/readData.hpp"
#include "sfLayout/sfLayout.h"
#include "SLL/SLLVisEngine.h"
#include "HashTable/HashVisEngine.h"
#include "AVL/AVLVisEngine.h"
#include "Trie/TrieVisEngine.h"
#include "Graph/MSTPrim/PrimVisEngine.h"
#include "Graph/Dijkstra/DijkstraVisEngine.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <filesystem>
#include <random>
#include <chrono>
#include <climits>

namespace fs = std::filesystem;



enum class ProgramState {
	MAIN_MENU,
	SETTINGS_MENU,
	CHOOSE_DS_MENU,
	VIS_SLL_SCREEN,
	VIS_HASH_SCREEN,
	VIS_AVL_SCREEN,
	VIS_TRIE_SCREEN,
	VIS_MST_PRIM_SCREEN,
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


private:
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
	void initVisAVLScreen();
	void displayVisAVLScreenSFML();
	void displayVisAVLScreenGUI();
	void finishVisAVLScreen();

	// Display Trie visualization screen
	void initVisTrieScreen();
	void displayVisTrieScreenSFML();
	void displayVisTrieScreenGUI();
	void finishVisTrieScreen();

	// Display MST Prim visualization screen
	void initVisMSTPrimScreen();
	void displayVisMSTPrimScreenSFML();
	void displayVisMSTPrimScreenGUI();
	void finishVisMSTPrimScreen();

	// Display Dijkstra visualization screen
	void initVisDijkstraScreen();
	void displayVisDijkstraScreenSFML();
	void displayVisDijkstraScreenGUI();
	void finishVisDijkstraScreen();





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
	const float NORMAL_UI_FONT_SIZE = 16.f; // Before scaling
	const unsigned int NUM_FONT_SIZE = 5; // Number of font sizes

	// SFML global vars
	sf::RenderWindow window;
	sf::Clock deltaClock;
	sf::View view; // The app's view
	sf::ContextSettings settings;
	sf::Font textFont;

	// ImGui global vars
	ImGuiIO* ioPtr;
	ImGuiStyle* stylePtr;

	// ImGui fonts
	std::vector<ImFont*> imFonts; // size of NUM_FONT_SIZE
	std::vector<ImFont*> imPseudocodeFonts; // size of NUM_FONT_SIZE
	void refreshImFontForVisEngine();

	// Random number generator
	std::mt19937 rng;

	// Function to calculate zoom factor of view
	// Returns the view's zoom factor (zoom in < 1, zoom out > 1)
	float calculateZoomFactor();

	bool init_imgui_successful = true;
	bool allowDragCanvas = false; // Allow dragging canvas (remember to set false)
	bool draggingCanvas = false; // If mouse is dragging canvas
	sf::Vector2f lastWorldPos; // Position of last dragged view
	
	bool draggingGraphVertex = false;


	// Initializing data structure from files
	bool invalidDataFromFile = false; // To print error messages when invalid data


	ProgramState programState = ProgramState::MAIN_MENU;

	// Set vis theme for engines (SETTINGS)
	static inline VIS_THEME currentVisTheme = VIS_THEME::LIGHT; // Default is Light mode
	void setLightVisTheme();
	void setDarkVisTheme();
	void refreshVisThemes();
	// Colors for SFML 
	static inline sf::Color backgroundColor = sf::Color::White;
	static inline sf::Color titleColor = sf::Color::Black;

	// SFML shapes to draw
	std::map<ProgramState, std::unique_ptr<sfLayout>> sfDrawables;
	std::map<ProgramState, std::unique_ptr<sfLayout>> sfDrawablesDefaultView;

	// Visualization engines
	SLLVisEngine visEngine_SLL; // Engine for visualizing SLL
	HashVisEngine visEngine_Hash; // Engine for visualizing Hash Table
	AVLVisEngine visEngine_AVL; // Engine for visualizing AVL Tree
	TrieVisEngine visEngine_Trie; // Engine for visualizing Trie
	PrimVisEngine visEngine_MSTPrim; // Engine for visualizing Prim's algorithm for MST
	DijkstraVisEngine visEngine_Dijkstra; // Engine for visualizing Dijkstra's algorithm



	constexpr static size_t CUSTOM_DATA_BUF_SIZE = 512;

	///// Input buffers for ImGui /////
	char* buf = new char[25];
	float f = 0.36;
	int imFontSizeIndexSlider = 0;



	///// Input buffers for SETTINGS /////
	const char* resolutionOptions[6]                  = { "800x600", "1920x1080", "1366x768", "1440x900", "1280x720", "1024x768" }; // Removed 2560x1440
	const std::vector<sf::Vector2u> resolutionVectors = { {800,600}, {1920,1080}, {1366,768}, {1440,900}, {1280,720}, {1024,768} };
	const char* appThemeOptions[3]               = { "Light", "Dark", "Purple" };
	const std::vector<APP_THEME> appThemeVectors = { APP_THEME::LIGHT, APP_THEME::DARK, APP_THEME::PURPLE };
	const char* visThemeOptions[2]               = { "Light", "Dark" };
	const std::vector<VIS_THEME> visThemeVectors = { VIS_THEME::LIGHT, VIS_THEME::DARK };
	///// SETTINGS variables
	int current_resolution_item = 0;
	int current_appTheme_item = 1; // Default is Dark mode
	int current_visTheme_item = 0; // Default is Light mode
	int imFontSizeIndex = 0; // (SETTINGS) for ImGui fonts

	void loadSettings(); // Load settings into Program
	void saveSettings(); // Save settings in Program into .cfg file



	///// Input buffers for data initialization /////
	unsigned int initHashTableSizeBuf   = 11;
	unsigned int initHashTableModuloBuf = 11;
	constexpr static unsigned int MAX_INIT_HASHTABLE_SIZE   = 128;
	constexpr static unsigned int MAX_INIT_HASHTABLE_MODULO = 128;
	const std::string SIZE_INPUT_WARNING_STRING   = "Table Size (min. 2, max. " + std::to_string(MAX_INIT_HASHTABLE_SIZE) + ")";
	const std::string MODULO_INPUT_WARNING_STRING = "Modulo M (min. 2, max. " + std::to_string(MAX_INIT_HASHTABLE_MODULO) + ")";

	char customDataSLLBuf[CUSTOM_DATA_BUF_SIZE];
	char customDataHashBuf[CUSTOM_DATA_BUF_SIZE];
	char customDataAVLBuf[CUSTOM_DATA_BUF_SIZE];
	char customDataTrieBuf[CUSTOM_DATA_BUF_SIZE];
	char customDataMSTPrimBuf[CUSTOM_DATA_BUF_SIZE];
	char customDataDijkstraBuf[CUSTOM_DATA_BUF_SIZE];



	///// File paths for data input /////
	std::string selectedFile;
	std::string fileContent;

	static inline fs::path SLL_DATA_FILEPATH = fs::path(DATA_DIR) / "SLL.txt";
	static inline fs::path HASH_DATA_FILEPATH = fs::path(DATA_DIR) / "HashTable.txt";
	static inline fs::path AVL_DATA_FILEPATH = fs::path(DATA_DIR) / "AVL.txt";
	static inline fs::path TRIE_DATA_FILEPATH = fs::path(DATA_DIR) / "Trie.txt";
	static inline fs::path GRAPH_DATA_FILEPATH = fs::path(DATA_DIR) / "Graph.txt";

	std::ifstream SLL_dataFile, hashTable_dataFile, AVL_dataFile, trie_dataFile, graph_dataFile;



	// Open data structure .txt files
	void createAndOpen(const fs::path dataFilePath);

	// Initialize data structures (if returns false, don't go to visualization menu screen)
	bool initSLL(const int dataInitOption);
	bool initHashTable(const int dataInitOption);
	bool initAVL(const int dataInitOption);
	bool initTrie(const int dataInitOption);
	bool initGraph(const int dataInitOption, const GraphReader::GraphInitMethod graphInitMethod,
		const char customDataBuf[], const fs::path& DATA_FILEPATH, const std::ifstream& dataFile);
};
