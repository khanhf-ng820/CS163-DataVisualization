#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <cmath>
#include <random>

#include "Themes/Themes.h"
#include "sfLayout/sfLayout.h"
#include "utils/readData.hpp"
#include "SLL/SLLAnimStep.h"
#include "SLL/SLLAlgoEngine.h"





enum class SLLVisMode {
	NONE, // Currently visualizing no actions
	SEARCH,
	INSERT_BEG,
	INSERT_END,
	INSERT_K,
	UPDATE,
	REMOVE_BEG,
	REMOVE_K
};


// REMEMBER:
// Drawing SFML: The center of the window is now (0, 0) coordinates
// Drawing GUI: The top-left of the window is (0, 0) coordinates
class SLLVisEngine : public SLLAlgoEngine {
public:
	// using SLLAlgoEngine::SLLAlgoEngine;
	// SLLVisEngine();
	SLLVisEngine(sf::RenderWindow& window, sf::Font& font);
	~SLLVisEngine();

	void freeMem();
	void resetParams();
	void resetEngine(); // CLEAR/RESET ALL PROPERTIES (REMEMBER TO UPDATE, ONLY USE WHEN INITIALIZING NEW SLL)
	void initSLLData(); // Empty SLL
	void initSLLData(std::mt19937& rng); // Randomized SLL
	void initSLLData(std::vector<int>& initData); // Specific data SLL

	// Set vis theme
	void setVisTheme(VIS_THEME visTheme);

	// Draw nodes: Iterate through linked list and draw nodes
	void addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, SLLAnimStep eventSLL);
	// INSERT MODE
	void addNodeDrawablesInsert(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, SLLAnimStep eventSLL);
	// REMOVE MODE
	void addNodeDrawablesRemove(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, SLLAnimStep eventSLL);
	// Draw nodes and links, depending on eventList
	void createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::vector<std::unique_ptr<sf::Drawable>>& drawableListDefaultView);
	void displayDrawables(std::unique_ptr<sfLayout>& sfmlLayout);


	sf::RenderWindow& window;
	sf::Font& font;

	SLLVisMode visMode = SLLVisMode::NONE;
	std::vector<SLLAnimStep> eventList;

	SLLNode* visCur = nullptr; //  cur in visualization (not in code)
	int visCurIndex = 0; // cur index in visualization (not in code)

	// For Input
	int valToSearch = 0;      // Searching
	int valToSearchInput = 0;
	int valToInsert = 0;      // Inserting
	int valToInsertInput = 0;
	int idxToInsert = 0;
	int idxToInsertInput = 0;
	int valToUpdate = 0;      // Updating value
	int valToUpdateInput = 0;
	int idxToUpdate = 0;
	int idxToUpdateInput = 0;
	int idxToRemove = 0;      // Remove node
	int idxToRemoveInput = 0;

	// For Animation
	int animStepIndex = 0; // first step
	int oldAnimStepIndex = 0; // first step
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


	static constexpr unsigned int RANDOM_DISTRIB_SIZE_MIN = 6;
	static constexpr unsigned int RANDOM_DISTRIB_SIZE_MAX = 9;
	static constexpr int RANDOM_DISTRIB_VALUE_MIN = -100;
	static constexpr int RANDOM_DISTRIB_VALUE_MAX = 100;


private:
	static constexpr sf::Vector2f originPosDisplacement = {75, 50};
	static constexpr sf::Vector2f headPosDisplacement = {-50, 0};
	sf::Vector2f originPos;
	static constexpr sf::Vector2f descriptionTextPos  = {50, 10};
	static constexpr sf::Vector2f nodeRectSize        = {50, 30};
	static constexpr sf::Vector2f nodeValueRectSize   = {30, 30};
	static constexpr float        nodeLayerSpacing    = 20 + 30; // 30 is nodeRectSize.y
	static constexpr float        linkArrowLength     = 20;
	static constexpr int          valueFontSize       = 10;
	static constexpr int          descriptionFontSize = 15;
	static constexpr float        arrowHeadSideLen    = 7.5;

	static inline    sf::Color    normalNodeColor         = sf::Color::Black;
	static inline    sf::Color    nullDiagonalColor       = sf::Color(0, 0, 0, 255/2);
	static inline    sf::Color    highlightFoundNodeColor = sf::Color::Green;
	static constexpr ImVec4       highlightCodeColor = {0.4f, 1.f, 0.f, 1.f};


	void initSLLvector(std::vector<int>& values); // Init SLL from std::vector<int>

	// Create AND display ImGui window to highlight source code (pseudocode)
	void drawPseudocodeWindow(SLLAnimStep eventSLL);

	sf::Vector2f lerp(sf::Vector2f v1, sf::Vector2f v2, float k) const;
	void drawArrow(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f v1, sf::Vector2f v2) const;




	// Predefined colors for vis themes
	static constexpr sf::Color lightNormalNodeColor         = sf::Color::Black;
	static constexpr sf::Color lightNullDiagonalColor       = sf::Color(0, 0, 0, 255/2);
	static constexpr sf::Color lightHighlightFoundNodeColor = sf::Color::Green;

	static constexpr sf::Color darkNormalNodeColor         = sf::Color::White;
	static constexpr sf::Color darkNullDiagonalColor       = sf::Color(255, 255, 255, 255/2);
	static constexpr sf::Color darkHighlightFoundNodeColor = sf::Color::Green;

	void setLightVisTheme();
	void setDarkVisTheme();
};
