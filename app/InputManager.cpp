#include "InputManager.h"
#include "windows.h"
#include <cwctype>



namespace MusicReadingTrainer {

	constexpr std::array<wchar_t, 12> InputManager::keys;
	constexpr std::array<wchar_t, 4> InputManager::menuKeys;

	InputManager::InputManager() {

		for (const auto key : keys) {
			keyStates[key] = false;
			previousKeyStates[key] = false;
		}

		for (auto key : menuKeys) {
			keyStates[key] = false;
			previousKeyStates[key] = false;
		}

	}

	void InputManager::update() {

		previousKeyStates = keyStates;

		for (auto& pair : keyStates) {
			wchar_t key = pair.first;
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

		for (auto& pair : keyStates) {
			if (pair.second) {
				pressedKeys.push_back(towlower(pair.first));
			}
		}
		return pressedKeys;

	}

	std::vector<wchar_t> InputManager::getJustPressedKeys() {

		std::vector<wchar_t> justPressedKeys;
		for (auto& pair : keyStates) {
			if (wasKeyJustPressed(pair.first)) {
				justPressedKeys.push_back(towlower(pair.first));
			}
		}
		return justPressedKeys;

	}

	std::vector<wchar_t> InputManager::getJustPressedKeysForMenu() {
		std::vector<wchar_t> justPressed;
		for (auto key : menuKeys) {
			if (wasKeyJustPressed(key)) {
				justPressed.push_back(key);
			}
		}
		return justPressed;
	}

	std::vector<wchar_t> InputManager::getJustPressedKeysForGameplay() {
		std::vector<wchar_t> justPressed;
		for (auto key : keys) {
			if (wasKeyJustPressed(key)) {
				justPressed.push_back(towlower(key));
			}
		}
		return justPressed;
	}

}