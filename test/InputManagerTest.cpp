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
            // Checks that upon construction, all keys (both general and menu) are initially not pressed.

            InputManager inputManager;

            for (wchar_t key : InputManager::keys) {
                Assert::IsFalse(inputManager.isKeyPressed(key));
                Assert::IsFalse(inputManager.wasKeyPressed(key));
            }
            for (wchar_t key : InputManager::menuKeys) {
                Assert::IsFalse(inputManager.isKeyPressed(key));
                Assert::IsFalse(inputManager.wasKeyPressed(key));
            }
        }

        TEST_METHOD(SetKeyState_UpdatesKeyStateCorrectly)
        {
            // Verifies that setting a key state to pressed and released updates current and previous states accordingly.

            InputManager inputManager;

            inputManager.setKeyState(L'C', true);
            Assert::IsTrue(inputManager.isKeyPressed(L'C'));
            Assert::IsFalse(inputManager.wasKeyPressed(L'C'));

            inputManager.setKeyState(L'C', false);
            Assert::IsFalse(inputManager.isKeyPressed(L'C'));
            Assert::IsTrue(inputManager.wasKeyPressed(L'C'));
        }

        TEST_METHOD(WasKeyJustPressed_ReturnsTrueIfPressedNowButNotBefore)
        {
            // Checks that a key is reported as "just pressed" only on the first press, not while held down.

            InputManager inputManager;

            // Simulate first-time press
            inputManager.setKeyState(L'V', true);
            Assert::IsTrue(inputManager.wasKeyJustPressed(L'V'));

            // Hold the key (not just pressed anymore)
            inputManager.setKeyState(L'V', true);
            Assert::IsFalse(inputManager.wasKeyJustPressed(L'V'));

            // Release and press again
            inputManager.setKeyState(L'V', false);
            inputManager.setKeyState(L'V', true);
            Assert::IsTrue(inputManager.wasKeyJustPressed(L'V'));
        }

        TEST_METHOD(GetPressedKeys_ReturnsAllCurrentlyPressedKeys)
        {
            // Confirms that all currently pressed keys are returned (converted to lowercase).


            InputManager inputManager;

            inputManager.setKeyState(L'G', true);
            inputManager.setKeyState(L'B', true);

            std::vector<wchar_t> pressed = inputManager.getPressedKeys();

            Assert::AreEqual((size_t)2, pressed.size());
            Assert::IsTrue(std::find(pressed.begin(), pressed.end(), L'g') != pressed.end());
            Assert::IsTrue(std::find(pressed.begin(), pressed.end(), L'b') != pressed.end());
        }

        TEST_METHOD(GetJustPressedKeys_ReturnsOnlyJustPressedKeys)
        {
            // Returns only keys that were just pressed (not held down from previous frame).

            InputManager inputManager;

            inputManager.setKeyState(L'X', true);
            std::vector<wchar_t> justPressed = inputManager.getJustPressedKeys();

            Assert::AreEqual((size_t)1, justPressed.size());
            Assert::AreEqual(L'x', justPressed[0]);

            // Key is still held
            inputManager.setKeyState(L'X', true);
            justPressed = inputManager.getJustPressedKeys();
            Assert::IsTrue(justPressed.empty());
        }

        TEST_METHOD(GetJustPressedKeysForMenu_ReturnsOnlyMenuKeys)
        {
            // Returns just pressed keys that are part of the menu keys.

            InputManager inputManager;

            inputManager.setKeyState(L'W', true);
            std::vector<wchar_t> justPressed = inputManager.getJustPressedKeysForMenu();

            Assert::AreEqual((size_t)1, justPressed.size());
            Assert::AreEqual(L'W', justPressed[0]);
        }

        TEST_METHOD(GetJustPressedKeysForGameplay_ReturnsOnlyGameplayKeys)
        {
            // Returns just pressed keys relevant to gameplay, even if some keys overlap with menu keys.

            InputManager inputManager;

            inputManager.setKeyState(L'Y', true);
            inputManager.setKeyState(L'S', true); // Appears both in gameplay and menu, test conflict

            std::vector<wchar_t> justPressed = inputManager.getJustPressedKeysForGameplay();

            Assert::AreEqual((size_t)2, justPressed.size());
            Assert::IsTrue(std::find(justPressed.begin(), justPressed.end(), L'y') != justPressed.end());
            Assert::IsTrue(std::find(justPressed.begin(), justPressed.end(), L's') != justPressed.end());
        }

    };
}