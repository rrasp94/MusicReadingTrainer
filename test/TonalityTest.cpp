#include "CppUnitTest.h"
#include "../app/Tonality.h"
#include "../app/Renderer.h"
#include "../app/ScreenBuffer.h"

#include <cwchar>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MusicReadingTrainer;


class MockRenderer : public Renderer {
public:
    int callCount = 0;
    int lastX = -1;
    int lastY = -1;
    int lastHeight = -1;
    const wchar_t* const* lastData = nullptr;

    void setScreen(int position_x, int position_y, int layoutHeight, const wchar_t* const* data) override {
        callCount++;
        lastX = position_x;
        lastY = position_y;
        lastHeight = layoutHeight;
        lastData = data;
    }
};

namespace MusicReadingTrainerTests 
{
    TEST_CLASS(TonalityTests)
    {
    public:

        TEST_METHOD(TestTonalityDrawsCorrectDataForAflat)
        {

            Tonality tonality;
            MockRenderer mockRenderer;

            tonality.setActiveKey(L"Aflat");

            const wchar_t* expectedData[] = {
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


            tonality.draw(mockRenderer);


            Assert::AreEqual(17, mockRenderer.lastHeight);
            for (int i = 0; i < 17; ++i) {
                Assert::AreEqual(0, wcscmp(expectedData[i], mockRenderer.lastData[i]));
            }
        }


        TEST_METHOD(TestTonalityDraw)
        {

            Tonality tonality;
            MockRenderer mockRenderer;

            tonality.draw(mockRenderer);

            Assert::AreEqual(1, mockRenderer.callCount);
            Assert::AreEqual(5, mockRenderer.lastX);
            Assert::AreEqual(2, mockRenderer.lastY);
            Assert::AreEqual(17, mockRenderer.lastHeight);

            Assert::IsNotNull(mockRenderer.lastData);

            std::wstring line = mockRenderer.lastData[4];
            Assert::IsTrue(line.find(L"---") != std::wstring::npos);

        }
    };
}

    
        
