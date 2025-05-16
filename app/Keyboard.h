#pragma once

#include "ScreenBuffer.h"
#include "InputManager.h"
#include <string>
#include <vector>

namespace MusicReadingTrainer {

	class Keyboard {

	private:

		int position_x = 20;
		int position_y = 22;

		std::vector<std::wstring> keyboardLayout;

	public:

		Keyboard();

		void updateLayout(const std::vector<wchar_t>& pressedKeys);
		void draw(ScreenBuffer& screenBuffer);

	};
}
