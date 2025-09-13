#include "CppUnitTest.h"
#include "../app/SoundManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MusicReadingTrainer;

namespace MusicReadingTrainerTests
{
    TEST_CLASS(SoundManagerTest)
    {
    public:

        TEST_METHOD(GetFrequency_ReturnsCorrectValues)
        {
            // Tests that GetFrequency returns correct values for specific keys, and 0.0 for an invalid key.

            try {
                SoundManager soundManager(false); // audio off

                Assert::AreEqual(261.63, soundManager.GetFrequency(L'Y'), 0.01);
                Assert::AreEqual(277.18, soundManager.GetFrequency(L'S'), 0.01);
                Assert::AreEqual(440.00, soundManager.GetFrequency(L'N'), 0.01);
                Assert::AreEqual(0.0, soundManager.GetFrequency(L'Z'), 0.01);
            }
            catch (...) {
                Assert::Fail(L"Exception thrown in GetFrequency_ReturnsCorrectValues");
            }
        }

        TEST_METHOD(SetKey_SetsCorrectFrequency)
        {
            // Tests that SetKey updates the global frequency to the correct value for each key.

            try {
                SoundManager soundManager(false); // audio off

                soundManager.SetKey(L'C');
                Assert::AreEqual(329.63, SoundManager::dFrequencyOutput.load(), 0.01);

                soundManager.SetKey(L'X');
                Assert::AreEqual(293.66, SoundManager::dFrequencyOutput.load(), 0.01);
            }
            catch (...) {
                Assert::Fail(L"Exception thrown in SetKey_SetsCorrectFrequency");
            }
        }

        TEST_METHOD(Start_ResetsFrequency)
        {
            // Tests that calling Start resets the global frequency output to 0.0.

            try {
                SoundManager soundManager(false); // audio off
                SoundManager::dFrequencyOutput = 500.0;

                soundManager.Start();
                Assert::AreEqual(0.0, SoundManager::dFrequencyOutput.load(), 0.01);
            }
            catch (...) {
                Assert::Fail(L"Exception thrown in Start_ResetsFrequency");
            }
        }

        TEST_METHOD(Stop_AlsoResetsFrequency)
        {
            // Tests that calling Stop also resets the global frequency output to 0.0.

            try {
                SoundManager soundManager(false); // audio off
                SoundManager::dFrequencyOutput = 500.0;

                soundManager.Stop();
                Assert::AreEqual(0.0, SoundManager::dFrequencyOutput.load(), 0.01);
            }
            catch (...) {
                Assert::Fail(L"Exception thrown in Stop_AlsoResetsFrequency");
            }
        }

        TEST_METHOD(MakeNoise_ProducesCorrectWaveform)
        {
            // Tests that MakeNoise produces either +0.1 or -0.1 waveform sample for a given time and frequency.

            try {
                SoundManager::SetRunning(true);
                SoundManager::dFrequencyOutput = 440.0;

                double dTime = 0.0;
                double sample = SoundManager::MakeNoise(dTime);
                Assert::IsTrue(sample == 0.1 || sample == -0.1);
            }
            catch (...) {
                Assert::Fail(L"Exception thrown in MakeNoise_ProducesCorrectWaveform");
            }
        }

    };
}