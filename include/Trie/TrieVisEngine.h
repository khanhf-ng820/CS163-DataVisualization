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
#include "Trie/LogicTrie.h"
#include "Trie/TrieSourceCode.h"



enum class TrieVisMode {
	NONE,
	SEARCH,
	INSERT,
	REMOVE,
	UPDATE
};



// REMEMBER:
// Drawing SFML: The center of the window is now (0, 0) coordinates
// Drawing GUI: The top-left of the window is (0, 0) coordinates
class TrieVisEngine : public AnimPlayer {
public:
	TrieVisEngine(sf::RenderWindow* window, sf::Font* font); // Empty, size 0 Trie
	TrieVisEngine(std::mt19937& rng, sf::RenderWindow* window, sf::Font* font); // Randomized Trie
	TrieVisEngine(std::vector<std::string>& words, sf::RenderWindow* window, sf::Font* font); // Custom data Trie
	~TrieVisEngine(); // Delete all dynamically allocated memory

	// Reset all properties to get ready for visualize new action
	void resetParams();

	// Draw nodes: Iterate through linked list and draw nodes
	void addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, TrieAnimStep eventTrie);
	void addNodeDrawablesInsert(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, TrieAnimStep eventTrie);
	void addNodeDrawablesDelete(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, TrieAnimStep eventTrie);
	void addNodeDrawablesUpdate(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, TrieAnimStep eventTrie);
	void drawPseudocodeWindow(TrieAnimStep eventTrie);
	// Draw nodes and links, depending on eventList
	void createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::vector<std::unique_ptr<sf::Drawable>>& drawableListDefaultView);
	void displayDrawables(std::unique_ptr<sfLayout>& sfmlLayout);


	sf::RenderWindow* windowPtr;
	sf::Font* fontPtr;
	sf::Vector2f normalWindowSize = {800.f, 600.f}; // Window size before rescaling window

	TrieVisMode visMode = TrieVisMode::NONE;
	std::vector<TrieAnimStep> eventList;


	///// Parameters for Visualization
	// int curIndex = -1; // Index of slot currently animating


	///// Buffers for Input in ImGui
	std::string wordToSearch;      // Searching
	char        wordToSearchInput[TRIE_TEXT_INPUT_BUF_SIZE];

	std::string wordToInsert;      // Inserting
	char        wordToInsertInput[TRIE_TEXT_INPUT_BUF_SIZE];

	std::string wordToRemove;      // Removing
	char        wordToRemoveInput[TRIE_TEXT_INPUT_BUF_SIZE];

	std::string oldWordToUpdate;      // Updating
	char        oldWordToUpdateInput[TRIE_TEXT_INPUT_BUF_SIZE];
	std::string newWordToUpdate;
	char        newWordToUpdateInput[TRIE_TEXT_INPUT_BUF_SIZE];


	// Methods and properties for animating steps
	// (Already included in AnimPlayer class)


	///// ALGORITHMS
	std::vector<TrieAnimStep> getEventsSearch(std::string word);
	std::vector<TrieAnimStep> getEventsInsert(std::string word);
	std::vector<TrieAnimStep> getEventsDelete(std::string word);
	std::vector<TrieAnimStep> getEventsUpdate(std::string oldWord, std::string newWord);


	LogicTrie tree; // Final state of tree
	std::vector<LogicTrie> oldTreeSnapshots; // Old Logical Trie trees

	std::vector<std::map<int, VisualTrieNode>> groupsOldVisualNodes; // Visual nodes from old trees (from oldest to newest)
	std::map<int, VisualTrieNode> visualNodesCur; // Visual nodes for CURRENT TREE



	static constexpr sf::Vector2f originPosDisplacement = {0, 70};
	sf::Vector2f originPos;
	static constexpr sf::Vector2f newNodeStartPos       = {50, 50};
	static constexpr sf::Vector2f descriptionTextPos    = {50, 10};
	static constexpr int          descriptionFontSize   = 15;
	static constexpr float        nodeCircleRadius      = 20;
	static constexpr float        nodeOutlineThickness  = 2;
	static constexpr int          nodeKeyTextFontSize   = 15;
	static constexpr int          nodeHeightTextFontSize = 12;
	static constexpr float        nodeLayerSpacing      = 60;
	static constexpr float        highlightCircleThickness = 5;
	static constexpr float        arrowHeadSideLen      = 8;
	static constexpr float        canvasLeftMargin      = 100;

	static constexpr sf::Color    normalNodeColor         = sf::Color::Black;
	static constexpr sf::Color    normalNodeKeyColor      = sf::Color::Blue;
	static constexpr sf::Color    normalNodeEOW_BGColor   = sf::Color(144, 238, 144, 127);
	static constexpr sf::Color    highlightCircleColor    = sf::Color::Green;
	static constexpr sf::Color    highlightFoundCircleColor = sf::Color::Red;
	static constexpr sf::Color    highlightCodeColor      = sf::Color::Green;


