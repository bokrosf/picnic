#ifndef ENGINE_ACTIVATABLE_H
#define ENGINE_ACTIVATABLE_H

class activatable
{
public:
    bool active() const;
    void active(bool active);
protected:
    activatable();
private:
    bool _active;
};

#endif
