#include "CppUnitTest.h"
#include "../app/ScoreManager.h"
#include "../app/ScreenBuffer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MusicReadingTrainer;

namespace MusicReadingTrainerTests
{
    TEST_CLASS(ScoreManagerTest)
    {
    public:
        TEST_METHOD(TestScoreManagerConstructorInitializesStatusLine)
        {
            // This test verifies that the ScoreManager constructor initializes
            // the statusLine with the correct default values.

            ScoreManager scoreManager;

            ScreenBuffer screenBuffer;
            screenBuffer.clearScreen();

            scoreManager.draw(screenBuffer);

            std::wstring actualLine;
            for (int x = 5; x < 120; ++x) {
                wchar_t ch = screenBuffer.getScreenCharAt(x, 0);
                if (ch == L'\0') break;
                actualLine += ch;
            }

            actualLine.erase(actualLine.find_last_not_of(L' ') + 1);

            Assert::IsTrue(actualLine.find(L"Level:  1") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Correct:   0") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Incorrect:   0") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Accuracy:   0%") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Streak:   0") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Max streak:   0") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Level-up:  0 / 10") != std::wstring::npos);
        }
        TEST_METHOD(TestScoreManagerDrawWritesStatusLineToScreenBuffer)
        {
            // This test verifies that the draw() method correctly writes
            // the statusLine to the ScreenBuffer at the expected coordinates.

            ScoreManager scoreManager;

            ScreenBuffer screenBuffer;
            screenBuffer.clearScreen();

            scoreManager.draw(screenBuffer);

            std::wstring drawnLine;
            for (int x = 5; x < 120; ++x) {
                wchar_t ch = screenBuffer.getScreenCharAt(x, 0);
                if (ch == L'\0') break;
                drawnLine += ch;
            }

            drawnLine.erase(drawnLine.find_last_not_of(L' ') + 1);

            Assert::IsTrue(drawnLine.find(L"Level:  1") != std::wstring::npos);
            Assert::IsTrue(drawnLine.find(L"Accuracy:   0%") != std::wstring::npos);
        }

        TEST_METHOD(TestAddCorrectAnswerIncreasesValues)
        {
            // Tests that adding a correct answer increments correct count, streak, and level-up progress.

            ScoreManager scoreManager;
            scoreManager.addCorrectAnswer();

            ScreenBuffer screenBuffer;
            scoreManager.draw(screenBuffer);

            std::wstring actualLine;
            for (int x = 5; x < 120; ++x) {
                wchar_t ch = screenBuffer.getScreenCharAt(x, 0);
                if (ch == L'\0') break;
                actualLine += ch;
            }
            actualLine.erase(actualLine.find_last_not_of(L' ') + 1);

            Assert::IsTrue(actualLine.find(L"Correct:   1") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Streak:   1") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Level-up:  1 / 10") != std::wstring::npos);
        }

        TEST_METHOD(TestAddIncorrectAnswerResetsStreakAndIncreasesIncorrect)
        {
            // Tests that adding an incorrect answer resets the streak, increases incorrect count, and resets level-up progress.

            ScoreManager scoreManager;
            scoreManager.addCorrectAnswer(); // build some streak
            scoreManager.addCorrectAnswer();
            scoreManager.addIncorrectAnswer();

            ScreenBuffer screenBuffer;
            scoreManager.draw(screenBuffer);

            std::wstring actualLine;
            for (int x = 5; x < 120; ++x) {
                wchar_t ch = screenBuffer.getScreenCharAt(x, 0);
                if (ch == L'\0') break;
                actualLine += ch;
            }
            actualLine.erase(actualLine.find_last_not_of(L' ') + 1);

            Assert::IsTrue(actualLine.find(L"Incorrect:   1") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Streak:   0") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Level-up:  0 / 10") != std::wstring::npos);
        }

        TEST_METHOD(TestResetSetsEverythingToDefault)
        {
            // Tests that reset method returns all score values (level, correct, incorrect, accuracy, streak, max streak) to their defaults.

            ScoreManager scoreManager;
            for (int i = 0; i < 5; ++i) scoreManager.addCorrectAnswer();
            scoreManager.addIncorrectAnswer();
            scoreManager.reset();

            ScreenBuffer screenBuffer;
            scoreManager.draw(screenBuffer);

            std::wstring actualLine;
            for (int x = 5; x < 120; ++x) {
                wchar_t ch = screenBuffer.getScreenCharAt(x, 0);
                if (ch == L'\0') break;
                actualLine += ch;
            }
            actualLine.erase(actualLine.find_last_not_of(L' ') + 1);

            Assert::IsTrue(actualLine.find(L"Level:  1") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Correct:   0") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Incorrect:   0") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Accuracy:   0%") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Streak:   0") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Max streak:   0") != std::wstring::npos);
        }

        TEST_METHOD(TestLevelIncreasesAfter10CorrectAnswers)
        {
            // Tests that after 10 correct answers the level increases and level-up progress resets.

            ScoreManager scoreManager;
            for (int i = 0; i < 10; ++i) scoreManager.addCorrectAnswer();

            ScreenBuffer screenBuffer;
            scoreManager.draw(screenBuffer);

            std::wstring actualLine;
            for (int x = 5; x < 120; ++x) {
                wchar_t ch = screenBuffer.getScreenCharAt(x, 0);
                if (ch == L'\0') break;
                actualLine += ch;
            }
            actualLine.erase(actualLine.find_last_not_of(L' ') + 1);

            Assert::IsTrue(actualLine.find(L"Level:  2") != std::wstring::npos);
            Assert::IsTrue(actualLine.find(L"Level-up:  0 / 10") != std::wstring::npos);
        }
    };
}