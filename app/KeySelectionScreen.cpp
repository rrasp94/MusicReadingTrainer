#include "KeySelectionScreen.h"

namespace MusicReadingTrainer {

    KeySelectionScreen::KeySelectionScreen()
        : selectedIndex(0)
    {
        keys = {
            Key::C, Key::G, Key::D, Key::A, Key::E, Key::B,
            Key::Gflat, Key::Dflat, Key::Aflat, Key::Eflat, Key::Bflat, Key::F
        };
    }

    bool KeySelectionScreen::update(const std::vector<wchar_t>& justPressedKeys, Key& selectedKey) {
    for (auto key : justPressedKeys) {
        wchar_t k = towupper(key);

        switch (k) { 
        case L'W': // gore
            if (selectedIndex > 0) --selectedIndex;
            break;
        case L'S': // dolje
            if (selectedIndex < (int)keys.size() - 1) ++selectedIndex;
            break;
        case L'\r': // Enter
            selectedKey = keys[selectedIndex];
            return true;
        default:
            break;
        }
    }
    return false;
}

    void KeySelectionScreen::draw(ScreenBuffer& screen) const {
        int startX = 60;
        int arrowX = 58;
        int startY = 9;

        for (int i = 0; i < (int)keys.size(); ++i) {
            int y = startY + i;
            screen.setCharAt(arrowX, y, L' ');  
        }

        for (int i = 0; i < (int)keys.size(); ++i) {
            int y = startY + i;

            std::wstring keyStr;
            switch (keys[i]) {
            case Key::C: keyStr = L"C"; break;
            case Key::G: keyStr = L"G"; break;
            case Key::D: keyStr = L"D"; break;
            case Key::A: keyStr = L"A"; break;
            case Key::E: keyStr = L"E"; break;
            case Key::B: keyStr = L"B"; break;
            case Key::Gflat: keyStr = L"Gb"; break;
            case Key::Dflat: keyStr = L"Db"; break;
            case Key::Aflat: keyStr = L"Ab"; break;
            case Key::Eflat: keyStr = L"Eb"; break;
            case Key::Bflat: keyStr = L"Bb"; break;
            case Key::F: keyStr = L"F"; break;
            }

            if (i == selectedIndex) {
                screen.setCharAt(arrowX, y, L'>');
            }

            for (size_t j = 0; j < keyStr.size(); ++j) {
                screen.setCharAt(startX + (int)j, y, keyStr[j]);
            }
        }
    }

}