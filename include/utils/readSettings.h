#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;


struct Settings {
	int resolutionItemIndex = 0;
	int appThemeItemIndex = 1; // Default is Dark mode
	int visThemeItemIndex = 0; // Default is Light mode
	int imFontSizeIndex = 0; // (SETTINGS)

	Settings() {}
	Settings(int resolutionItemIdx, int appThemeItemIdx, int visThemeItemIdx, int imFontSizeIdx)
	: resolutionItemIndex(resolutionItemIdx), appThemeItemIndex(appThemeItemIdx), visThemeItemIndex(visThemeItemIdx), imFontSizeIndex(imFontSizeIdx) {}
};



namespace SettingsReader {
	// Helper function
	// Safe int parsing
	bool tryParseInt(const std::string& str, int& out);
	bool tryParseUInt(const std::string& str, unsigned int& out);

	Settings readSettings();
	void     saveSettings(const Settings& s);
};
