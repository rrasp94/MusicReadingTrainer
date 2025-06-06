#include "LevelManager.h"

namespace MusicReadingTrainer {

    LevelManager::LevelManager() {
        initializeLevels();
    }

    void LevelManager::initializeLevels() {
        levelNotePositions = {
            {1, {9, 12}},
            {2, {9, 12, 10}},
            {3, {9, 12, 10, 11}},
            {4, {9, 12, 10, 11, 13}},
            {5, {9, 12, 10, 11, 13, 14}},
            {6, {9, 12, 10, 11, 13, 14, 8}},
            {7, {9, 12, 10, 11, 13, 14, 8, 7}},
            {8, {9, 12, 10, 11, 13, 14, 8, 7, 6}},
            {9, {9, 12, 10, 11, 13, 14, 8, 7, 6, 15}},
            {10, {9, 12, 10, 11, 13, 14, 8, 7, 6, 15, 16}},
            {11, {9, 12, 10, 11, 13, 14, 8, 7, 6, 15, 16, 17}},
            {12, {9, 12, 10, 11, 13, 14, 8, 7, 6, 15, 16, 17, 18}},
            {13, {9, 12, 10, 11, 13, 14, 8, 7, 6, 15, 16, 17, 18, 5}},
            {14, {9, 12, 10, 11, 13, 14, 8, 7, 6, 15, 16, 17, 18, 5, 4}},
            {15, {9, 12, 10, 11, 13, 14, 8, 7, 6, 15, 16, 17, 18, 5, 4, 3}},
            {16, {9, 12, 10, 11, 13, 14, 8, 7, 6, 15, 16, 17, 18, 5, 4, 3, 2}}
        };
    }

    void LevelManager::setLevel(int level) {
        if (levelNotePositions.find(level) != levelNotePositions.end()) {
            currentLevel = level;
        }
    }

    int LevelManager::getLevel() const {
        return currentLevel;
    }

    std::map<NoteName, std::vector<int>> LevelManager::getNotePositionsForCurrentLevel(

        const std::map<NoteName, std::vector<int>>& notePositionsForKey) const
    {
        std::map<NoteName, std::vector<int>> filteredNotes;

        auto levelIt = levelNotePositions.find(currentLevel);
        if (levelIt == levelNotePositions.end()) {
            return filteredNotes;
        }

        const auto& allowedPositions = levelIt->second;

        for (auto noteIt = notePositionsForKey.begin(); noteIt != notePositionsForKey.end(); ++noteIt) {
            const NoteName& noteName = noteIt->first;
            const std::vector<int>& positions = noteIt->second;
            std::vector<int> filteredPositions;

            for (size_t i = 0; i < positions.size(); ++i) {
                int pos = positions[i];
                if (std::find(allowedPositions.begin(), allowedPositions.end(), pos) != allowedPositions.end()) {
                    filteredPositions.push_back(pos);
                }
            }

            if (!filteredPositions.empty()) {
                filteredNotes[noteName] = std::move(filteredPositions);
            }
        }

        return filteredNotes;
    }

}