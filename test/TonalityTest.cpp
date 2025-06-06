#include "CppUnitTest.h"
#include "../app/Tonality.h"
#include "../app/ScreenBuffer.h"

#include <cwchar>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MusicReadingTrainer;

namespace MusicReadingTrainerTests 
{
    TEST_CLASS(TonalityTests)
    {
    public:

        TEST_METHOD(TestTonalityDrawsCorrectDataForAflat)
        {

            // Verifies full staff lines for "Aflat" key are drawn correctly.

            Tonality tonality;
            Key key = Key::Aflat;

            ScreenBuffer screenBuffer;
            screenBuffer.clearScreen();

            tonality.draw(screenBuffer, key);

            std::vector<std::wstring> expectedData = {
                L"                   |                                                                                           ",
                L"                   |                                                                                           ",
                L"                   |                                                                                           ",
                L"                   |                                                                                           ",
                L"-------------------|-------------------------------------------------------------------------------------------",
                L" b                 |                                                                                           ",
                L"---b---------------|-------------------------------------------------------------------------------------------",
                L"                   |                                                                                           ",
                L"b------------------|-------------------------------------------------------------------------------------------",
                L"  b                |                                                                                           ",
                L"-------------------|-------------------------------------------------------------------------------------------",
                L"                   |                                                                                           ",
                L"-------------------|-------------------------------------------------------------------------------------------",
                L"                   |                                                                                           ",
                L"                   |                                                                                           ",
                L"                   |                                                                                           ",
                L"                   |                                                                                           ",
            };

            const int position_x = 5;
            const int position_y = 2;

            std::vector<std::wstring> actualData;
            for (int y = 0; y < (int)expectedData.size(); ++y) {
                std::wstring line;
                for (int x = 0; x < (int)expectedData[y].length(); ++x) {
                    line += screenBuffer.getScreenCharAt(position_x + x, position_y + y);
                }
                actualData.push_back(line);
            }

            Assert::AreEqual((int)expectedData.size(), (int)actualData.size());

            for (int i = 0; i < (int)expectedData.size(); ++i) {
                Assert::AreEqual(expectedData[i], actualData[i]);
            }
        }

        TEST_METHOD(TestTonalityDraw)
        {
            // Checks that staff lines contain the expected "---" pattern.

            Tonality tonality;

            ScreenBuffer screenBuffer;
            screenBuffer.clearScreen();

            tonality.draw(screenBuffer, Key::C);

            const int position_x = 5;  
            const int position_y = 2;  

            int lineIndex = 4;

            std::wstring line;
 
            for (int x = position_x; x < 120; ++x) {
                line += screenBuffer.getScreenCharAt(x, position_y + lineIndex);
            }

            Assert::IsTrue(line.find(L"---") != std::wstring::npos, L"Line does not contain expected '---' pattern");
        }
    };
}

    
        
