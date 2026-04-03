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





inline static int FilterCallbackLowercaseAZ(ImGuiInputTextCallbackData* data) {
	if (data->EventChar < 256) {
		char c = (char)data->EventChar;

		// Allow only letters and numbers
		if (!(c >= 'a' && c <= 'z'))
			return 1; // Reject character
	}
	return 0;
}
