#ifndef GAME_ASSETT_H
#define GAME_ASSETT_H

#include <filesystem>
#include <string>

namespace game::assett
{
    const std::string root = std::filesystem::path("assett").string();
}

namespace game::assett::texture
{
    const std::string texture = std::filesystem::path(root).append("texture");
    const std::string test = std::filesystem::path(texture).append("test.bmp");
}

#endif
