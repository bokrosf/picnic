#ifndef ENGINE_COMPONENT_UPDATABLE_H
#define ENGINE_COMPONENT_UPDATABLE_H

class updatable
{
public:
    updatable();
    virtual void update() = 0;

    static const int default_priority;
    int priority;
};

#endif