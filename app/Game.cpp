#include "Game.h"


namespace MusicReadingTrainer {


	void Game::run() {

		while (isRunning) {
			update();
			render();
			Sleep(100); 
		}
	}

	void Game::update() {

		inputManager.update();

		std::vector<wchar_t> pressedKeys = inputManager.getPressedKeys();

		keyboard.updateLayout(pressedKeys);

		handleSound(pressedKeys);

	}

	void Game::render() {

		screenBuffer.clearScreen();

		tonality.draw(screenBuffer);

		keyboard.draw(screenBuffer);

		scoreManager.draw(screenBuffer);

		screenBuffer.renderScreen();
	}

	void Game::handleSound(const std::vector<wchar_t>& pressedKeys) {

		if (!pressedKeys.empty()) {
			soundManager.SetKey(towupper(pressedKeys[0]));
		}
		else {
			soundManager.Stop();
		}

	}

}