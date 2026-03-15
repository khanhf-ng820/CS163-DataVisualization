#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>




static inline constexpr float EPSILON_TIME = 1e-6;


inline const float fract(float f) { return f - floor(f); }

inline const sf::Vector2f round(sf::Vector2f vec) {
	return sf::Vector2f(round(vec.x), round(vec.y));
}



inline const std::string trim(const std::string& str) {
	auto start = std::find_if_not(str.begin(), str.end(),
		[](unsigned char ch) { return std::isspace(ch); });

	auto end = std::find_if_not(str.rbegin(), str.rend(),
		[](unsigned char ch) { return std::isspace(ch); }).base();

	if (start >= end)
		return "";

	return std::string(start, end);
}



inline const bool vecContains(std::vector<int> vec, int str) {
	return std::find(vec.begin(), vec.end(), str) != vec.end();
}
