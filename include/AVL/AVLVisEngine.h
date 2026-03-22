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


	// Methods and properties for animating steps
	// (Already included in AnimPlayer class)


	LogicAVLTree tree;
	std::map<int, VisualAVLNode> visualNodesOld1; // Visual nodes for TREE BEFORE ROTATION 1
	std::map<int, VisualAVLNode> visualNodesOld2; // Visual nodes for TREE BEFORE ROTATION 2 / AFTER ROTATION 1
	std::map<int, VisualAVLNode> visualNodesCur; // Visual nodes for CURRENT TREE



	static constexpr sf::Vector2f originPosDisplacement = {0, 50};
	sf::Vector2f originPos;
	static constexpr sf::Vector2f descriptionTextPos    = {50, 10};
	static constexpr int          descriptionFontSize   = 15;
	static constexpr float        nodeCircleRadius      = 25;
	static constexpr int          nodeKeyTextFontSize   = 15;
	static constexpr float        nodeLayerSpacing      = 100;
	static constexpr float        canvasLeftMargin      = 100;

	static constexpr sf::Color    normalNodeColor         = sf::Color::Black;
	static constexpr sf::Color    normalNodeKeyColor      = sf::Color::Blue;
	static constexpr sf::Color    normalNodeHeightColor   = sf::Color(6, 64, 43, 255);


private:
	// Set correct positions for ALL VISUAL nodes (uses inorder positioning)
	void refreshAllVisNodePos(std::map<int, VisualAVLNode>& visualNodes, LogicAVLNode* root);
	// Helper function for refreshAllNodePos
	void refreshRecursiveVisNodePos(std::map<int, VisualAVLNode>& visualNodes, LogicAVLNode* node, float& xPos, float dx, int& layerY);


	// Draw a node (a circle with the key as text inside it)
	void drawNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualAVLNode& visNode);
	// Draw a STILL tree (no interpolation between the tree states)
	void drawStillTree(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::map<int, VisualAVLNode>& visualNodes);
};
