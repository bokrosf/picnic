#ifndef GAME_ASSETT_H
#define GAME_ASSETT_H

#include <filesystem>
#include <string>

namespace game::assett
{
    const std::filesystem::path root = std::filesystem::path("assett");
}

namespace game::assett::texture
{
    const std::filesystem::path texture = root / "texture";
    const std::string test = texture / "test.bmp";
}

#endif
