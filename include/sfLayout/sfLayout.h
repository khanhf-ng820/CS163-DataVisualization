#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>





class sfLayout {
public:
	sfLayout(sf::RenderWindow* window_ptr);
	~sfLayout();

	void displayAll();
	void clear();


	std::vector<std::unique_ptr<sf::Drawable>> drawables;

private:
	sf::RenderWindow* window_ptr;
};
