#include "ScreenBuffer.h"

#include <algorithm>



namespace MusicReadingTrainer {

	ScreenBuffer::ScreenBuffer() {

		screen = std::vector<wchar_t>(nScreenWidth * nScreenHeight, L' ');
		hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole);

	}

	ScreenBuffer::~ScreenBuffer() {

		CloseHandle(hConsole);

	}

	void ScreenBuffer::setScreen(int position_x, int position_y, const std::vector<std::wstring>& data) {

		for (int y = 0; y < data.size(); y++) {
			for (int x = 0; x < data[y].size(); x++) {
				int screen_index = (position_y + y) * nScreenWidth + (position_x + x);
				screen[screen_index] = data[y][x];
			}
		}

	}

	void ScreenBuffer::clearScreen() {

		for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';

	}

	void ScreenBuffer::renderScreen() {

		WriteConsoleOutputCharacter(hConsole, screen.data(), nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);

	}

	wchar_t ScreenBuffer::getScreenCharAt(int x, int y) const {
		return screen[y * nScreenWidth + x];
	}

}