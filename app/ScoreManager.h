#pragma once
#include "ScreenBuffer.h"

namespace MusicReadingTrainer {

	class ScoreManager {

	private:

		int position_x = 5;
		int position_y = 0;

		int level = 1;
		int correct = 0;
		int incorrect = 0;
		int totalAnswers = 0;
		int accuracy = 0;
		int streak = 0;
		int maxStreak = 0;
		int levelUpStreak = 0;
		int levelUpTarget = 10;

		wchar_t statusLine[200];

	public:

		ScoreManager();

		void draw(ScreenBuffer& screenBuffer);

	};

}
