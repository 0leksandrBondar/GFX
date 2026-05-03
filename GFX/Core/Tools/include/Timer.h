//
// Created by aleks on 5/1/2026.
//

#ifndef OPENGL_GAME_TIMER_H
#define OPENGL_GAME_TIMER_H
#include "GFX/Core/Window/include/Window.h"

#endif // OPENGL_GAME_TIMER_H
#pragma once

#include <chrono>

namespace GFX::Core
{
    class Timer final : public NonCopyableButMovable
    {
    public:
        Timer();

        void update();

        [[nodiscard]] float getDeltaTime() const { return _deltaTime; }

    private:
        std::chrono::steady_clock::time_point _lastFrameTime{};
        float _deltaTime = 0.0f;
    };
} // namespace GFX::Core