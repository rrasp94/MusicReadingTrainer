#include "InputManager.h"
#include "windows.h"



namespace MusicReadingTrainer {

	constexpr std::array<wchar_t, 12> InputManager::keys;

	InputManager::InputManager() {

		for (const auto key : keys) {
			keyStates[key] = false;
			previousKeyStates[key] = false;
		}

	}

	void InputManager::update() {

		previousKeyStates = keyStates;

		for (const auto key : keys) {
			keyStates[key] = (GetAsyncKeyState(key) & 0x8000) != 0;
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

		for (const auto key : keys) {
			if (isKeyPressed(key)) {
				pressedKeys.push_back(towlower(key));
			}
		}

		return pressedKeys;

	}

}