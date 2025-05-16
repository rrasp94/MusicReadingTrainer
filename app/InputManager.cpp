#include "InputManager.h"
#include "windows.h"



namespace MusicReadingTrainer {

	InputManager::InputManager() {

		for (int i = 0; i < wcslen(keys); i++) {

			wchar_t key = keys[i];
			keyStates[key] = false;
			previousKeyStates[key] = false;

		}

	}

	void InputManager::update() {

		previousKeyStates = keyStates;

		for (int i = 0; i < wcslen(keys); i++) {

			wchar_t key = keys[i];
			if (GetAsyncKeyState(key) & 0x8000) {
				keyStates[key] = true;
			}
			else {
				keyStates[key] = false;
			}
		}

	}

	bool InputManager::isKeyPressed(wchar_t key) {

		return keyStates[key];

	}

	bool InputManager::wasKeyPressed(wchar_t key) {

		return previousKeyStates[key];

	}

	bool InputManager::wasKeyJustPressed(wchar_t key) {

		return keyStates[key] && !previousKeyStates[key];

	}

	std::vector<wchar_t> InputManager::getPressedKeys() {

		std::vector<wchar_t> pressedKeys;

		for (int i = 0; i < wcslen(keys); i++) {
			wchar_t key = keys[i];
			if (isKeyPressed(key)) {
				pressedKeys.push_back(towlower(key));
			}
		}
		return pressedKeys;

	}

}