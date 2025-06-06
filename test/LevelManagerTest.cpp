#include "CppUnitTest.h"
#include "../app/LevelManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MusicReadingTrainer;

namespace MusicReadingTrainerTests
{
    TEST_CLASS(LevelManagerTest)
    {
    public:

        TEST_METHOD(TestDefaultLevelIsOne)
        {
            // Tests that the default level is set to 1.

            LevelManager manager;
            Assert::AreEqual(1, manager.getLevel());
        }

        TEST_METHOD(TestSetValidLevel)
        {
            // Tests setting a valid level and retrieving it.

            LevelManager manager;
            manager.setLevel(5);
            Assert::AreEqual(5, manager.getLevel());
        }

        TEST_METHOD(TestSetInvalidLevelDoesNotChange)
        {
            // Tests that setting an invalid level does not change the current level.

            LevelManager manager;
            manager.setLevel(999); // undefined level
            Assert::AreEqual(1, manager.getLevel()); // remains default level 1
        }

        TEST_METHOD(TestGetNotePositionsForCurrentLevelFiltersCorrectly)
        {
            // Tests that getNotePositionsForCurrentLevel correctly filters note positions based on the current level.


            LevelManager manager;
            manager.setLevel(2); // allowed positions: 9, 12, 10

            std::map<NoteName, std::vector<int>> input = {
                { NoteName::C, {9, 11, 12} },
                { NoteName::D, {10, 13} },
                { NoteName::E, {4} } // not allowed for level 2
            };

            auto result = manager.getNotePositionsForCurrentLevel(input);

            Assert::AreEqual(size_t(2), result.size());

            // Check filtered positions for NoteName::C
            Assert::AreEqual(size_t(2), result[NoteName::C].size());
            Assert::AreEqual(9, result[NoteName::C][0]);
            Assert::AreEqual(12, result[NoteName::C][1]);

            // Check filtered positions for NoteName::D
            Assert::AreEqual(size_t(1), result[NoteName::D].size());
            Assert::AreEqual(10, result[NoteName::D][0]);

            // NoteName::E should be excluded since positions are not allowed at level 2
            Assert::IsTrue(result.find(NoteName::E) == result.end());
        }

        TEST_METHOD(TestGetNotePositionsReturnsEmptyWhenNoMatchingPositions)
        {
            // Tests that getNotePositionsForCurrentLevel returns an empty map when no note positions match the current level.


            LevelManager manager;
            manager.setLevel(1); // allowed positions: 9, 12

            std::map<NoteName, std::vector<int>> input = {
                { NoteName::C, {3, 4, 5} }, // none allowed for level 1
                { NoteName::D, {6} }
            };

            auto result = manager.getNotePositionsForCurrentLevel(input);

            Assert::IsTrue(result.empty());
        }

        TEST_METHOD(TestGetNotePositionsIgnoresEmptyNotes)
        {
            // Tests that getNotePositionsForCurrentLevel ignores notes with empty position vectors.

            LevelManager manager;
            manager.setLevel(1); // allowed positions: 9, 12

            std::map<NoteName, std::vector<int>> input = {
                { NoteName::C, {4, 5, 6} }, // none allowed
                { NoteName::D, {} }          // empty vector
            };

            auto result = manager.getNotePositionsForCurrentLevel(input);

            Assert::IsTrue(result.empty());
        }

    };
}