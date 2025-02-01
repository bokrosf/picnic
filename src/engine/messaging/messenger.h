#ifndef ENGINE_MESSAGING_MESSENGER_H
#define ENGINE_MESSAGING_MESSENGER_H

#include <ranges>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <engine/messaging/recipient.h>

namespace messenger
{
    template<typename Message>
    void send(const Message &message);

    template<typename Message>
    void subscribe(recipient<Message> &recipient);

    template<typename Message>
    void unsubscribe(recipient<Message> &recipient);

    namespace detail
    {
        struct subscription
        {
            subscription(void *object);

            void *object;
            bool removed;
        };

        extern std::unordered_map<std::type_index, std::vector<subscription>> subscriptions;
        extern bool sending;
    }
}

template<typename Message>
void messenger::send(const Message &message)
{
    using namespace messenger::detail;

    std::type_index key = std::type_index(typeid(Message));

    if (!subscriptions.contains(key))
    {
        return;
    }

    sending = true;

    for (auto &s : subscriptions[key])
    {
        if (auto r = reinterpret_cast<recipient<Message> *>(s.object))
        {
            r->receive(message);
        }
    }

    sending = false;
    std::erase_if(subscriptions[key], [](const auto &s) { return s.removed; });
}

template<typename Message>
void messenger::subscribe(recipient<Message> &recipient)
{
    using namespace messenger::detail;

    std::type_index key = std::type_index(typeid(Message));
    subscriptions[key].emplace_back(&recipient);
}

template<typename Message>
void messenger::unsubscribe(recipient<Message> &recipient)
{
    using namespace messenger::detail;

    std::type_index key = std::type_index(typeid(Message));

    if (!subscriptions.contains(key))
    {
        return;
    }

    if (sending)
    {
        for (auto &s : subscriptions[key] | std::views::filter([&recipient](const auto &s) { return s.object == &recipient; }))
        {
            s.removed = true;
        }
    }
    else
    {
        std::erase_if(subscriptions[key], [&recipient](const auto &s) { return s.object == &recipient; });
    }
}

#endif
