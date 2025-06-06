#pragma once

#include <map>
#include <vector>
#include <random>
#include "Note.h"

namespace MusicReadingTrainer {

    class NoteGenerator {

    private:

        std::mt19937 gen;


    public:

        NoteGenerator();

        Note generateNote(int startX, const std::map<NoteName, std::vector<int>>& filteredNotes);

    };

}
