#pragma once

#include <string>
#include <map>
#include <vector>

#include "ScreenBuffer.h"
#include "MusicTypes.h"

namespace MusicReadingTrainer {

	class Tonality {

	private:

		int position_x = 5;
		int position_y = 2;

		std::map<Key, std::vector<std::wstring>> staves;

		std::map<Key, std::map<NoteName, std::vector<int>>> notePositions;

		void initializeStaves();
		void initializeNotePositions();

	public:

		Tonality();

		void draw(ScreenBuffer& screenBuffer, Key key);

		const std::map<NoteName, std::vector<int>>& getNotePositionsForKey(Key key) const;

		bool isFlatKey(Key key) const;

	};

}

