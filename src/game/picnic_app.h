#ifndef GAME_PICNICAPP_H
#define GAME_PICNICAPP_H

#include <engine/app.h>
#include <engine/app_configuration.h>

class picnic_app : public app
{
public:
    picnic_app(const app_configuration &configuration);
protected:
    void load_start_scene() override;
};

#endif
