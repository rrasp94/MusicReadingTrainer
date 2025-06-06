#pragma once

#include "ScreenBuffer.h"
#include <string>
#include <vector>
#include <map>
#include "Note.h"

namespace MusicReadingTrainer {

	class Keyboard {

	private:

		int position_x = 20;
		int position_y = 22;

		std::vector<std::wstring> keyboardLayout;

		std::map<wchar_t, NoteName> keyToNoteSharpMap;
		std::map<wchar_t, NoteName> keyToNoteFlatMap;

		const std::map<wchar_t, NoteName>* currentKeyToNoteMap;

	public:

		Keyboard(bool useFlats = false);

		void updateLayout(const std::vector<wchar_t>& pressedKeys);

		void draw(ScreenBuffer& screenBuffer);

		NoteName getNoteForKey(wchar_t key) const;

		void setUseFlats(bool useFlats);

	};
}
