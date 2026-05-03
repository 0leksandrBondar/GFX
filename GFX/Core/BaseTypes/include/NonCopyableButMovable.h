#pragma once

namespace GFX::Core
{
    class NonCopyableButMovable
    {
    public:
        NonCopyableButMovable(const NonCopyableButMovable&) = delete;
        NonCopyableButMovable& operator=(const NonCopyableButMovable&) = delete;

    protected:
        NonCopyableButMovable() = default;
        ~NonCopyableButMovable() = default;

        NonCopyableButMovable(NonCopyableButMovable&&) = default;
        NonCopyableButMovable& operator=(NonCopyableButMovable&&) = default;
    };
} // namespace GFX::Core