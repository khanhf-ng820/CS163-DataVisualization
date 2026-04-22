#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <chrono>
#include <random>

#include "Themes/Themes.h"
#include "sfLayout/sfLayout.h"
#include "utils/readData.hpp"
#include "utils/utils.h"
#include "AnimPlayer/AnimPlayer.h"
#include "HashTable/HashAnimStep.h"
#include "HashTable/HashSourceCode.h"





enum class HashVisMode {
	NONE,
	SEARCH,
	INSERT,
	REMOVE,
	UPDATE
};


// REMEMBER:
// Drawing SFML: The center of the window is now (0, 0) coordinates
// Drawing GUI: The top-left of the window is (0, 0) coordinates
class HashVisEngine : public AnimPlayer {
public:
	HashVisEngine(sf::RenderWindow* window, sf::Font* font); // Empty, size 0 hash table
	HashVisEngine(int tableSize, int tableModulo, sf::RenderWindow* window, sf::Font* font); // Empty hash table
	HashVisEngine(int tableSize, int tableModulo, std::mt19937& rng, sf::RenderWindow* window, sf::Font* font); // Randomized hash table
	HashVisEngine(std::vector<TableSlotInput>& values, int tableModulo, sf::RenderWindow* window, sf::Font* font); // Custom hash table

	// Reset all properties to get ready for visualize new action
	void resetParams();

	// Set vis theme
	void setVisTheme(VIS_THEME visTheme);

	// Initialize table data
	void initHashTableData(); // Empty HashTable
	void initHashTableData(std::mt19937& rng); // Randomized HashTable
	void initHashTableData(std::vector<int> initData); // Specific data HashTable


	// Draw nodes: Iterate through linked list and draw nodes
	void addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, HashAnimStep eventHash);
	// INSERT MODE
	void addNodeDrawablesInsert(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, HashAnimStep eventHash);
	// REMOVE MODE
	void addNodeDrawablesRemove(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, HashAnimStep eventHash);
	// UPDATE MODE
	void addNodeDrawablesUpdate(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, HashAnimStep eventHash);
	// Draw nodes and links, depending on eventList
	void createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::vector<std::unique_ptr<sf::Drawable>>& drawableListDefaultView);
	void displayDrawables(std::unique_ptr<sfLayout>& sfmlLayout);


	sf::RenderWindow* windowPtr;
	sf::Font* fontPtr;
	sf::Vector2f normalWindowSize = {800.f, 600.f};

	HashVisMode visMode = HashVisMode::NONE;
	std::vector<HashAnimStep> eventList;


	// ///// Table
	std::vector<TableSlot> table;
	int tableSize = 0; // Size of hash table
	int tableModulo = 11; // Modulo for hash function


	// ///// Parameters for Visualization
	int curIndex = -1; // Index of slot currently animating

	// For SEARCH MODE
	int searchSlotIdx = -1; // Index of slot currently animating

	int oldKeySlot = -1; // Old key of slot before changes
	bool isOldSlotDeleted = false; // Did old slot before changes have deletion marker?

	// For INSERT MODE
	int insertSlotIdx = -1; // Index of inserted slot
	int insertKey = -1; // Key to assign/insert to the slot
	// int insertVal = -1; // Value to assign/insert to the slot

	// For REMOVE MODE
	int removeSlotIdx = -1; // Index of slot to remove
	int removeStoppingSlotIdx = -1; // Index of slot to stop at after failing to remove
	// int removeVal = -1; // Value to remove from the slot

	// For UPDATE MODE
	TableSlot oldSlotRemoval; // Old slot before removal
	TableSlot oldSlotInsert; // Old slot before insertion

	int highlightSlotIdx = -1; // Index of highlighted slot
	int foundSlotIdx = -1; // Index of found slot when searching/updating


	// ///// Parameters for Input in ImGui
	int keyToSearch = -1;      // Searching
	int keyToSearchInput = 0;

	int keyToInsert = -1;      // Inserting
	int keyToInsertInput = 0;

	int keyToRemove = -1;      // Removing
	int keyToRemoveInput = 0;

	int oldKeyToUpdate = -1;      // Updating
	int oldKeyToUpdateInput = 0;
	int newKeyToUpdate = -1;
	int newKeyToUpdateInput = 0;


	// Methods and properties for animating steps
	// (Already included in AnimPlayer class)


	///// ALGORITHMS
	std::vector<HashAnimStep> getEventsSearch(int key);
	void insert(int key);
	std::vector<HashAnimStep> getEventsInsert(int key);
	void remove(int key);
	std::vector<HashAnimStep> getEventsRemove(int key);
	void update(int key, int newKey);
	std::vector<HashAnimStep> getEventsUpdate(int key, int newKey);


	// Helper methods
	bool isUpdatable(int oldKey, int newKey);


	static constexpr int RANDOM_DISTRIB_KEY_MIN = -100;
	static constexpr int RANDOM_DISTRIB_KEY_MAX = 100;


