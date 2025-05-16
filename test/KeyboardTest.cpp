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
            // This test verifies that the keyboard layout remains unchanged
            // when no keys are pressed.

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
            // This test verifies that pressing specific keys (e.g., 's', 'y')
            // causes them to be converted to uppercase in the layout.

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
            // This test verifies that pressing a key that doesn't exist in the layout (e.g., 'z')
            // does not modify the layout.

            Keyboard keyboard;

            std::vector<wchar_t> pressed = { L'z' }; 
            keyboard.updateLayout(pressed);

            ScreenBuffer screenBuffer;
            screenBuffer.clearScreen();
            keyboard.draw(screenBuffer);


            Assert::AreEqual(L's', screenBuffer.getScreenCharAt(26, 23));
        }
    };
}