#pragma once

#include <map>
#include <vector>


namespace MusicReadingTrainer {

	class InputManager {

	private:

		const wchar_t* keys = L"YSXDCVGBHNJM";
		std::map<wchar_t, bool> keyStates;
		std::map<wchar_t, bool> previousKeyStates;

	public:

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
