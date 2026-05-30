#include "GFX/Graphics/Graphics/include/Text.h"

#include <utility>

namespace GFX::Graphics
{
    Text::Text(FontPtr font, std::string string) : _font(std::move(font)), _string(std::move(string))
    {
    }
} // namespace GFX::Graphics
