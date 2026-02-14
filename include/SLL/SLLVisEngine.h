#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "SLL/SLLAnimStep.h"
#include "SLL/SLLAlgoEngine.h"
#include "sfLayout/sfLayout.h"




class SLLVisEngine : public SLLAlgoEngine {
public:
	// using SLLAlgoEngine::SLLAlgoEngine;
	// SLLVisEngine();
	SLLVisEngine(sf::RenderWindow& window, sf::Font& font);
	~SLLVisEngine();

	void initDrawables(std::vector<std::unique_ptr<sf::Drawable>>& drawableList, std::vector<SLLAnimStep> eventList);
	void displayDrawables(std::unique_ptr<sfLayout>& sfmlLayout);


	sf::RenderWindow& window;
	sf::Font& font;

	int animStepIndex = 0; // first step
	float time = 0;

	float dt_per_sec = 0.25f;
	void increaseTime();

	sf::Vector2f startingPos;
	static constexpr sf::Vector2f nodeRectSize = {70, 50};
	static constexpr sf::Vector2f nodeValueRectSize = {50, 50};
	static constexpr float        linkArrowLength = 40;
	static constexpr int          valueFontSize = 15;

private:

};
