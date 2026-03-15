#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "sfLayout/sfLayout.h"
#include "utils/utils.h"





class AnimPlayer {
public:
	AnimPlayer();

	float time = 0;
	float dt = 0.005; // Speed of animation
	float targetTime = 0; // ONLY USE WHEN PAUSED

	bool animPaused = false;
	bool animInProgress = false;
	constexpr static float dt_per_sec = 0.25f; // FOR TESTING ONLY

	constexpr static float MAX_TIME = 100000;


	void resetAnimParams();

	void increaseTime();
	void decreaseTime();

	void prevStep();
	void nextStep();
	void skipToFinalState();

protected:
	int animStepIndex = 0;
	int oldAnimStepIndex = 0;
};
