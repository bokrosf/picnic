#include <exception>
#include <iostream>
#include <SDL3/SDL_main.h>
#include <engine/logging/logger.h>
#include <game/picnic_app.h>

int main(int argc, char *argv[])
{
    logger::destination(std::cout);

    try
    {
        picnic_app app(app_configuration{"Picnic"});
        app.run();
    }
    catch (std::exception &ex)
    {
        logger::error(ex.what());
    }

    return 0;
}
