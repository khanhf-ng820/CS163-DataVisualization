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

#include "Trie/const.h"



static inline constexpr float EPSILON_TIME = 1e-6;



///// Math / sf::Vector utility functions
static inline constexpr double PI_CONST = 3.14159265358979323846;

inline const float fract(float f) { return f - floor(f); }

inline const sf::Vector2f round(sf::Vector2f vec) {
	return sf::Vector2f(round(vec.x), round(vec.y));
}

inline const bool isPerfectSquare(long long n) {
	if (n < 0) return false;
	if (n == 0 || n == 1) return true;
	long long root = static_cast<long long>(std::round(std::sqrt(n)));
	return root * root == n;
}

inline const int perfectSquareRoot(int n) {
	assert(isPerfectSquare(n));
	return static_cast<int>(std::sqrt(n));
}

inline const sf::Vector2f limitMag(sf::Vector2f vec, float maxMag) {
	if (vec.lengthSquared() > maxMag * maxMag)
		vec = vec.normalized() * maxMag;
	return vec;
}

inline const sf::Vector2f lerp(sf::Vector2f v1, sf::Vector2f v2, float k)  {
	return v1 + k * (v2 - v1);
}

inline const sf::Vector2f easeInOutLerp(sf::Vector2f v1, sf::Vector2f v2, float k)  {
	return v1 + (v2 - v1) * (k < 0.5f ? 2 * k * k : 1 - 2 * (1 - k) * (1 - k));
}





///// String utility functions
inline const std::string trim(const std::string& str) {
	auto start = std::find_if_not(str.begin(), str.end(),
		[](unsigned char ch) { return std::isspace(ch); });

	auto end = std::find_if_not(str.rbegin(), str.rend(),
		[](unsigned char ch) { return std::isspace(ch); }).base();

	if (start >= end)
		return "";

	return std::string(start, end);
}

inline const void SetStringToClipboard(const std::string& text) {
    sf::Clipboard::setString(text);
}





///// Trie utility functions
inline const bool isLowercaseAZChar(const char c) {
	return (c >= 'a' && c <= 'z'); // Must change this if changing Trie alphabet
}
inline const bool isLowercaseAZStr(const std::string& str) {
	for (const char& c : str) {
		if (!isLowercaseAZChar(c)) return false;
	}
	return true;
}
inline const bool isValidTrieChar(const char c) {
	return isLowercaseAZChar(c);
}
inline const bool isValidTrieString(const std::string& str) {
	return isLowercaseAZStr(str) && str.size() >= TRIE_INIT_WORD_MIN_LENGTH && str.size() <= TRIE_INIT_WORD_MAX_LENGTH;
}





///// std::vector utility functions
inline const bool vecContains(std::vector<int> vec, int str) {
	return std::find(vec.begin(), vec.end(), str) != vec.end();
}
