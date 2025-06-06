#pragma once

#include <map>
#include <vector>
#include "Tonality.h"

namespace MusicReadingTrainer {

    class LevelManager {

    private:
        std::map<int, std::vector<int>> levelNotePositions;
        int currentLevel = 1;

        void initializeLevels();

    public:
        LevelManager();

        void setLevel(int level);
        int getLevel() const;

        std::map<NoteName, std::vector<int>> getNotePositionsForCurrentLevel(
            const std::map<NoteName, std::vector<int>>& notePositionsForKey) const;
    };

}
