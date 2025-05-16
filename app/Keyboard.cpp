#include "Keyboard.h"

namespace MusicReadingTrainer {

    Keyboard::Keyboard() {

        keyboardLayout = {
            L"|   |   | |   |   |   |   | |   | |   |   |",
            L"|   | s | | d |   |   | g | | h | | j |   |",
            L"|   |___| |___|   |   |___| |___| |___|   |",
            L"|     |     |     |     |     |     |     |",
            L"|  y  |  x  |  c  |  v  |  b  |  n  |  m  |",
            L"|_____|_____|_____|_____|_____|_____|_____|"
        };
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

    void Keyboard::draw(ScreenBuffer& renderer) {
        renderer.setScreen(position_x, position_y, keyboardLayout);
    }

}