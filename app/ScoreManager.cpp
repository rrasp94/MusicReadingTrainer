#include "ScoreManager.h"
#include <string>

namespace MusicReadingTrainer {

	ScoreManager::ScoreManager() {

		swprintf(statusLine, sizeof(statusLine) / sizeof(wchar_t),
			L"Level: %2d | Correct: %3d | Incorrect: %3d | Accuracy: %3d%% | Streak: %3d | Max streak: %3d | Level-up: %2d / %2d",
			level, correct, incorrect, accuracy, streak, maxStreak, levelUpStreak, levelUpTarget);

	}

	void ScoreManager::draw(ScreenBuffer& screenBuffer) {

		screenBuffer.setScreen(position_x, position_y, std::vector<std::wstring>{ statusLine });

	}
}