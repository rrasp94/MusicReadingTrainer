#include "CppUnitTest.h"
#include "../app/KeySelectionScreen.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MusicReadingTrainer;

namespace MusicReadingTrainerTests 
{

	TEST_CLASS(KeySelectionScreenTests)
	{
	public:

		TEST_METHOD(InitialSelectedIndexIsZeroAndEnterReturnsC)
		{
			// Checks that the initial selected key is C and pressing Enter confirms it.

			KeySelectionScreen screen;
			Key selected;

			bool confirmed = screen.update({ L'\r' }, selected);

			Assert::IsTrue(confirmed);
			Assert::AreEqual((int)Key::C, (int)selected);
		}

		TEST_METHOD(PressingSMovesSelectionDown)
		{
			// Simulates pressing S to move down to the second key (G) and confirms it.

			KeySelectionScreen screen;
			Key selected;

			screen.update({ L'S' }, selected); // now selectedIndex == 1
			bool confirmed = screen.update({ L'\r' }, selected); // confirm selection

			Assert::IsTrue(confirmed);
			Assert::AreEqual((int)Key::G, (int)selected);
		}

		TEST_METHOD(PressingWOnFirstItemKeepsIndexAtZero)
		{
			// Pressing W at the top of the list should not change the selection; it remains C.

			KeySelectionScreen screen;
			Key selected;

			screen.update({ L'W' }, selected); // already at top
			bool confirmed = screen.update({ L'\r' }, selected); // confirm selection

			Assert::IsTrue(confirmed);
			Assert::AreEqual((int)Key::C, (int)selected);
		}

		TEST_METHOD(PressingWThenSReturnsBackToInitialPosition)
		{
			// Presses S to move down and then W to move back, returning to the initial position C.

			KeySelectionScreen screen;
			Key selected;

			screen.update({ L'S' }, selected); // down to G
			screen.update({ L'W' }, selected); // back to C
			bool confirmed = screen.update({ L'\r' }, selected);

			Assert::IsTrue(confirmed);
			Assert::AreEqual((int)Key::C, (int)selected);
		}

		TEST_METHOD(PressingEnterWithoutMovementStillConfirmsC)
		{
			// Confirms the default key C without any movement.

			KeySelectionScreen screen;
			Key selected;

			bool confirmed = screen.update({ L'\r' }, selected);

			Assert::IsTrue(confirmed);
			Assert::AreEqual((int)Key::C, (int)selected);
		}

		TEST_METHOD(PressingInvalidKeyReturnsFalseAndNoSelection)
		{
			// Presses an invalid key (X), which should not change the selection or confirm anything.

			KeySelectionScreen screen;
			Key selected = Key::E; // start with something not default

			bool result = screen.update({ L'X' }, selected);

			Assert::IsFalse(result);
			// Value should not change
			Assert::AreEqual((int)Key::E, (int)selected);
		}

		TEST_METHOD(CanSelectLastKeyByPressingSEnoughTimes)
		{
			// Presses S repeatedly to reach the last key (F) and confirms it.

			KeySelectionScreen screen;
			Key selected;

			for (int i = 0; i < 11; ++i) {
				screen.update({ L'S' }, selected);
			}

			bool confirmed = screen.update({ L'\r' }, selected);

			Assert::IsTrue(confirmed);
			Assert::AreEqual((int)Key::F, (int)selected);
		}

		TEST_METHOD(PressingSAtBottomDoesNotGoOutOfBounds)
		{
			// Presses S more times than needed and confirms that the selection doesn't go out of bounds (stays at F).

			KeySelectionScreen screen;
			Key selected;

			// go to bottom
			for (int i = 0; i < 20; ++i) {
				screen.update({ L'S' }, selected);
			}

			bool confirmed = screen.update({ L'\r' }, selected);

			Assert::IsTrue(confirmed);
			Assert::AreEqual((int)Key::F, (int)selected); // last key
		}
	};
}