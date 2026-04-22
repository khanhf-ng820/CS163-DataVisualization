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

#include "Themes/Themes.h"
#include "sfLayout/sfLayout.h"
#include "utils/readData.hpp"
#include "utils/utils.h"
#include "AnimPlayer/AnimPlayer.h"
#include "Graph/MSTPrim/LogicGraphPrim.h"
#include "Graph/MSTPrim/PrimPseudocode.h"



enum class PrimVisMode {
	NONE,
	MST_PRIM
};



// REMEMBER:
// Drawing SFML: The center of the window is now (0, 0) coordinates
// Drawing GUI: The top-left of the window is (0, 0) coordinates
class PrimVisEngine : public AnimPlayer {
public:
	PrimVisEngine(unsigned int numVertex, sf::RenderWindow* window, sf::Font* font, sf::View* view); // N vertices graph
	PrimVisEngine(std::mt19937& rng, sf::RenderWindow* window, sf::Font* font, sf::View* view); // Randomized graph
	// Custom data initialization for graph
	PrimVisEngine(std::vector<std::vector<int>>& adjMatrix, 
		sf::RenderWindow* window, sf::Font* font, sf::View* view);
	PrimVisEngine(std::vector<std::vector<Edge>>& adjList, 
		sf::RenderWindow* window, sf::Font* font, sf::View* view);
	PrimVisEngine(unsigned int numVertex, std::vector<GraphReader::GraphEdge>& edgeList, 
		sf::RenderWindow* window, sf::Font* font, sf::View* view);
	~PrimVisEngine() = default; // Delete all dynamically allocated memory
	PrimVisEngine(const PrimVisEngine&) = default;
    PrimVisEngine& operator=(const PrimVisEngine&) = default;

	// Reset all properties to get ready for visualize new action
	void resetParams();

	// Set vis theme
	void setVisTheme(VIS_THEME visTheme);


	// Keeps track of which node is dragged, set position of that node
	int draggedVertexID = -1;
	void getDraggedVertexID(sf::Vector2f mousePos, sf::Vector2f viewDisplacement, float viewZoomFactor);
	void resetDraggedVertexID();
	void dragVertexByMouse(sf::Vector2f mousePos, sf::Vector2f viewDisplacement, float viewZoomFactor);

	// Draw nodes and links, depending on eventList
	void createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::vector<std::unique_ptr<sf::Drawable>>& drawableListDefaultView);
	void displayDrawables(std::unique_ptr<sfLayout>& sfmlLayout);


	sf::RenderWindow* windowPtr;
	sf::Font* fontPtr;
	sf::View* viewPtr;

	PrimVisMode visMode = PrimVisMode::NONE;
	std::vector<PrimAnimStep> eventList;


	///// Parameters for Visualization


	///// Buffers for Input in ImGui
	int startVertexID = 0;         // Run Prim
	int startVertexIDInput = 0;


	// Methods and properties for animating steps
	// (Already included in AnimPlayer class)


	///// ALGORITHMS
	std::vector<PrimAnimStep> getEventsPrim(int startVertex);


	LogicGraphPrim graph; // Final state of graph
	// Old Logical Prim graphs
	std::vector<std::vector<LogicGraphVertexPrim>> oldGraphSnapshots;

	// std::vector<std::vector<VisualGraphVertex>> groupsOldVisualNodes; // Visual nodes from old graphs (from oldest to newest)
	std::vector<VisualGraphVertex> visualNodesCur; // Visual nodes for CURRENT GRAPH



