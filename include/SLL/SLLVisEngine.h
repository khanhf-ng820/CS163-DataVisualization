#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

#include "SLL/SLLAnimStep.h"
#include "SLL/SLLAlgoEngine.h"
#include "sfLayout/sfLayout.h"




static constexpr float EPSILON = 1e-6;

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


class SLLVisEngine : public SLLAlgoEngine {
public:
	// using SLLAlgoEngine::SLLAlgoEngine;
	// SLLVisEngine();
	SLLVisEngine(sf::RenderWindow& window, sf::Font& font);
	~SLLVisEngine();

	void resetParams();
	// Draw nodes: Iterate through linked list and draw nodes
	void addNodeDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, SLLAnimStep eventSLL);
	// INSERT MODE
	void addNodeDrawablesInsert(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, SLLAnimStep eventSLL);
	// REMOVE MODE
	void addNodeDrawablesRemove(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, SLLAnimStep eventSLL);
	// Draw nodes and links, depending on eventList
	void createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList);
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
	float dt_per_sec = 0.25f; // FOR TESTING ONLY
	void increaseTime();
	void decreaseTime();

	void prevStep();
	void nextStep();


	static constexpr sf::Vector2f originPosDisplacement = {75, 50};
	static constexpr sf::Vector2f headPosDisplacement = {-50, 0};
	sf::Vector2f originPos;
	static constexpr sf::Vector2f descriptionTextPos = {50, 10};
	static constexpr sf::Vector2f nodeRectSize = {50, 30};
	static constexpr sf::Vector2f nodeValueRectSize = {30, 30};
	static constexpr float        nodeLayerSpacing = 20 + 30; // 30 is nodeRectSize.y
	static constexpr float        linkArrowLength = 20;
	static constexpr int          valueFontSize = 10;
	static constexpr int          descriptionFontSize = 15;
	static constexpr float        arrowHeadSideLen = 7.5;

private:
	sf::Vector2f lerp(sf::Vector2f v1, sf::Vector2f v2, float k) const;

	void drawArrow(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, sf::Vector2f v1, sf::Vector2f v2) const;
};
