#include "NoteGenerator.h"


namespace MusicReadingTrainer {

    NoteGenerator::NoteGenerator()

        : gen(std::random_device{}()) {

    }

    Note NoteGenerator::generateNote(int startX, const std::map<NoteName, std::vector<int>>& filteredNotes) {

        if (filteredNotes.empty()) {
            return Note();
        }

        std::uniform_int_distribution<> distNote(0, static_cast<int>(filteredNotes.size()) - 1);
        auto it = filteredNotes.begin();
        std::advance(it, distNote(gen));

        NoteName chosenNoteName = it->first;
        const std::vector<int>& possibleYs = it->second;

        if (possibleYs.empty()) {
            return Note(); 
        }

        std::uniform_int_distribution<> distY(0, static_cast<int>(possibleYs.size()) - 1);
        int chosenY = possibleYs[distY(gen)];

        return Note(startX, chosenY, chosenNoteName);
    }

}