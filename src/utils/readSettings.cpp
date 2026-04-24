#include "utils/readSettings.h"



// Helper function
// Safe int parsing
bool SettingsReader::tryParseInt(const std::string& str, int& out) {
	std::istringstream iss(str);
	return (iss >> out) && iss.eof();
}

bool SettingsReader::tryParseUInt(const std::string& str, unsigned int& out) {
	std::istringstream iss(str);
	return (iss >> out) && iss.eof();
}




Settings SettingsReader::readSettings() {
	Settings s; // default settings

	std::ifstream file(fs::path(SETTINGS_FILE));
	if (!file.is_open()) {
		std::cerr << "-- " << std::string(SETTINGS_FILE) << " not found\n"; // log
		return s; // file missing, return defaults
	}

	std::cerr << "-- " << std::string(SETTINGS_FILE) << " file exists\n"; // log

	std::string line;
	while (std::getline(file, line)) {
		// Skip empty lines
		if (line.empty()) continue;

		auto pos = line.find('=');
		if (pos == std::string::npos) continue; // malformed line

		std::string key = line.substr(0, pos);
		std::string value = line.substr(pos + 1);

		if (key == "resolutionItemIndex") {
			int v;
			if (tryParseInt(value, v)) {
				s.resolutionItemIndex = v;
			}
		} else if (key == "appThemeItemIndex") {
			int v;
			if (tryParseInt(value, v)) {
				s.appThemeItemIndex = v;
			}
		} else if (key == "visThemeItemIndex") {
			int v;
			if (tryParseInt(value, v)) {
				s.visThemeItemIndex = v;
			}
		} else if (key == "imFontSizeIndex") {
			int v;
			if (tryParseInt(value, v)) {
				s.imFontSizeIndex = v;
			}
		}
	}

	return s;
}




void SettingsReader::saveSettings(const Settings& s) {
	std::ofstream file(fs::path(SETTINGS_FILE), std::ios::trunc);
	if (!file.is_open()) {
		std::cerr << "-- " << std::string(SETTINGS_FILE) << " can\'t be opened!\n"; // log
		return;
	}

	file << "resolutionItemIndex=" << s.resolutionItemIndex << "\n";
	file << "appThemeItemIndex=" << s.appThemeItemIndex << "\n";
	file << "visThemeItemIndex=" << s.visThemeItemIndex << "\n";
	file << "imFontSizeIndex=" << s.imFontSizeIndex << "\n";
}
