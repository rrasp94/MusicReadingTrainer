#pragma once

#include "windows.h"
#include <vector>
#include <string>


namespace MusicReadingTrainer {

	class ScreenBuffer {

	private:
		const int nScreenWidth = 120;
		const int nScreenHeight = 30;
		std::vector<wchar_t> screen;
		HANDLE hConsole;
		DWORD dwBytesWritten = 0;

	public:
		ScreenBuffer();
		~ScreenBuffer();

		void setScreen(int position_x, int position_y, const std::vector<std::wstring>& data);

		void clearScreen();
		void renderScreen();

		wchar_t getScreenCharAt(int x, int y) const;
	};

}
