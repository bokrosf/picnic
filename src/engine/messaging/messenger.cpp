#include <engine/messaging/messenger.h>

namespace messenger
{
    using namespace detail;

    void unsubscribe_all(void *recipient)
    {
        while (subscriptions_by_recipient.contains(recipient)
            && !subscriptions_by_recipient[recipient].empty())
        {
            unsubscribe(recipient, subscriptions_by_recipient[recipient].front());
        }
    }
}

namespace messenger::detail
{
    std::unordered_map<std::type_index, std::vector<subscription>> subscriptions_by_type;
    std::unordered_map<void *, std::vector<std::type_index>> subscriptions_by_recipient;
    bool sending = false;

    void unsubscribe(void *recipient, const std::type_index &message_type)
    {
        if (!subscriptions_by_type.contains(message_type))
        {
            return;
        }

        if (sending)
        {
            for (auto &s : subscriptions_by_type[message_type] | std::views::filter([recipient](const auto &s) { return s.recipient == recipient; }))
            {
                s.removed = true;
            }
        }
        else
        {
            std::erase_if(subscriptions_by_type[message_type], [recipient](const auto &s) { return s.recipient == recipient; });

            if (subscriptions_by_type[message_type].empty())
            {
                subscriptions_by_type.erase(message_type);
            }
        }

        if (!subscriptions_by_recipient.contains(recipient))
        {
            return;
        }

        std::erase_if(subscriptions_by_recipient[recipient], [&message_type](const auto &t) { return t == message_type; });

        if (subscriptions_by_recipient[recipient].empty())
        {
            subscriptions_by_recipient.erase(recipient);
        }
    }
}
