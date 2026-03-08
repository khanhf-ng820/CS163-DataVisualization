#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>

#include "sfLayout/sfLayout.h"
#include "utils/utils-readData.h"
#include "utils/utils.h"
#include "HashTable/HashAnimStep.h"





enum class HashVisMode {
	NONE,
	SEARCH,
	UPDATE,
	DELETE,
	INSERT
};


class HashVisEngine {
public:
	HashVisEngine(sf::RenderWindow* window, sf::Font* font); // Empty, size 0 hash table
	HashVisEngine(int tableSize, sf::RenderWindow* window, sf::Font* font); // Empty hash table
	HashVisEngine(std::vector<int> values, sf::RenderWindow* window, sf::Font* font); // Custom hash table

	void resetParams();


	// Draw nodes: Iterate through linked list and draw nodes
	void addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, HashAnimStep eventHash);
	// INSERT MODE
	void addNodeDrawablesInsert(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, HashAnimStep eventHash);
	// DELETE MODE
	void addNodeDrawablesDelete(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, HashAnimStep eventHash);
	// Draw nodes and links, depending on eventList
	void createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList);
	void displayDrawables(std::unique_ptr<sfLayout>& sfmlLayout);


	sf::RenderWindow* windowPtr;
	sf::Font* fontPtr;

	HashVisMode visMode = HashVisMode::NONE;
	std::vector<HashAnimStep> eventList;


	// Table
	std::vector<TableSlot> table;
	int tableSize = 0; // Size of hash table


	// For Visualization
	int curIndex = -1; // Index of slot currently animating

	int searchSlotIdx = -1; // Index of slot currently animating

	int insertKey = -1; // Key to assign/insert to the slot
	// int insertVal = -1; // Value to assign/insert to the slot

	int deleteKey = -1; // Key to delete from the slot
	// int deleteVal = -1; // Value to delete from the slot

	int highlightSlotIdx = -1; // Index of highlighted slot
	int foundSlotIdx = -1; // Index of found slot when searching/updating


	// For Input
	int keyToSearch = 0;      // Searching
	int keyToSearchInput = 0;

	// For Animating steps
	int animStepIndex = 0;
	int oldAnimStepIndex = 0;
	float time = 0;
	float dt = 0.005;
	float targetTime = 0; // ONLY USE WHEN PAUSED

	bool animPaused = false;
	bool animInProgress = false;
	constexpr static float dt_per_sec = 0.25f; // FOR TESTING ONLY

	void increaseTime();
	void decreaseTime();

	void prevStep();
	void nextStep();
	void skipToFinalState();



	std::vector<HashAnimStep> getEventsSearch(int key);
	// void insert(int key, int val);
	// std::vector<HashAnimStep> getEventsInsert(int key, int val);
	// void update(int key, int newVal);
	// std::vector<HashAnimStep> getEventsUpdate(int key, int newVal);
	// void delete(int key);
	// std::vector<HashAnimStep> getEventsDelete(int key);



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

	static constexpr sf::Color    normalSlotColor         = sf::Color::Black;
	static constexpr sf::Color    normalSlotValueColor    = sf::Color::Black;
	static constexpr sf::Color    normalSlotKeyColor      = sf::Color::Blue;
	static constexpr sf::Color    normalSlotIndexColor    = sf::Color::Blue;
	static constexpr sf::Color    highlightSlotColor      = sf::Color::Red;
	static constexpr sf::Color    highlightFoundSlotColor = sf::Color::Green;
	static constexpr ImVec4       highlightCodeColor      = {0.4f, 1.f, 0.f, 1.f};

private:
	int hashFunc(int key);

	// Create AND display ImGui window to highlight source code (pseudocode)
	void drawHighlightCodeWindow(HashAnimStep eventHash);

	sf::Vector2f lerp(sf::Vector2f v1, sf::Vector2f v2, float k) const;
	// void drawSlot(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, int slotIndex, int key, int value, sf::Vector2f pos) const;
	// Draw a slot
	void drawSlot(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, int slotIndex, int key, sf::Vector2f pos) const;
	// Draw highlight border around a slot
	void drawHighlightBorder(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, int slotIndex, int key, sf::Vector2f pos, bool isFoundSlot) const;
};
