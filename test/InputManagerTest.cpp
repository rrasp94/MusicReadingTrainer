#include "CppUnitTest.h"
#define TESTING
#include "../app/InputManager.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MusicReadingTrainer;

namespace MusicReadingTrainerTests
{
    TEST_CLASS(InputManagerTest)
    {
    public:

        
        TEST_METHOD(Constructor_InitializesKeyStatesToFalse)
        {
            // Tests that all keys are initialized to false (not pressed)
            InputManager inputManager;

            for (wchar_t key : InputManager::keys) {
                Assert::IsFalse(inputManager.isKeyPressed(key));
                Assert::IsFalse(inputManager.wasKeyPressed(key));
            }
        }
        TEST_METHOD(SetKeyState_UpdatesKeyStateCorrectly)
        {
            // Tests manual key state assignment using setKeyState

            InputManager inputManager;

            inputManager.setKeyState(L'C', true);  // simulate pressing 'C'
            Assert::IsTrue(inputManager.isKeyPressed(L'C'));
            Assert::IsFalse(inputManager.wasKeyPressed(L'C'));

            inputManager.setKeyState(L'C', false);  // simulate releasing 'C'
            Assert::IsFalse(inputManager.isKeyPressed(L'C'));
            Assert::IsTrue(inputManager.wasKeyPressed(L'C'));
        }
        TEST_METHOD(WasKeyJustPressed_ReturnsTrueIfPressedNowButNotBefore)
        {
            // Tests wasKeyJustPressed logic (key is pressed now but wasn't before)

            InputManager inputManager;

            inputManager.setKeyState(L'V', true);  // simulate just pressed
            Assert::IsTrue(inputManager.wasKeyJustPressed(L'V'));

            inputManager.setKeyState(L'V', true);  // still pressed, not "just" pressed
            Assert::IsFalse(inputManager.wasKeyJustPressed(L'V'));

            inputManager.setKeyState(L'V', false); // simulate release
            inputManager.setKeyState(L'V', true);  // simulate new press
            Assert::IsTrue(inputManager.wasKeyJustPressed(L'V'));
        }
        TEST_METHOD(GetPressedKeys_ReturnsAllCurrentlyPressedKeys)
        {
            // Tests that getPressedKeys returns only currently pressed keys

            InputManager inputManager;

            inputManager.setKeyState(L'G', true);  // simulate pressing 'G'
            inputManager.setKeyState(L'B', true);  // simulate pressing 'B'

            std::vector<wchar_t> pressed = inputManager.getPressedKeys();

            Assert::AreEqual((size_t)2, pressed.size());
            Assert::IsTrue(std::find(pressed.begin(), pressed.end(), L'g') != pressed.end());
            Assert::IsTrue(std::find(pressed.begin(), pressed.end(), L'b') != pressed.end());
        }
    };
}