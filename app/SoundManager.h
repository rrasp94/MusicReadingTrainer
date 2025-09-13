#pragma once
#include <atomic>
#include "olcNoiseMaker.h"

namespace MusicReadingTrainer {

    class SoundManager {

    private:

        olcNoiseMaker<short>* sound;
        bool audioEnabled;
        static std::atomic<bool> running;

    public:

        SoundManager(bool enableAudio = true);
        ~SoundManager();

        void Start();
        void Stop();
        void SetKey(wchar_t key);

        double GetFrequency(wchar_t key);
        static double MakeNoise(double dTime);

        static void SetRunning(bool value) { running = value; }

        static std::atomic<double> dFrequencyOutput;

    };

}
