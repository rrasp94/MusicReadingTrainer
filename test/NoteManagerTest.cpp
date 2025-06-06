#include "CppUnitTest.h"
#include "../app/NoteManager.h"
#include "../app/Note.h"
#include "../app/ScreenBuffer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MusicReadingTrainer;

namespace MusicReadingTrainerTests
{
    TEST_CLASS(NoteManagerTest)
    {
    public:

        TEST_METHOD(TestAddNote)
        {
            // Tests adding a new note to the NoteManager and verifies the note's properties.

            NoteManager manager;
            Note note(100, 10, NoteName::C);

            manager.addNote(note);

            Assert::AreEqual(size_t(1), manager.getNotes().size());
            Assert::AreEqual(100, manager.getNotes()[0].x);
            Assert::AreEqual(10, manager.getNotes()[0].y);
            Assert::AreEqual((int)NoteName::C, (int)manager.getNotes()[0].name);
        }

        TEST_METHOD(TestUpdateNotesMovesLeft)
        {
            // Tests that notes move left after calling updateNotes.

            NoteManager manager;
            manager.addNote(Note(50, 10, NoteName::D));

            manager.updateNotes();

            Assert::AreEqual(49, manager.getNotes()[0].x);
        }

        TEST_METHOD(TestRemoveOffscreenNotes)
        {
            // Tests removal of notes that have moved offscreen (beyond the left boundary).

            NoteManager manager;
            manager.addNote(Note(10, 10, NoteName::E)); // should be removed
            manager.addNote(Note(20, 10, NoteName::F)); // should remain

            manager.removeOffscreenNotes();

            Assert::AreEqual(size_t(1), manager.getNotes().size());
            Assert::AreEqual(20, manager.getNotes()[0].x);
        }

        TEST_METHOD(TestShouldGenerateNewNoteWhenEmpty)
        {
            // Tests that a new note should be generated if the note list is empty.

            NoteManager manager;

            Assert::IsTrue(manager.shouldGenerateNewNote());
        }

        TEST_METHOD(TestShouldGenerateNewNoteWhenFarEnough)
        {
            // Tests that a new note should be generated if the last note is far enough from the spawn position.

            NoteManager manager;
            manager.addNote(Note(80, 10, NoteName::G)); // 115 - 80 = 35 > 25

            Assert::IsTrue(manager.shouldGenerateNewNote(25));
        }

        TEST_METHOD(TestShouldNotGenerateNewNoteWhenTooClose)
        {
            // Tests that a new note should NOT be generated if the last note is too close to the spawn position.

            NoteManager manager;
            manager.addNote(Note(95, 10, NoteName::A)); // 115 - 95 = 20 < 25

            Assert::IsFalse(manager.shouldGenerateNewNote(25));
        }

        TEST_METHOD(TestGetFirstActiveNoteIndex)
        {
            // Tests getting the index of the first active (not processed) note.

            NoteManager manager;
            Note processed(100, 10, NoteName::B);
            processed.wasProcessed = true;

            manager.addNote(processed);
            manager.addNote(Note(101, 10, NoteName::C)); // should be first active

            Assert::AreEqual(1, manager.getFirstActiveNoteIndex());
        }

        TEST_METHOD(TestGetFirstActiveNoteIndexNone)
        {
            // Tests that -1 is returned if there are no active (unprocessed) notes.

            NoteManager manager;
            Note n1(100, 10, NoteName::D);
            n1.wasProcessed = true;
            manager.addNote(n1);

            Assert::AreEqual(-1, manager.getFirstActiveNoteIndex());
        }

        TEST_METHOD(TestClearNotes)
        {
            // Tests that clearNotes removes all notes from the NoteManager.

            NoteManager manager;
            manager.addNote(Note(100, 10, NoteName::E));
            manager.clearNotes();

            Assert::AreEqual(size_t(0), manager.getNotes().size());
        }

        TEST_METHOD(TestDrawArrowAboveActiveNote)
        {
            // Tests drawing an arrow ('v') above the first active note.

            NoteManager manager;
            ScreenBuffer screen;

            Note note(30, 10, NoteName::F); // x > 24
            note.status = NoteStatus::Untouched;

            manager.addNote(note);

            screen.clearScreen();
            manager.drawArrowAboveActiveNote(screen);

            Assert::AreEqual(L'v', screen.getScreenCharAt(30, 9));
        }

        TEST_METHOD(TestDrawNotesSetsCorrectSymbol)
        {
            // Tests that drawing notes outputs the correct symbol based on their status.

            NoteManager manager;
            ScreenBuffer screen;

            Note note(50, 12, NoteName::G);
            note.status = NoteStatus::Correct; // should draw '@'

            manager.addNote(note);
            screen.clearScreen();
            manager.drawNotes(screen);

            Assert::AreEqual(L'@', screen.getScreenCharAt(50, 12));
        }
    };
}