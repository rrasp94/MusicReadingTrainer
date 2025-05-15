#include "CppUnitTest.h"
#include "../app/ScreenBuffer.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MusicReadingTrainer;


namespace MusicReadingTrainerTests 
{
    TEST_CLASS(ScreenBufferTests)
    {
    public:

        TEST_METHOD(TestClearScreen)
        {
            ScreenBuffer screenBuffer;
            screenBuffer.clearScreen();

            for (int i = 0; i < 120 * 30; i++) {
                Assert::AreEqual(screenBuffer.getScreenCharAt(i % 120, i / 120), L' ');
            }
        }

        TEST_METHOD(TestSetScreen)
        {
            ScreenBuffer screenBuffer;
            screenBuffer.clearScreen();
            std::vector<std::wstring> data = { L"Hello", L"World" };
            screenBuffer.setScreen(0, 0, data);

            Assert::AreEqual(screenBuffer.getScreenCharAt(0, 0), L'H');
            Assert::AreEqual(screenBuffer.getScreenCharAt(1, 0), L'e');
            Assert::AreEqual(screenBuffer.getScreenCharAt(0, 1), L'W');
            Assert::AreEqual(screenBuffer.getScreenCharAt(1, 1), L'o');
        }
    };
}
  
        