private:
	void initInputBuffers();
	void refreshOriginPos();
	// Helper algorithm functions
	void getEventsSearchStep(std::vector<TrieAnimStep>& events, LogicTrieNode* root, int key);

	// Set correct positions for ALL VISUAL nodes (uses inorder positioning)
	void generateAllVisNodePos(std::map<int, VisualTrieNode>& visualNodes, LogicTrie& logicTree);
	// Helper functions for generateAllVisNodePos
	void generateAllVisNodePosXHelper(std::map<int, VisualTrieNode>& visualNodes, LogicTrie& logicTree, LogicTrieNode* root);
	void generateRecursiveVisNodePosX(std::map<int, VisualTrieNode>& visualNodes, LogicTrieNode* node, float& xPos, float dx);
	void generateAllVisNodePosYHelper(std::map<int, VisualTrieNode>& visualNodes, LogicTrie& logicTree, LogicTrieNode* root);
	void generateRecursiveVisNodePosY(std::map<int, VisualTrieNode>& visualNodes, LogicTrieNode* node, int& layerY);


	// Draw a node (a circle with the key as text inside it)
	void drawNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualTrieNode& visNode);
	// Draw the highlight circle (a circle highlighting a node)
	void drawHighlightCircle(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f center, bool isFoundNode);
	// Draw tree edges
	///// MAKE SURE visualNodes std::map OBJECTS ARE POPULATED FIRST) /////
	void drawTreeEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const LogicTrieNode* root, std::map<int, VisualTrieNode>& visualNodes);
	// Draw a STILL tree (no interpolation between the tree snapshots)
	void drawStillTree(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::map<int, VisualTrieNode>& visualNodes, LogicTrie& logicTree);

	// Draw lerped node
	void drawLerpNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualTrieNode& visNode1, const VisualTrieNode& visNode2);
	// Draw lerped tree edges (arrows)
	void drawLerpTreeEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const LogicTrieNode* root,
		std::map<int, VisualTrieNode>& visualNodes1, std::map<int, VisualTrieNode>& visualNodes2);
	// Draw lerped tree (nodes and edges)
	void drawLerpTree(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
		std::map<int, VisualTrieNode>& visualNodes1, LogicTrie& logicTree1,
		std::map<int, VisualTrieNode>& visualNodes2, LogicTrie& logicTree2);
	// Draw lerped tree when inserting a node
	void drawLerpTreeInsertNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
		std::map<int, VisualTrieNode>& visualNodes1, LogicTrie& logicTree1,
		std::map<int, VisualTrieNode>& visualNodes2, LogicTrie& logicTree2,
		uint64_t nodeInsertID);
	// Draw lerped tree when deleting a node
	void drawLerpTreeDeleteNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
		std::map<int, VisualTrieNode>& visualNodes1, LogicTrie& logicTree1,
		std::map<int, VisualTrieNode>& visualNodes2, LogicTrie& logicTree2,
		uint64_t nodeRemoveID);


	// Helper drawing functions
	void drawNodeArrow(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f start, sf::Vector2f end);
};
