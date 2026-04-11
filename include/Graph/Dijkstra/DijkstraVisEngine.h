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
#include "Graph/Dijkstra/DijkstraPseudocode.h"



enum class DijkstraVisMode {
	NONE,
	DIJKSTRA
};



// REMEMBER:
// Drawing SFML: The center of the window is now (0, 0) coordinates
// Drawing GUI: The top-left of the window is (0, 0) coordinates
class DijkstraVisEngine : public AnimPlayer {
public:
	DijkstraVisEngine(unsigned int numVertex, sf::RenderWindow* window, sf::Font* font, sf::View* view); // N vertices graph
	// DijkstraVisEngine(std::mt19937& rng, sf::RenderWindow* window, sf::Font* font, sf::View* view); // Randomized graph
	DijkstraVisEngine(std::vector<std::vector<Edge>>& adjList, sf::RenderWindow* window, sf::Font* font, sf::View* view); // Custom data graph
	~DijkstraVisEngine(); // Delete all dynamically allocated memory

	// Reset all properties to get ready for visualize new action
	void resetParams();


	// Keeps track of which node is dragged, set position of that node
	int draggedVertexID = -1;
	void getDraggedVertexID(sf::Vector2f mousePos, sf::Vector2f viewDisplacement, float viewZoomFactor);
	void resetDraggedVertexID();
	void dragVertexByMouse(sf::Vector2f mousePos, sf::Vector2f viewDisplacement, float viewZoomFactor);

	// Draw nodes and links, depending on eventList
	void createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList);
	void displayDrawables(std::unique_ptr<sfLayout>& sfmlLayout);


	sf::RenderWindow* windowPtr;
	sf::Font* fontPtr;
	sf::View* viewPtr;

	DijkstraVisMode visMode = DijkstraVisMode::NONE;
	std::vector<DijkstraAnimStep> eventList;
	std::unique_ptr<sfLayout> drawableListDefaultView;


	///// Parameters for Visualization
	// int curIndex = -1; // Index of slot currently animating


	///// Buffers for Input in ImGui
	int startVertexID = 0;         // Run Dijkstra
	int startVertexIDInput = 0;


	// Methods and properties for animating steps
	// (Already included in AnimPlayer class)


	///// ALGORITHMS
	std::vector<DijkstraAnimStep> getEventsDijkstra(int startVertex);


	LogicGraphDijkstra graph; // Final state of graph
	// Old Logical Dijkstra graphs
	std::vector<std::vector<LogicGraphVertexDijkstra>> oldGraphSnapshots;

	// std::vector<std::vector<VisualGraphVertex>> groupsOldVisualNodes; // Visual nodes from old graphs (from oldest to newest)
	std::vector<VisualGraphVertex> visualNodesCur; // Visual nodes for CURRENT GRAPH



	static constexpr sf::Vector2f originPosDisplacement = {0, 70};
	sf::Vector2f originPos;
	static constexpr sf::Vector2f newNodeStartPos       = {50, 50};
	static constexpr sf::Vector2f descriptionTextPos    = {50, 10};
	static constexpr int          descriptionFontSize   = 15;
	static constexpr float        canvasLeftMargin      = 100;

	static constexpr float        nodeCircleRadius      = 20;
	static constexpr float        nodeOutlineThickness  = 2;
	static constexpr int          nodeIDTextFontSize    = 15;
	static constexpr int          nodeHeightTextFontSize = 12;
	static constexpr int          nodeInfoTextFontSize  = 12;
	static constexpr float        nodeLayerSpacing      = 60;
	static constexpr float        highlightCircleThickness = 5;

	static constexpr int          edgeWeightTextFontSize = 14;
	static constexpr float        highlightEdgeThickness   = 3;
	static constexpr float        arrowHeadSideLen      = 8;

	static constexpr sf::Color    normalNodeColor         = sf::Color::Black;
	static constexpr sf::Color    normalNodeKeyColor      = sf::Color::Blue;
	static constexpr sf::Color    visitedNodeColor        = sf::Color::Green; // sf::Color(255, 116, 108, 102);
	static constexpr sf::Color    draggedNodeColor        = sf::Color::Cyan;
	static constexpr sf::Color    weightTextColor         = sf::Color::Red;
	static constexpr sf::Color    nodeInfoTextColor       = sf::Color(6, 64, 43, 255);
	static constexpr sf::Color    highlightCircleColor    = sf::Color::Blue;
	static constexpr sf::Color    highlightFoundCircleColor = sf::Color::Red;
	static constexpr sf::Color    highlightEdgeColor      = sf::Color::Blue;
	static constexpr sf::Color    highlightCodeColor      = sf::Color::Green;


