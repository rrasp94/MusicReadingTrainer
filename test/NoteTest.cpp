#include "CppUnitTest.h"
#include "../app/Note.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MusicReadingTrainer;

namespace MusicReadingTrainerTests
{
    TEST_CLASS(NoteTest)
    {
    public:

        TEST_METHOD(TestDefaultConstructor)
        {
            // Tests that the default constructor initializes Note with expected default values.

            Note note;
            Assert::AreEqual(115, note.x);
            Assert::AreEqual(0, note.y);
            Assert::AreEqual((int)NoteName::C, (int)note.name);
            Assert::AreEqual((int)NoteStatus::Untouched, (int)note.status);
            Assert::IsFalse(note.wasProcessed);
        }

        TEST_METHOD(TestParameterizedConstructor)
        {
            // Tests that the parameterized constructor correctly sets position and note name, with default status and processed flag.

            Note note(50, 10, NoteName::E);
            Assert::AreEqual(50, note.x);
            Assert::AreEqual(10, note.y);
            Assert::AreEqual((int)NoteName::E, (int)note.name);
            Assert::AreEqual((int)NoteStatus::Untouched, (int)note.status);
            Assert::IsFalse(note.wasProcessed);
        }

        TEST_METHOD(TestGetSymbol_Untouched)
        {
            // Tests that getSymbol returns 'O' when Note status is Untouched.

            Note note;
            note.status = NoteStatus::Untouched;
            Assert::AreEqual(L'O', note.getSymbol());
        }

        TEST_METHOD(TestGetSymbol_Correct)
        {
            // Tests that getSymbol returns '@' when Note status is Correct.

            Note note;
            note.status = NoteStatus::Correct;
            Assert::AreEqual(L'@', note.getSymbol());
        }

        TEST_METHOD(TestGetSymbol_Incorrect)
        {
            // Tests that getSymbol returns 'X' when Note status is Incorrect.

            Note note;
            note.status = NoteStatus::Incorrect;
            Assert::AreEqual(L'X', note.getSymbol());
        }
    };
}