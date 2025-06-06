#include "CppUnitTest.h"
#include "../app/NoteGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MusicReadingTrainer;

namespace MusicReadingTrainerTests
{
    TEST_CLASS(NoteGeneratorTest)
    {
    public:

        TEST_METHOD(TestGenerateNoteWithEmptyMap)
        {
            // Tests generating a note when the map of notes is empty.
            // Expects the default note at position (115, 0) with name C and Untouched status.

            NoteGenerator generator;
            std::map<NoteName, std::vector<int>> emptyMap;

            Note note = generator.generateNote(100, emptyMap);

            Assert::AreEqual(115, note.x);
            Assert::AreEqual(0, note.y);
            Assert::AreEqual((int)NoteName::C, (int)note.name);
            Assert::AreEqual((int)NoteStatus::Untouched, (int)note.status);
            Assert::IsFalse(note.wasProcessed);
        }

        TEST_METHOD(TestGenerateNoteWithValidMap)
        {
            // Tests generating a note when the map contains valid note names and y-positions.
            // Expects the generated note to have the given x, the correct NoteName, and y chosen from the vector.

            NoteGenerator generator;
            std::map<NoteName, std::vector<int>> notesMap;

            notesMap[NoteName::E] = { 5, 10 };

            Note note = generator.generateNote(100, notesMap);

            Assert::AreEqual(100, note.x);
            Assert::IsTrue(note.name == NoteName::E);
            Assert::IsTrue(note.y == 5 || note.y == 10);
            Assert::AreEqual((int)NoteStatus::Untouched, (int)note.status);
            Assert::IsFalse(note.wasProcessed);
        }

        TEST_METHOD(TestGenerateNoteWithEmptyVectorForNote)
        {
            // Tests generating a note when the map has a note name but an empty vector of y-positions.
            // Expects the default note at position (115, 0) with name C and Untouched status.

            NoteGenerator generator;
            std::map<NoteName, std::vector<int>> notesMap;

            notesMap[NoteName::G] = {};

            Note note = generator.generateNote(100, notesMap);

            Assert::AreEqual(115, note.x);
            Assert::AreEqual(0, note.y);
            Assert::AreEqual((int)NoteName::C, (int)note.name);
            Assert::AreEqual((int)NoteStatus::Untouched, (int)note.status);
            Assert::IsFalse(note.wasProcessed);
        }
    };
}