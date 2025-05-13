#pragma once

#include "ScreenBuffer.h"
#include "Tonality.h"


namespace MusicReadingTrainer {

	class Game {

	private:

		ScreenBuffer screenBuffer;
		Tonality tonality;

	public:

		void render();

	};

}

