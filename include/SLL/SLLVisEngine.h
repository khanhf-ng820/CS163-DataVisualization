#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

#include "SLL/SLLAnimStep.h"
#include "SLL/SLLAlgoEngine.h"
#include "sfLayout/sfLayout.h"




enum class SLLVisMode {
	NONE, // Currently visualizing nothing
	SEARCH,
	INSERT_BEG,
	INSERT_END,
	INSERT_K
};


class SLLVisEngine : public SLLAlgoEngine {
public:
	// using SLLAlgoEngine::SLLAlgoEngine;
	// SLLVisEngine();
	SLLVisEngine(sf::RenderWindow& window, sf::Font& font);
	~SLLVisEngine();

	void resetParams();
	void createDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::vector<SLLAnimStep> eventList);
	void displayDrawables(std::unique_ptr<sfLayout>& sfmlLayout);


	sf::RenderWindow& window;
	sf::Font& font;

	SLLVisMode visMode = SLLVisMode::NONE;

	SLLNode* visCur = nullptr; //  cur in visualization (not in code)
	int visCurIndex = 0; // cur index in visualization (not in code)

	int animStepIndex = 0; // first step
	int oldAnimStepIndex = 0; // first step
	float time = 0;
	float dt = 0.005; // FOR TESTING ONLY

	float dt_per_sec = 0.25f;
	void increaseTime();


	static constexpr sf::Vector2f originPosDisplacement = {50, 50};
	sf::Vector2f originPos;
	static constexpr sf::Vector2f nodeRectSize = {50, 30};
	static constexpr sf::Vector2f nodeValueRectSize = {30, 30};
	static constexpr float        linkArrowLength = 20;
	static constexpr int          valueFontSize = 10;
	static constexpr float        arrowHeadLength = 7.5;

private:
	sf::Vector2f lerp(sf::Vector2f v1, sf::Vector2f v2, float k) const;
};
