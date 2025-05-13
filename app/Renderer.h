#pragma once

namespace MusicReadingTrainer {

    class Renderer {
    public:
        virtual void setScreen(int position_x, int position_y, int layoutHeight, const wchar_t* const* data) = 0;
        virtual ~Renderer() = default;
    };

}

