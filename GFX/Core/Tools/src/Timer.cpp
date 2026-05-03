#include "GFX/Core/Tools/include/Timer.h"

namespace GFX::Core
{
    Timer::Timer() { _lastFrameTime = std::chrono::steady_clock::now(); }

    void Timer::update()
    {
        const auto now = std::chrono::steady_clock::now();
        _deltaTime = std::chrono::duration<float>(now - _lastFrameTime).count();
        _lastFrameTime = now;

        if (_deltaTime > 0.1f)
            _deltaTime = 0.1f;
    }

} // namespace gfx2d