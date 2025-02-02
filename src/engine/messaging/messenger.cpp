#include <engine/messaging/messenger.h>

std::unordered_map<std::type_index, std::vector<messenger::detail::subscription>> messenger::detail::subscriptions_by_type;
bool messenger::detail::sending = false;
