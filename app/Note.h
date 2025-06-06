#pragma once

#include <string>
#include "Tonality.h"

namespace MusicReadingTrainer {

    enum class NoteStatus {

        Untouched,
        Correct,
        Incorrect

    };


    class Note {

    public:
        int x = 115;              
        int y = 0;
        NoteName name = NoteName::C;
        NoteStatus status = NoteStatus::Untouched;
        bool wasProcessed = false;

        Note() = default;

        Note(int x, int y, NoteName name);  

        wchar_t getSymbol() const;
    };


}