private:
	static constexpr sf::Vector2f originPosDisplacement = {75, 50};
	sf::Vector2f originPos;
	static constexpr sf::Vector2f descriptionTextPos = {50, 10};
	static constexpr sf::Vector2f slotValRectSize = {60, 20};
	static constexpr sf::Vector2f slotKeyRectSize = {60, 20};
	static constexpr float        slotIdxTextSpacing = 20;
	static constexpr float        slotLayerSpacing = 40;
	static constexpr int          valueFontSize = 10;
	static constexpr int          keyFontSize = 15;
	static constexpr int          indexFontSize = 12;
	static constexpr int          descriptionFontSize = 15;

	static inline    sf::Color    normalSlotColor         = sf::Color::Black;
	static inline    sf::Color    normalSlotValueColor    = sf::Color::Black;
	static inline    sf::Color    normalSlotKeyColor      = sf::Color::Blue;
	static inline    sf::Color    normalSlotIndexColor    = sf::Color::Blue;
	static inline    sf::Color    highlightSlotColor      = sf::Color::Red;
	static inline    sf::Color    highlightFoundSlotColor = sf::Color::Green;
	static constexpr sf::Color    highlightCodeColor      = sf::Color(0x3CB371FF);	// {0.4f, 1.f, 0.f, 1.f};


	int hashFunc(int key);

	//// Helper methods
	bool containsKey(int key);
	bool isFull();

	void refreshOriginPos();
	// Create AND display ImGui window to highlight source code (pseudocode)
	void drawPseudocodeWindow(HashAnimStep eventHash);

	std::string hashDescriptionString(int key);
	sf::Vector2f lerp(sf::Vector2f v1, sf::Vector2f v2, float k) const;
	// void drawSlot(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, int slotIndex, int key, int value, sf::Vector2f pos) const;
	// Draw a slot
	void drawSlot(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, int slotIndex, int key, bool empty, bool deleted, sf::Vector2f topLeftPos) const;
	void drawSlot(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, TableSlot& slot, sf::Vector2f topLeftPos) const;
	// Draw highlight border around a slot
	void drawHighlightBorder(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, int slotIndex, int key, sf::Vector2f pos, bool isFoundSlot) const;




	// Predefined colors for vis themes
	static constexpr sf::Color lightNormalSlotColor         = sf::Color::Black;
	static constexpr sf::Color lightNormalSlotValueColor    = sf::Color::Black;
	static constexpr sf::Color lightNormalSlotKeyColor      = sf::Color::Blue;
	static constexpr sf::Color lightNormalSlotIndexColor    = sf::Color::Blue;
	static constexpr sf::Color lightHighlightSlotColor      = sf::Color::Red;
	static constexpr sf::Color lightHighlightFoundSlotColor = sf::Color::Green;

	static constexpr sf::Color darkNormalSlotColor         = sf::Color::White;
	static constexpr sf::Color darkNormalSlotValueColor    = sf::Color::White;
	static constexpr sf::Color darkNormalSlotKeyColor      = sf::Color(0x90D5FFFF);
	static constexpr sf::Color darkNormalSlotIndexColor    = sf::Color(0x80EF80FF);
	static constexpr sf::Color darkHighlightSlotColor      = sf::Color::Red;
	static constexpr sf::Color darkHighlightFoundSlotColor = sf::Color::Green;

	void setLightVisTheme();
	void setDarkVisTheme();
};
