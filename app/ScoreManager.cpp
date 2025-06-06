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

    void ScoreManager::addCorrectAnswer() {

        correct++;
        totalAnswers++;
        streak++;
        if (streak > maxStreak) maxStreak = streak;
        levelUpStreak++;
        if (level < maxLevel && levelUpStreak >= levelUpTarget) {
            level++;
            levelUpStreak = 0;
        }
        accuracy = (totalAnswers > 0) ? (correct * 100) / totalAnswers : 0;
        updateStatusLine();

    }

    void ScoreManager::addIncorrectAnswer() {

        incorrect++;
        totalAnswers++;
        streak = 0;
        levelUpStreak = 0;
        updateStatusLine();

    }

    void ScoreManager::updateStatusLine() {

        swprintf(statusLine, sizeof(statusLine) / sizeof(wchar_t),
            L"Level: %2d | Correct: %3d | Incorrect: %3d | Accuracy: %3d%% | Streak: %3d | Max streak: %3d | Level-up: %2d / %2d",
            level, correct, incorrect, accuracy, streak, maxStreak, levelUpStreak, levelUpTarget);

    }

    void ScoreManager::reset() {

        level = 1;
        correct = 0;
        incorrect = 0;
        totalAnswers = 0;
        accuracy = 0;
        streak = 0;
        maxStreak = 0;
        levelUpStreak = 0;
        updateStatusLine();

    }

    int ScoreManager::getLevel() const {
        return level;
    }
}