#include <exception>
#include <iostream>
#include <SDL3/SDL_main.h>
#include <engine/logging/logger.h>
#include <game/picnic_app.h>

int main(int argc, char *argv[])
{
    logger::destination(std::cout);
    app *app = nullptr;

    try
    {
        app = new picnic_app(app_configuration{"Picnic"});
        app->run();
    }
    catch (std::exception &ex)
    {
        logger::error(ex.what());
    }

    delete app;

    return 0;
}
