#include "CppUnitTest.h"
#include "../app/Keyboard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MusicReadingTrainer;

namespace MusicReadingTrainerTests
{
    TEST_CLASS(KeyboardTest)
    {
    public:

        TEST_METHOD(TestKeyboardInitialLayoutUnchanged)
        {
            // Verifies that the keyboard layout remains unchanged if no keys are pressed.

            Keyboard keyboard;

            std::vector<wchar_t> emptyKeys;
            keyboard.updateLayout(emptyKeys);

            ScreenBuffer screenBuffer;
            screenBuffer.clearScreen();
            keyboard.draw(screenBuffer);

            wchar_t ch = screenBuffer.getScreenCharAt(26, 23);
            Assert::AreEqual(L's', ch);
        }

        TEST_METHOD(TestKeyboardKeyHighlight)
        {
            // Verifies that pressing specific keys (e.g., 's', 'y') highlights them by converting to uppercase.

            Keyboard keyboard;

            std::vector<wchar_t> pressed = { L's', L'y' };
            keyboard.updateLayout(pressed);

            ScreenBuffer screenBuffer;
            screenBuffer.clearScreen();
            keyboard.draw(screenBuffer);

            Assert::AreEqual(L'S', screenBuffer.getScreenCharAt(26, 23));
            Assert::AreEqual(L'Y', screenBuffer.getScreenCharAt(23, 26));
        }

        TEST_METHOD(TestKeyboardNoMatchDoesNothing)
        {
            // Verifies that pressing a non-existent key (e.g., 'z') does not change the layout.

            Keyboard keyboard;

            std::vector<wchar_t> pressed = { L'z' };
            keyboard.updateLayout(pressed);

            ScreenBuffer screenBuffer;
            screenBuffer.clearScreen();
            keyboard.draw(screenBuffer);

            Assert::AreEqual(L's', screenBuffer.getScreenCharAt(26, 23));
        }

        TEST_METHOD(TestGetNoteForKeySharp)
        {
            // Tests the note mapping when using sharps.

            Keyboard keyboard(false); // false means use sharps

            Assert::AreEqual((int)NoteName::C, (int)keyboard.getNoteForKey(L'y'));
            Assert::AreEqual((int)NoteName::Csharp, (int)keyboard.getNoteForKey(L's'));
            Assert::AreEqual((int)NoteName::Asharp, (int)keyboard.getNoteForKey(L'j'));
        }

        TEST_METHOD(TestGetNoteForKeyFlat)
        {
            // Tests the note mapping when using flats.

            Keyboard keyboard(true); // true means use flats

            Assert::AreEqual((int)NoteName::C, (int)keyboard.getNoteForKey(L'y'));
            Assert::AreEqual((int)NoteName::Dflat, (int)keyboard.getNoteForKey(L's'));
            Assert::AreEqual((int)NoteName::Bflat, (int)keyboard.getNoteForKey(L'j'));
        }

        TEST_METHOD(TestSwitchBetweenSharpAndFlat)
        {
            // Tests switching between sharp and flat modes.

            Keyboard keyboard;

            keyboard.setUseFlats(true);
            Assert::AreEqual((int)NoteName::Eflat, (int)keyboard.getNoteForKey(L'd'));

            keyboard.setUseFlats(false);
            Assert::AreEqual((int)NoteName::Dsharp, (int)keyboard.getNoteForKey(L'd'));
        }
    };
}