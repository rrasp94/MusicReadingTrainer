#pragma once

#include "ScreenBuffer.h"
#include "Tonality.h"
#include "Keyboard.h"
#include "InputManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"


namespace MusicReadingTrainer {

	class Game {

	private:

		ScreenBuffer screenBuffer;
		Tonality tonality;
		Keyboard keyboard;
		InputManager inputManager;
		ScoreManager scoreManager;
		SoundManager soundManager;

		bool isRunning = true;

	public:

		void run(); 
		void update();
		void render();

		void handleSound(const std::vector<wchar_t>& pressedKeys);

	};

}

