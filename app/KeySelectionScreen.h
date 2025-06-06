#pragma once
#include "ScreenBuffer.h"
#include "MusicTypes.h"
#include <vector>

namespace MusicReadingTrainer {

    class KeySelectionScreen {
    private:
        std::vector<Key> keys;
        int selectedIndex;

    public:
        KeySelectionScreen();

        
        bool update(const std::vector<wchar_t>& justPressedKeys, Key& selectedKey);

        void draw(ScreenBuffer& screen) const;
    };

}
