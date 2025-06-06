#include "ScreenBuffer.h"

#include <algorithm>



namespace MusicReadingTrainer {

	ScreenBuffer::ScreenBuffer() {

		hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole);

		updateConsoleSize();
	}

	ScreenBuffer::~ScreenBuffer() {

		CloseHandle(hConsole);

	}

	void ScreenBuffer::updateConsoleSize() {

		CONSOLE_SCREEN_BUFFER_INFO csbi;

		if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
			nScreenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
			nScreenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
			screen.resize(nScreenWidth * nScreenHeight, L' ');
		}

	}

	void ScreenBuffer::setScreen(int position_x, int position_y, const std::vector<std::wstring>& data) {
		
		updateConsoleSize(); 

		for (int y = 0; y < data.size(); y++) {
			for (int x = 0; x < data[y].size(); x++) {
				int posX = position_x + x;
				int posY = position_y + y;

				if (posX >= 0 && posX < nScreenWidth && posY >= 0 && posY < nScreenHeight) {
					int screen_index = posY * nScreenWidth + posX;
					screen[screen_index] = data[y][x];
				}
			}
		}
	}

	void ScreenBuffer::setCharAt(int x, int y, wchar_t ch) {

		updateConsoleSize(); 
		if (x >= 0 && x < nScreenWidth && y >= 0 && y < nScreenHeight) {
			screen[y * nScreenWidth + x] = ch;
		}
	}

	void ScreenBuffer::clearScreen() {

		updateConsoleSize();
		std::fill(screen.begin(), screen.end(), L' ');

	}

	void ScreenBuffer::renderScreen() {

		updateConsoleSize();
		WriteConsoleOutputCharacter(hConsole, screen.data(), nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);

	}

	wchar_t ScreenBuffer::getScreenCharAt(int x, int y) const {
		return screen[y * nScreenWidth + x];
	}

	int ScreenBuffer::getWidth() const {
		return nScreenWidth;
	}

	int ScreenBuffer::getHeight() const {
		return nScreenHeight;
	}

}