#include "AnimPlayer/AnimPlayer.h"





AnimPlayer::AnimPlayer() {}


void AnimPlayer::resetAnimParams() {
	animInProgress = false;
	animStepIndex = 0;
	oldAnimStepIndex = 0;
	time = 0;
}


void AnimPlayer::increaseTime() {
	time += dt;
}

void AnimPlayer::decreaseTime() {
	time -= dt;
}

void AnimPlayer::prevStep() {
	targetTime = time - 1;
	targetTime = floor(targetTime);
	targetTime = std::max(targetTime, 0.f);
}

void AnimPlayer::nextStep() {
	targetTime = time + 1;
	targetTime = floor(targetTime);
	targetTime = std::max(targetTime, 0.f);
}

void AnimPlayer::skipToStartState() {
	time = targetTime = 0;
	// animPaused = false; // Auto un-pause
}

void AnimPlayer::skipToFinalState() {
	time = 100000;
	animPaused = false; // Auto un-pause
}
