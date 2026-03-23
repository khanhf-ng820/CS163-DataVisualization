#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <map>
#include <chrono>
#include <random>

#include "sfLayout/sfLayout.h"
#include "utils/readData.hpp"
#include "utils/utils.h"
#include "AnimPlayer/AnimPlayer.h"
#include "AVL/LogicAVLTree.h"



enum class AVLVisMode {
	NONE,
	SEARCH,
	INSERT,
	REMOVE,
	UPDATE
};



class AVLVisEngine : public AnimPlayer {
public:
	AVLVisEngine(sf::RenderWindow* window, sf::Font* font); // Empty, size 0 AVL tree

	// Reset all properties to get ready for visualize new action
	void resetParams();

	// Draw nodes: Iterate through linked list and draw nodes
	void addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, AVLAnimStep eventAVL);
	// Draw nodes and links, depending on eventList
	void createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList);
	void displayDrawables(std::unique_ptr<sfLayout>& sfmlLayout);


	sf::RenderWindow* windowPtr;
	sf::Font* fontPtr;

	AVLVisMode visMode = AVLVisMode::NONE;
	std::vector<AVLAnimStep> eventList;


	///// Parameters for Visualization
	// int curIndex = -1; // Index of slot currently animating


	///// Parameters for Input in ImGui
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
	std::vector<AVLAnimStep> getEventsSearch(int key);


	LogicAVLTree tree;
	std::map<int, VisualAVLNode> visualNodesOld1; // Visual nodes for TREE BEFORE ROTATION 1
	std::map<int, VisualAVLNode> visualNodesOld2; // Visual nodes for TREE BEFORE ROTATION 2 / AFTER ROTATION 1
	std::map<int, VisualAVLNode> visualNodesCur; // Visual nodes for CURRENT TREE



	static constexpr sf::Vector2f originPosDisplacement = {0, 50};
	sf::Vector2f originPos;
	static constexpr sf::Vector2f descriptionTextPos    = {50, 10};
	static constexpr int          descriptionFontSize   = 15;
	static constexpr float        nodeCircleRadius      = 25;
	static constexpr float        nodeOutlineThickness  = 2;
	static constexpr int          nodeKeyTextFontSize   = 15;
	static constexpr float        nodeLayerSpacing      = 100;
	static constexpr float        highlightCircleThickness = 5;
	static constexpr float        arrowHeadSideLen      = 8;
	static constexpr float        canvasLeftMargin      = 100;

	static constexpr sf::Color    normalNodeColor         = sf::Color::Black;
	static constexpr sf::Color    normalNodeKeyColor      = sf::Color::Blue;
	static constexpr sf::Color    normalNodeHeightColor   = sf::Color(6, 64, 43, 255);
	static constexpr sf::Color    highlightCircleColor    = sf::Color::Green;
	static constexpr sf::Color    highlightFoundCircleColor = sf::Color::Red;


private:
	// Helper algorithms functions
	void getEventsSearchStep(std::vector<AVLAnimStep>& events, LogicAVLNode* root, int key);

	// Set correct positions for ALL VISUAL nodes (uses inorder positioning)
	void refreshAllVisNodePos(std::map<int, VisualAVLNode>& visualNodes, LogicAVLNode* root);
	// Helper function for refreshAllNodePos
	void refreshRecursiveVisNodePos(std::map<int, VisualAVLNode>& visualNodes, LogicAVLNode* node, float& xPos, float dx, int& layerY);


	// Draw a node (a circle with the key as text inside it)
	void drawNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualAVLNode& visNode);
	// Draw the highlight circle (a circle highlighting a node)
	void drawHighlightCircle(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f center, bool isFoundNode);
	// Draw tree edges
	///// MAKE SURE visualNodes std::map OBJECTS ARE POPULATED FIRST) /////
	void drawTreeEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const LogicAVLNode* root, std::map<int, VisualAVLNode>& visualNodes);
	// Draw a STILL tree (no interpolation between the tree states)
	void drawStillTree(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::map<int, VisualAVLNode>& visualNodes);


	// Helper drawing functions
	void drawNodeArrow(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f start, sf::Vector2f end);
};
