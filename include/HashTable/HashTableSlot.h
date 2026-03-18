#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <vector>
#include "utils/readData.hpp"




// Uses lazy deletion, linear probing (Open addressing)
class TableSlot {
public:
	TableSlot();
	explicit TableSlot(int index);
	TableSlot(int index, int key);
	TableSlot(int index, TableSlotInput input);

	// Methods
	bool hasKey(int keyVal);

	// Hash table properties
	int index = -1;
	int key   = -1;
	// int value = -1;
	bool empty   = true;
	bool deleted = false; // Tombstone marker, for lazy deletion

	// Animation properties
	bool highlighted = false; // Highlighted during animation

	// SFML properties
	sf::Vector2f rectPosition = {0.f, 0.f};
};

