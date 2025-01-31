#include <engine/component/updatable.h>

const int updatable::default_priority = 0;

updatable::updatable()
    : priority(default_priority)
{
}