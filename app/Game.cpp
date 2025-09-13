#include "Game.h"
#include <algorithm>

namespace MusicReadingTrainer {

	Game* g_game = nullptr;

	BOOL WINAPI ConsoleHandler(DWORD signal) {
		if (signal == CTRL_CLOSE_EVENT && g_game) {
			g_game->requestExit();
		}
		return TRUE;
	}

	Game::Game()
		: isRunning(true), isKeySelected(false), activeKey(Key::C)
	{
		levelManager.setLevel(1);
	}

	void Game::stopGame() {

		isRunning = false;

		if (isKeySelected) { 
			soundManager.Stop();
			noteManager.clearNotes();
		}
	}

	void Game::requestExit() {
		shouldExit = true;
	}

	void Game::run() {

		while (!isKeySelected && !shouldExit) {
			inputManager.update();
			auto justPressedKeys = inputManager.getJustPressedKeys();

			for (wchar_t key : justPressedKeys) {
				if (key == L'\x1B') { // ESC
					requestExit();
					break;
				}
			}

			if (shouldExit) break;

			if (keySelectionScreen.update(justPressedKeys, activeKey)) {
				isKeySelected = true;
				break;
			}

			render();
			Sleep(100);
		}

		while (isRunning && !shouldExit) {
			update();
			render();
			Sleep(100);
		}

		if (shouldExit && isKeySelected) {
			stopGame();
		}
	}

	void Game::update() {

		inputManager.update();

		std::vector<wchar_t> justPressedGameplayKeys = inputManager.getJustPressedKeysForGameplay();
		std::vector<wchar_t> justPressedMenuKeys = inputManager.getJustPressedKeysForMenu();
		std::vector<wchar_t> pressedKeys = inputManager.getPressedKeys();

		for (wchar_t key : justPressedMenuKeys) {
			if (key == L'\x1B') {
				if (!isKeySelected) {
					requestExit();
					return;
				}
				else {
					isKeySelected = false;
					scoreManager.reset();
					levelManager.setLevel(1);
					noteManager.clearNotes();
					soundManager.Stop();
					return;
				}
			}
		}

		if (!isKeySelected) {
			Key selected;
			bool done = keySelectionScreen.update(justPressedMenuKeys, selected);
			keySelectionScreen.draw(screenBuffer);
			screenBuffer.renderScreen();

			if (done) {
				activeKey = selected; 
				isKeySelected = true;
			}
			return; 
		}

		keyboard.updateLayout(pressedKeys);
		keyboard.setUseFlats(tonality.isFlatKey(activeKey));

		const auto& notePositionsForKey = tonality.getNotePositionsForKey(activeKey);
		const auto& allowedPositionsForLevel = levelManager.getNotePositionsForCurrentLevel(notePositionsForKey);

		if (noteManager.shouldGenerateNewNote()) {
			Note newNote = noteGenerator.generateNote(115, allowedPositionsForLevel);
			noteManager.addNote(newNote);
		}

		noteManager.updateNotes();

		auto& notes = noteManager.getNotes();

		int previousLevel = scoreManager.getLevel();

		for (auto& note : notes) {
			if (note.x == 24 && note.status == NoteStatus::Untouched) {
				note.status = NoteStatus::Incorrect;
				scoreManager.addIncorrectAnswer();
			}
		}

		for (auto& note : notes) {
			if (note.status == NoteStatus::Untouched) {

				bool correctKeyPressed = false;
				bool anyKeyPressed = !justPressedGameplayKeys.empty();

				for (wchar_t key : justPressedGameplayKeys) {
					NoteName pressedNote = keyboard.getNoteForKey(key);

					if (pressedNote == note.name) {
						note.status = NoteStatus::Correct;
						scoreManager.addCorrectAnswer();
						correctKeyPressed = true;
						break;
					}
				}

				if (!correctKeyPressed && anyKeyPressed) {
					note.status = NoteStatus::Incorrect;
					scoreManager.addIncorrectAnswer();
				}

				break; 
			}
		}

		int currentLevel = scoreManager.getLevel();
		if (currentLevel != previousLevel) {
			levelManager.setLevel(currentLevel);
		}

		noteManager.removeOffscreenNotes();

		handleSound(pressedKeys);
	}

	void Game::render() {

		screenBuffer.clearScreen();

		if (!isKeySelected) {
			
			keySelectionScreen.draw(screenBuffer);
			
		}
		else {
			
			tonality.draw(screenBuffer, activeKey);
			keyboard.draw(screenBuffer);
			noteManager.drawNotes(screenBuffer);
			noteManager.drawArrowAboveActiveNote(screenBuffer);
			scoreManager.draw(screenBuffer);
		}

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