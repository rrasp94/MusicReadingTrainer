#pragma once

#include <map>
#include <vector>
#include <array>


namespace MusicReadingTrainer {

	class InputManager {

	private:

		std::map<wchar_t, bool> keyStates;
		std::map<wchar_t, bool> previousKeyStates;

	public:

		static constexpr std::array<wchar_t, 12> keys = { L'Y', L'S', L'X', L'D', L'C', L'V', L'G', L'B', L'H', L'N', L'J', L'M' };

		InputManager();

		void update();

		bool isKeyPressed(wchar_t key);

		bool wasKeyPressed(wchar_t key);

		bool wasKeyJustPressed(wchar_t key);

		std::vector<wchar_t> getPressedKeys();

		#ifdef TESTING
		void MusicReadingTrainer::InputManager::setKeyState(wchar_t key, bool isPressed) {
			previousKeyStates[key] = keyStates[key];
			keyStates[key] = isPressed;
		}
		#endif

	};

}
