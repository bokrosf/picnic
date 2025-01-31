#ifndef ENGINE_MESSAGING_RECIPIENT_H
#define ENGINE_MESSAGING_RECIPIENT_H

template<typename T>
class recipient
{
public:
    virtual void receive(const T &message) = 0;
};

#endif
