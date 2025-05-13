#pragma once

#include "windows.h"
#include "Renderer.h"
#include <vector>


namespace MusicReadingTrainer {

	class ScreenBuffer : public Renderer {

	private:
		const int nScreenWidth = 120;
		const int nScreenHeight = 30;
		wchar_t* screen;
		HANDLE hConsole;
		DWORD dwBytesWritten = 0;

	public:
		ScreenBuffer();
		~ScreenBuffer();

		void setScreen(int position_x, int position_y, int layoutHeight, const wchar_t* const* data);

		void clearScreen();
		void renderScreen();

		wchar_t getScreenCharAt(int x, int y) const;
	};

}
