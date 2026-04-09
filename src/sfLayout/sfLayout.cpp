#include "sfLayout/sfLayout.h"



sfLayout::sfLayout(sf::RenderWindow* window_ptr)
	: window_ptr(window_ptr)
{}

sfLayout::~sfLayout() {}



void sfLayout::displayAll() {
	for (const auto& drawable : drawables) {
		window_ptr->draw(*drawable);
	}
}

void sfLayout::clear() {
	drawables.clear();
	drawables.shrink_to_fit();
}
