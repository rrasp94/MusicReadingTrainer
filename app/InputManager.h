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
		static constexpr std::array<wchar_t, 4> menuKeys = { L'W', L'S', L'\r', L'\x1B' };

		InputManager();

		void update();

		bool isKeyPressed(wchar_t key);
		bool wasKeyPressed(wchar_t key);
		bool wasKeyJustPressed(wchar_t key);

		std::vector<wchar_t> getPressedKeys();
		std::vector<wchar_t> getJustPressedKeys();

		std::vector<wchar_t> getJustPressedKeysForMenu();
		std::vector<wchar_t> getJustPressedKeysForGameplay();

		#ifdef TESTING
		void MusicReadingTrainer::InputManager::setKeyState(wchar_t key, bool isPressed) {
			previousKeyStates[key] = keyStates[key];
			keyStates[key] = isPressed;
		}
		#endif

	};

}
