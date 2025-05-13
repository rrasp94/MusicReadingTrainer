#include "Game.h"
#include "Tonality.h"
#include "ScreenBuffer.h"

namespace MusicReadingTrainer {


	void Game::render() {

		screenBuffer.clearScreen();

		tonality.draw(screenBuffer);

		screenBuffer.renderScreen();

	}

}