private:
	void refreshOriginPos();

	// Draw nodes: Iterate through graph and draw nodes
	void addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, DijkstraAnimStep eventDijkstra);
	void drawPseudocodeWindow(DijkstraAnimStep eventDijkstra);
	// Get string of shortest path of the clicked vertex
	std::string getShortestPathString(int startVertex, int endVertex);

	// // Helper algorithm functions
	// void getEventsSearchStep(std::vector<DijkstraAnimStep>& events, LogicDijkstraNode* root, int key);

	// Set initial positions for ALL VISUAL NODES (evenly spaced in circle)
	void generateAllVisNodePos(LogicGraphDijkstra& logicGraph);

	// Properties/Constants to draw graph (force-directed)
	double k = 1; // = sqrt((width * height) / n);
	float centerAttractionConstant = 0.003f;
	float temperature = 20.f;
	float timeStep = 0.001f; // To scale force to move nodes

	// Update positions (based on force-directed graph drawing)
	// Fruchterman-Reingold algorithm
	void updateNodePositions();


	// Draw a node (a circle with the key as text inside it)
	void drawNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualGraphVertex& visVertex, const std::vector<LogicGraphVertexDijkstra>& graphSnapshot);
	// Draw the highlight circle (a circle highlighting a vertex)
	void drawHighlightCircle(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f center, bool isHighlighted);
	// Draw graph edges
	///// MAKE SURE visualNodes std::map OBJECTS ARE POPULATED FIRST) /////
	void drawGraphEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const std::vector<LogicGraphVertexDijkstra>& graphSnapshot);
	// Draw a STILL graph (no interpolation between the graph snapshots)
	void drawStillGraph(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const std::vector<LogicGraphVertexDijkstra>& graphSnapshot);

	// // Draw lerped node
	// void drawLerpNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualGraphVertex& visNode1, const VisualGraphVertex& visNode2);
	// // Draw lerped graph edges (straight lines)
	// void drawLerpTreeEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const LogicDijkstraNode* root,
	// 	std::vector<VisualGraphVertex>& visualNodes1, std::vector<VisualGraphVertex>& visualNodes2);
	// // Draw lerped graph (nodes and edges)
	// void drawLerpTree(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
	// 	std::vector<VisualGraphVertex>& visualNodes1, LogicDijkstra& logicTree1,
	// 	std::vector<VisualGraphVertex>& visualNodes2, LogicDijkstra& logicTree2);
	// // Draw lerped graph when inserting a node
	// void drawLerpTreeInsertNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
	// 	std::vector<VisualGraphVertex>& visualNodes1, LogicDijkstra& logicTree1,
	// 	std::vector<VisualGraphVertex>& visualNodes2, LogicDijkstra& logicTree2,
	// 	uint64_t nodeInsertID);
	// // Draw lerped graph when deleting a node
	// void drawLerpTreeDeleteNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
	// 	std::vector<VisualGraphVertex>& visualNodes1, LogicDijkstra& logicTree1,
	// 	std::vector<VisualGraphVertex>& visualNodes2, LogicDijkstra& logicTree2,
	// 	uint64_t nodeRemoveID);


	// Helper drawing functions
	void drawEdgeLine(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f start, sf::Vector2f end);
	void drawEdgeWeightText(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f start, sf::Vector2f end, int weight);
	void drawHighlightEdge(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f start, sf::Vector2f end);
};
