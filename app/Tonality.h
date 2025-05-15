#pragma once

#include <string>
#include <map>
#include <vector>

#include "ScreenBuffer.h"

namespace MusicReadingTrainer {

	class Tonality {

	private:

		int position_x = 5;
		int position_y = 2;

		std::wstring activeKey = L"Aflat";
		std::map<std::wstring, std::vector<std::wstring>> staves;

		void initializeStaves();

	public:

		Tonality();

		void setActiveKey(const std::wstring& newKey);

		void draw(ScreenBuffer& screenBuffer);

	};

}

