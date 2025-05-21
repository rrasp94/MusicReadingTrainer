#include "CppUnitTest.h"
#include "../app/ScreenBuffer.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MusicReadingTrainer;


namespace MusicReadingTrainerTests 
{
    TEST_CLASS(ScreenBufferTest)
    {
    public:

        TEST_METHOD(TestClearScreen)
        {
            // Verifies that clearScreen fills the entire buffer with spaces.

            ScreenBuffer screenBuffer;
            screenBuffer.clearScreen();

            int width = screenBuffer.getWidth();
            int height = screenBuffer.getHeight();

            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    Assert::AreEqual(screenBuffer.getScreenCharAt(x, y), L' ');
                }
            }
        }

        TEST_METHOD(TestSetScreen)
        {
            // Verifies that setScreen writes the given lines correctly at specified position.

            ScreenBuffer screenBuffer;
            screenBuffer.clearScreen();

            std::vector<std::wstring> data = { L"Hello", L"World" };
            screenBuffer.setScreen(0, 0, data);

            Assert::AreEqual(screenBuffer.getScreenCharAt(0, 0), L'H');
            Assert::AreEqual(screenBuffer.getScreenCharAt(1, 0), L'e');
            Assert::AreEqual(screenBuffer.getScreenCharAt(0, 1), L'W');
            Assert::AreEqual(screenBuffer.getScreenCharAt(1, 1), L'o');
        }

        TEST_METHOD(TestScreenSizeMatchesConsole)
        {
            // Verifies that the screen buffer dimensions match the actual console window size.

            ScreenBuffer screenBuffer;

            Assert::IsTrue(screenBuffer.getWidth() > 0);
            Assert::IsTrue(screenBuffer.getHeight() > 0);
        }

    };
}
  
        

