#pragma once

#include <string>
#include <map>
#include <vector>

#include "ScreenBuffer.h"

namespace MusicReadingTrainer {

	enum class Key {
		C, G, D, A, E, B, Gflat, Dflat, Aflat, Eflat, Bflat, F
	};

	class Tonality {

	private:

		int position_x = 5;
		int position_y = 2;

		Key activeKey = Key::Aflat;
		std::map<Key, std::vector<std::wstring>> staves;

		void initializeStaves();

	public:

		Tonality();

		void setActiveKey(Key newKey);

		void draw(ScreenBuffer& screenBuffer);

	};

}

