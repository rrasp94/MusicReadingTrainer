#pragma once

#include "ScreenBuffer.h"
#include "Tonality.h"
#include "Keyboard.h"
#include "InputManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "NoteManager.h"
#include "NoteGenerator.h"
#include "LevelManager.h"
#include "KeySelectionScreen.h"

#include <vector>
#include <windows.h>
#include <atomic>

namespace MusicReadingTrainer {

	class Game {

	private:

		ScreenBuffer screenBuffer;
		Tonality tonality;
		Keyboard keyboard;
		InputManager inputManager;
		ScoreManager scoreManager;
		SoundManager soundManager;
		NoteManager noteManager;
		NoteGenerator noteGenerator;
		LevelManager levelManager;
		KeySelectionScreen keySelectionScreen;

		Key activeKey;

		std::atomic<bool> shouldExit;
		bool isRunning;
		bool isKeySelected;

		static Game* instance;
		static BOOL WINAPI ConsoleHandler(DWORD signal);

	public:

		Game();
		~Game();

		void run(); 
		void update();
		void render();

		void handleSound(const std::vector<wchar_t>& pressedKeys);

		void stopGame();
		void requestExit();

	};

}

