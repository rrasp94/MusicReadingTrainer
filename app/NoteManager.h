#pragma once

#include <vector>
#include "Note.h"
#include "ScreenBuffer.h"


namespace MusicReadingTrainer {

	class NoteManager {

	private:

		std::vector<Note> notes;


	public:

		void addNote(const Note& note);

		void updateNotes();

		void removeOffscreenNotes();

		const std::vector<Note>& getNotes() const;

		std::vector<Note>& getNotes();

		void drawNotes(ScreenBuffer& screen);

		bool shouldGenerateNewNote(int distance = 25) const;

		int getFirstActiveNoteIndex() const;

		void drawArrowAboveActiveNote(ScreenBuffer& screen) const;

		void clearNotes();

	};

}
