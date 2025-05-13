#pragma once

#include <string>
#include <map>
#include <vector>

#include "Renderer.h"
#include "ScreenBuffer.h"

namespace MusicReadingTrainer {

	class Tonality {

	private:

		int position_x = 5;
		int position_y = 2;
		int layoutHeight = 17;

		std::wstring activeKey = L"Aflat";
		std::map<std::wstring, const wchar_t**> staves;

		void initializeStaves();

	public:

		Tonality();

		void setActiveKey(const std::wstring& newKey);

		void draw(Renderer& renderer);

	};

}

