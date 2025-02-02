#ifndef ENGINE_MESSAGING_MESSENGER_H
#define ENGINE_MESSAGING_MESSENGER_H

#include <functional>
#include <ranges>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace messenger
{
    template<typename Message>
    void send(const Message &message);

    template<typename Message, typename Recipient>
    void subscribe(Recipient *recipient, void (Recipient::* handler)(const Message &));

    template<typename Message>
    void unsubscribe(void *recipient);

    namespace detail
    {
        struct subscription
        {
            void *recipient;
            bool removed;
            std::function<void(const void *)> handler;
        };

        extern std::unordered_map<std::type_index, std::vector<subscription>> subscriptions_by_type;
        extern bool sending;
    }
}

template<typename Message>
void messenger::send(const Message &message)
{
    using namespace messenger::detail;

    std::type_index key = std::type_index(typeid(Message));

    if (!subscriptions_by_type.contains(key))
    {
        return;
    }

    sending = true;

    for (auto &s : subscriptions_by_type[key])
    {
        s.handler(&message);
    }

    sending = false;
    std::erase_if(subscriptions_by_type[key], [](const auto &s) { return s.removed; });
}

template<typename Message, typename Recipient>
void messenger::subscribe(Recipient *recipient, void (Recipient::* handler)(const Message &))
{
    using namespace messenger::detail;

    std::type_index key = std::type_index(typeid(Message));

    subscriptions_by_type[key].emplace_back(subscription
    {
        .recipient = recipient,
        .removed = false,
        .handler = [recipient, handler](const void *message)
        {
            (recipient->*handler)(*reinterpret_cast<const Message *>(message));
        }
    });
}

template<typename Message>
void messenger::unsubscribe(void *recipient)
{
    using namespace messenger::detail;

    std::type_index key = std::type_index(typeid(Message));

    if (!subscriptions_by_type.contains(key))
    {
        return;
    }

    if (sending)
    {
        for (auto &s : subscriptions_by_type[key] | std::views::filter([recipient](const auto &s) { return s.recipient == recipient; }))
        {
            s.removed = true;
        }
    }
    else
    {
        std::erase_if(subscriptions_by_type[key], [recipient](const auto &s) { return s.recipient == recipient; });
    }
}

#endif
