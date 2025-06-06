#include "Keyboard.h"
#include <cwctype>

namespace MusicReadingTrainer {

    Keyboard::Keyboard(bool useFlats) {

        keyboardLayout = {
            L"|   |   | |   |   |   |   | |   | |   |   |",
            L"|   | s | | d |   |   | g | | h | | j |   |",
            L"|   |___| |___|   |   |___| |___| |___|   |",
            L"|     |     |     |     |     |     |     |",
            L"|  y  |  x  |  c  |  v  |  b  |  n  |  m  |",
            L"|_____|_____|_____|_____|_____|_____|_____|"
        };

        keyToNoteSharpMap = {
            {L'Y', NoteName::C},
            {L'S', NoteName::Csharp},
            {L'X', NoteName::D},
            {L'D', NoteName::Dsharp},
            {L'C', NoteName::E},
            {L'V', NoteName::F},
            {L'G', NoteName::Fsharp},
            {L'B', NoteName::G},
            {L'H', NoteName::Gsharp},
            {L'N', NoteName::A},
            {L'J', NoteName::Asharp},
            {L'M', NoteName::B}
        };

        keyToNoteFlatMap = {
            {L'Y', NoteName::C},
            {L'S', NoteName::Dflat},
            {L'X', NoteName::D},
            {L'D', NoteName::Eflat},
            {L'C', NoteName::E},
            {L'V', NoteName::F},
            {L'G', NoteName::Gflat},
            {L'B', NoteName::G},
            {L'H', NoteName::Aflat},
            {L'N', NoteName::A},
            {L'J', NoteName::Bflat},
            {L'M', NoteName::B}
        };

        currentKeyToNoteMap = useFlats ? &keyToNoteFlatMap : &keyToNoteSharpMap;
    }

    void Keyboard::setUseFlats(bool useFlats) {
        currentKeyToNoteMap = useFlats ? &keyToNoteFlatMap : &keyToNoteSharpMap;
    }

    NoteName Keyboard::getNoteForKey(wchar_t key) const {
        wchar_t upKey = towupper(key);
        auto it = currentKeyToNoteMap->find(upKey);
        return it->second;
    }

    void Keyboard::updateLayout(const std::vector<wchar_t>& pressedKeys) {

        std::vector<std::wstring> originalLayout = {
            L"|   |   | |   |   |   |   | |   | |   |   |",
            L"|   | s | | d |   |   | g | | h | | j |   |",
            L"|   |___| |___|   |   |___| |___| |___|   |",
            L"|     |     |     |     |     |     |     |",
            L"|  y  |  x  |  c  |  v  |  b  |  n  |  m  |",
            L"|_____|_____|_____|_____|_____|_____|_____|"
        };

        keyboardLayout = originalLayout;

        for (wchar_t key : pressedKeys) {
            for (int y : {1, 4}) {
                for (int x = 0; x < keyboardLayout[y].size(); ++x) {
                    if (keyboardLayout[y][x] == key) {
                        keyboardLayout[y][x] = towupper(key);
                    }
                }
            }
        }

    }

    void Keyboard::draw(ScreenBuffer& screenBuffer) {

        screenBuffer.setScreen(position_x, position_y, keyboardLayout);

    }

}