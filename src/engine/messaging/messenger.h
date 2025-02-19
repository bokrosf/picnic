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

    void unsubscribe_all(void *recipient);

    namespace detail
    {
        struct subscription
        {
            void *recipient;
            bool removed;
            std::function<void(const void *)> handler;
        };

        extern std::unordered_map<std::type_index, std::vector<subscription>> subscriptions_by_type;
        extern std::unordered_map<void *, std::vector<std::type_index>> subscriptions_by_recipient;
        extern bool sending;

        void unsubscribe(void *recipient, const std::type_index &message_type);
    }

    template<typename Message>
    void send(const Message &message)
    {
        using namespace detail;

        std::type_index message_type = std::type_index(typeid(Message));

        if (!subscriptions_by_type.contains(message_type))
        {
            return;
        }

        sending = true;

        for (auto &s : subscriptions_by_type[message_type] | std::views::filter([](const auto &s) { return !s.removed; }))
        {
            s.handler(&message);
        }

        sending = false;
        std::erase_if(subscriptions_by_type[message_type], [](const auto &s) { return s.removed; });

        if (subscriptions_by_type[message_type].empty())
        {
            subscriptions_by_type.erase(message_type);
        }
    }

    template<typename Message, typename Recipient>
    void subscribe(Recipient *recipient, void (Recipient::* handler)(const Message &))
    {
        using namespace detail;

        std::type_index message_type = std::type_index(typeid(Message));

        subscriptions_by_type[message_type].emplace_back(subscription
        {
            .recipient = recipient,
            .removed = false,
            .handler = [recipient, handler](const void *message)
            {
                (recipient->*handler)(*reinterpret_cast<const Message *>(message));
            }
        });

        subscriptions_by_recipient[recipient].push_back(message_type);
    }

    template<typename Message>
    void unsubscribe(void *recipient)
    {
        using namespace detail;

        unsubscribe(recipient, std::type_index(typeid(Message)));
    }
}

#endif
