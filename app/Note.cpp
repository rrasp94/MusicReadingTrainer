#include "Note.h"

namespace MusicReadingTrainer {


    Note::Note(int x, int y, NoteName name)
        : x(x), y(y), name(name), status(NoteStatus::Untouched), wasProcessed(false) {
    }



    wchar_t Note::getSymbol() const {

        switch (status) {
        case NoteStatus::Correct:
            return L'@';
        case NoteStatus::Incorrect:
            return L'X';
        case NoteStatus::Untouched:
        default:
            return L'O';
        }
    }

}