private:
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
	static constexpr float        highlightCircleThickness = 3.5;

	static constexpr int          edgeWeightTextFontSize = 14;
	static constexpr float        highlightEdgeThickness = 3;
	static constexpr float        highlightEdgeInMSTThickness = 3.5;
	static constexpr float        arrowHeadSideLen       = 8;

	static inline    sf::Color    normalNodeColor         = sf::Color::Black;
	static inline    sf::Color    normalNodeKeyColor      = sf::Color::Blue;
	static inline    sf::Color    visitedNodeColor        = sf::Color(144, 238, 144, 255); // sf::Color(255, 116, 108, 102);
	static inline    sf::Color    draggedNodeColor        = sf::Color::Cyan;
	static inline    sf::Color    weightTextColor         = sf::Color::Red;
	static inline    sf::Color    nodeInfoTextColor       = sf::Color(6, 64, 43, 255);
	static inline    sf::Color    highlightCircleColor    = sf::Color::Blue;
	static inline    sf::Color    highlightFoundCircleColor = sf::Color::Red;
	static inline    sf::Color    highlightEdgeColor      = sf::Color::Blue;
	static inline    sf::Color    highlightEdgeInMSTColor = sf::Color::Red;
	static inline    sf::Color    highlightCodeColor      = sf::Color(0x3CB371FF);


	void refreshOriginPos();

	// Draw nodes: Iterate through graph and draw nodes
	void addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, PrimAnimStep eventPrim);
	void drawPseudocodeWindow(PrimAnimStep eventPrim);
	// Get string of shortest path of the clicked vertex
	std::string getShortestPathString(int startVertex, int endVertex);

	// // Helper algorithm functions
	// void getEventsSearchStep(std::vector<PrimAnimStep>& events, LogicPrimNode* root, int key);

	// Set initial positions for ALL VISUAL NODES (evenly spaced in circle)
	void generateAllVisNodePos(LogicGraphPrim& logicGraph);

	// Properties/Constants to draw graph (force-directed)
	double k = 1; // = sqrt((width * height) / n);
	float centerAttractionConstant = 0.003f;
	float temperature = 20.f;
	float timeStep = 0.001f; // To scale force to move nodes

	// Update positions (based on force-directed graph drawing)
	// Fruchterman-Reingold algorithm
	void updateNodePositions();


	// Draw a node (a circle with the key as text inside it)
	void drawNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualGraphVertex& visVertex, const std::vector<LogicGraphVertexPrim>& graphSnapshot);
	// Draw the highlight circle (a circle highlighting a vertex)
	void drawHighlightCircle(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f center, bool isHighlighted);
	// Draw graph edges
	///// MAKE SURE visualNodes std::map OBJECTS ARE POPULATED FIRST) /////
	void drawGraphEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const std::vector<LogicGraphVertexPrim>& graphSnapshot);
	// Draw a STILL graph (no interpolation between the graph snapshots)
	void drawStillGraph(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const std::vector<LogicGraphVertexPrim>& graphSnapshot);

	// // Draw lerped node
	// void drawLerpNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const VisualGraphVertex& visNode1, const VisualGraphVertex& visNode2);
	// // Draw lerped graph edges (straight lines)
	// void drawLerpTreeEdges(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, const LogicPrimNode* root,
	// 	std::vector<VisualGraphVertex>& visualNodes1, std::vector<VisualGraphVertex>& visualNodes2);
	// // Draw lerped graph (nodes and edges)
	// void drawLerpTree(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
	// 	std::vector<VisualGraphVertex>& visualNodes1, LogicPrim& logicTree1,
	// 	std::vector<VisualGraphVertex>& visualNodes2, LogicPrim& logicTree2);
	// // Draw lerped graph when inserting a node
	// void drawLerpTreeInsertNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
	// 	std::vector<VisualGraphVertex>& visualNodes1, LogicPrim& logicTree1,
	// 	std::vector<VisualGraphVertex>& visualNodes2, LogicPrim& logicTree2,
	// 	uint64_t nodeInsertID);
	// // Draw lerped graph when deleting a node
	// void drawLerpTreeDeleteNode(std::vector<std::unique_ptr<sf::Drawable>>& drawableList,
	// 	std::vector<VisualGraphVertex>& visualNodes1, LogicPrim& logicTree1,
	// 	std::vector<VisualGraphVertex>& visualNodes2, LogicPrim& logicTree2,
	// 	uint64_t nodeRemoveID);


	// Helper drawing functions
	void drawEdgeLine(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f start, sf::Vector2f end);
	void drawEdgeWeightText(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f start, sf::Vector2f end, int weight);
	void drawHighlightEdge(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f start, sf::Vector2f end, bool inMST);




	// Predefined colors for vis themes
	static constexpr sf::Color lightNormalNodeColor         = sf::Color::Black;
	static constexpr sf::Color lightNormalNodeKeyColor      = sf::Color::Blue;
	static constexpr sf::Color lightVisitedNodeColor        = sf::Color(144, 238, 144, 255); // sf::Color(255, 116, 108, 102);
	static constexpr sf::Color lightDraggedNodeColor        = sf::Color::Cyan;
	static constexpr sf::Color lightWeightTextColor         = sf::Color::Red;
	static constexpr sf::Color lightNodeInfoTextColor       = sf::Color(6, 64, 43, 255);
	static constexpr sf::Color lightHighlightCircleColor    = sf::Color::Blue;
	static constexpr sf::Color lightHighlightFoundCircleColor = sf::Color::Red;
	static constexpr sf::Color lightHighlightEdgeColor      = sf::Color::Blue;
	static constexpr sf::Color lightHighlightEdgeInMSTColor = sf::Color::Red;
	static constexpr sf::Color lightHighlightCodeColor      = sf::Color(0x3CB371FF);

	static constexpr sf::Color darkNormalNodeColor         = sf::Color::White;
	static constexpr sf::Color darkNormalNodeKeyColor      = sf::Color(0x90D5FFFF);
	static constexpr sf::Color darkVisitedNodeColor        = sf::Color(0x06402BFF); // sf::Color(0x2E6F40FF);
	static constexpr sf::Color darkDraggedNodeColor        = sf::Color(0x545555FF);
	static constexpr sf::Color darkWeightTextColor         = sf::Color(0xFF746CFF);
	static constexpr sf::Color darkNodeInfoTextColor       = sf::Color::Green;      //sf::Color(0x80EF80FF);
	static constexpr sf::Color darkHighlightCircleColor    = sf::Color(0x3A5D9CFF);
	static constexpr sf::Color darkHighlightFoundCircleColor = sf::Color(0xFF746CFF);
	static constexpr sf::Color darkHighlightEdgeColor      = sf::Color(0x3A5D9CFF);
	static constexpr sf::Color darkHighlightEdgeInMSTColor = sf::Color::Red;
	static constexpr sf::Color darkHighlightCodeColor      = sf::Color(0x3CB371FF);

	void setLightVisTheme();
	void setDarkVisTheme();
};
