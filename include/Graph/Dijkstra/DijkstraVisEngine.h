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
#include "Graph/Dijkstra/LogicGraphDijkstra.h"
// #include "Graph/Dijkstra/DijkstraSourceCode.h"



enum class DijkstraVisMode {
	NONE,
	DIJKSTRA
};



// REMEMBER:
// Drawing SFML: The center of the window is now (0, 0) coordinates
// Drawing GUI: The top-left of the window is (0, 0) coordinates
class DijkstraVisEngine : public AnimPlayer {
public:
	DijkstraVisEngine(unsigned int numVertex, sf::RenderWindow* window, sf::Font* font); // N vertices graph
	// DijkstraVisEngine(std::mt19937& rng, sf::RenderWindow* window, sf::Font* font); // Randomized graph
	DijkstraVisEngine(std::vector<std::vector<Edge>>& adjList, sf::RenderWindow* window, sf::Font* font); // Custom data graph
	~DijkstraVisEngine(); // Delete all dynamically allocated memory

	// Reset all properties to get ready for visualize new action
	void resetParams();

	// Draw nodes: Iterate through linked list and draw nodes
	void addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, DijkstraAnimStep eventDijkstra);
	void drawPseudocodeWindow(DijkstraAnimStep eventDijkstra);
	// Draw nodes and links, depending on eventList
	void createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList);
	void displayDrawables(std::unique_ptr<sfLayout>& sfmlLayout);


	sf::RenderWindow* windowPtr;
	sf::Font* fontPtr;

	DijkstraVisMode visMode = DijkstraVisMode::NONE;
	std::vector<DijkstraAnimStep> eventList;


	///// Parameters for Visualization
	// int curIndex = -1; // Index of slot currently animating


	///// Buffers for Input in ImGui
	int startVertexID = 0;         // Run Dijkstra
	int startVertexIDInput = 0;
	// int wordToSearch = 0;      // Searching
	// int wordToSearchInput = -1;

	// int wordToInsert = 0;      // Inserting
	// int wordToInsertInput = -1;

	// int wordToRemove = 0;      // Removing
	// int wordToRemoveInput = -1;

	// int oldWordToUpdate = 0;      // Updating
	// int oldWordToUpdateInput = -1;
	// int newWordToUpdate;
	// int newWordToUpdateInput = -1;


	// Methods and properties for animating steps
	// (Already included in AnimPlayer class)


	///// ALGORITHMS
	std::vector<DijkstraAnimStep> getEventsDijkstra(int startVertex);
	// std::vector<DijkstraAnimStep> getEventsSearch(std::string word);
	// std::vector<DijkstraAnimStep> getEventsInsert(std::string word);
	// std::vector<DijkstraAnimStep> getEventsDelete(std::string word);
	// std::vector<DijkstraAnimStep> getEventsUpdate(std::string oldWord, std::string newWord);


	LogicGraphDijkstra graph; // Final state of graph
	// Old Logical Dijkstra graphs
	std::vector<LogicGraphDijkstra> oldGraphSnapshots;

	// std::vector<std::map<int, VisualGraphVertex>> groupsOldVisualNodes; // Visual nodes from old graphs (from oldest to newest)
	std::map<int, VisualGraphVertex> visualNodesCur; // Visual nodes for CURRENT TREE



	static constexpr sf::Vector2f originPosDisplacement = {0, 70};
	sf::Vector2f originPos;
	static constexpr sf::Vector2f newNodeStartPos       = {50, 50};
	static constexpr sf::Vector2f descriptionTextPos    = {50, 10};
	static constexpr int          descriptionFontSize   = 15;
	static constexpr float        nodeCircleRadius      = 20;
	static constexpr float        nodeOutlineThickness  = 2;
	static constexpr int          nodeIDTextFontSize   = 15;
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
	void refreshOriginPos();
	// // Helper algorithm functions
	// void getEventsSearchStep(std::vector<DijkstraAnimStep>& events, LogicDijkstraNode* root, int key);

	// Set correct positions for ALL VISUAL nodes (uses inorder positioning)
	// void generateAllVisNodePos(LogicDijkstra& logicTree);
	void generateAllVisNodePos(LogicGraphDijkstra& logicGraph);
	// Helper functions for generateAllVisNodePos
	// void generateAllVisNodePosHelper(LogicDijkstra& logicTree, LogicDijkstraNode* root);
	// void generateRecursiveVisNodePos(LogicDijkstraNode* node, float& xPos, float dx);
	// void generateAllVisNodePosYHelper(LogicDijkstra& logicTree, LogicDijkstraNode* root);
	// void generateRecursiveVisNodePosY(LogicDijkstraNode* node, int& layerY);


	// Draw a node (a circle with the key as text inside it)
	void drawNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualGraphVertex& visVertex, const LogicGraphDijkstra& graphSnapshot);
	// Draw the highlight circle (a circle highlighting a vertex)
	void drawHighlightCircle(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f center, bool isHighlighted);
	// Draw graph edges
	///// MAKE SURE visualNodes std::map OBJECTS ARE POPULATED FIRST) /////
	void drawGraphEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const LogicGraphDijkstra& graphSnapshot);
	// Draw a STILL graph (no interpolation between the graph snapshots)
	void drawStillGraph(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const LogicGraphDijkstra& graphSnapshot);

	// // Draw lerped node
	// void drawLerpNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualGraphVertex& visNode1, const VisualGraphVertex& visNode2);
	// // Draw lerped graph edges (straight lines)
	// void drawLerpTreeEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const LogicDijkstraNode* root,
	// 	std::map<int, VisualGraphVertex>& visualNodes1, std::map<int, VisualGraphVertex>& visualNodes2);
	// // Draw lerped graph (nodes and edges)
	// void drawLerpTree(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
	// 	std::map<int, VisualGraphVertex>& visualNodes1, LogicDijkstra& logicTree1,
	// 	std::map<int, VisualGraphVertex>& visualNodes2, LogicDijkstra& logicTree2);
	// // Draw lerped graph when inserting a node
	// void drawLerpTreeInsertNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
	// 	std::map<int, VisualGraphVertex>& visualNodes1, LogicDijkstra& logicTree1,
	// 	std::map<int, VisualGraphVertex>& visualNodes2, LogicDijkstra& logicTree2,
	// 	uint64_t nodeInsertID);
	// // Draw lerped graph when deleting a node
	// void drawLerpTreeDeleteNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
	// 	std::map<int, VisualGraphVertex>& visualNodes1, LogicDijkstra& logicTree1,
	// 	std::map<int, VisualGraphVertex>& visualNodes2, LogicDijkstra& logicTree2,
	// 	uint64_t nodeRemoveID);


	// Helper drawing functions
	// void drawEdgeLine(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f start, sf::Vector2f end);
	void drawNodeArrow(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f start, sf::Vector2f end);
};
