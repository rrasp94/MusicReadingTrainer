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

		bool isRunning;
		bool isKeySelected;

	public:

		Game();

		void run(); 
		void update();
		void render();

		void handleSound(const std::vector<wchar_t>& pressedKeys);

		void stopGame();

	};

	extern Game* g_game;                       
	BOOL WINAPI ConsoleHandler(DWORD signal);  

}

