#include "ScreenBuffer.h"

#include <algorithm>


namespace MusicReadingTrainer {

	ScreenBuffer::ScreenBuffer() {

		screen = new wchar_t[nScreenWidth * nScreenHeight];
		hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole);

	}

	ScreenBuffer::~ScreenBuffer() {

		delete[] screen;
		CloseHandle(hConsole);

	}

	void ScreenBuffer::setScreen(int position_x, int position_y, int layoutHeight, const wchar_t* const* data) {

		for (int y = 0; y < layoutHeight; y++) {
			for (int x = 0; x < wcslen(data[y]); x++) {
				int screen_index = (position_y + y) * nScreenWidth + (position_x + x);
				screen[screen_index] = data[y][x];
			}
		}

	}

	void ScreenBuffer::clearScreen() {

		for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';

	}

	void ScreenBuffer::renderScreen() {

		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);

	}

	wchar_t ScreenBuffer::getScreenCharAt(int x, int y) const {
		return screen[y * nScreenWidth + x];
	}

}