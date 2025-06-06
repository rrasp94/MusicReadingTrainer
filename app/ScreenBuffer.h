#pragma once

#include "windows.h"
#include <vector>
#include <string>


namespace MusicReadingTrainer {

	class ScreenBuffer {

	private:
		int nScreenWidth = 120;
		int nScreenHeight = 30;
		std::vector<wchar_t> screen;
		HANDLE hConsole;
		DWORD dwBytesWritten = 0;

		void updateConsoleSize();

	public:
		ScreenBuffer();
		~ScreenBuffer();

		void setScreen(int position_x, int position_y, const std::vector<std::wstring>& data);
		void setCharAt(int x, int y, wchar_t ch);

		void clearScreen();
		void renderScreen();

		wchar_t getScreenCharAt(int x, int y) const;

		int getWidth() const;
		int getHeight() const;
	};

}
