#include "SoundManager.h"
#include <cmath>


namespace MusicReadingTrainer {

	std::atomic<double> SoundManager::dFrequencyOutput = 0.0;
    std::atomic<bool> SoundManager::running = false;

    SoundManager::SoundManager(bool enableAudio)
        : sound(nullptr), audioEnabled(enableAudio)
    {
        running = true;

        if (audioEnabled) {
            std::vector<std::wstring> devices = olcNoiseMaker<short>::Enumerate();

            if (!devices.empty()) {
                sound = new olcNoiseMaker<short>(devices[0], 44100, 1, 16, 512);
                sound->SetUserFunction(SoundManager::MakeNoise);
            }
            else {
                sound = nullptr;
            }
        }
    }

    SoundManager::~SoundManager() {

        running = false;     

        if (sound) {
            sound->Stop(); 
            delete sound;
            sound = nullptr;
        }
        dFrequencyOutput = 0.0;
    }

    void SoundManager::Start() {

        dFrequencyOutput = 0.0;
        running = true;

    }

    void SoundManager::Stop() {

        dFrequencyOutput = 0.0;
        running = false;
        if (sound)
            sound->Stop();
    }

    void SoundManager::SetKey(wchar_t key) {

        dFrequencyOutput = GetFrequency(key);

    }

    double SoundManager::GetFrequency(wchar_t key) {

        switch (key) {
        case 'Y': return 261.63;
        case 'S': return 277.18;
        case 'X': return 293.66;
        case 'D': return 311.13;
        case 'C': return 329.63;
        case 'V': return 349.23;
        case 'G': return 369.99;
        case 'B': return 392.00;
        case 'H': return 415.30;
        case 'N': return 440.00;
        case 'J': return 466.16;
        case 'M': return 493.88;
        default:  return 0.0;
        }

    }

    double SoundManager::MakeNoise(double dTime) {

        if (!running) return 0.0; 
        double dOutput = sin(dFrequencyOutput * 2.0 * 3.14159 * dTime);
        return dOutput > 0 ? 0.1 : -0.1;

    }

}