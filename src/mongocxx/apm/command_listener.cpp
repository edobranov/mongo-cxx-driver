#include <mongocxx/config/private/prelude.hh>

#include <mongocxx/apm/command_listener.hpp>
#include <mongocxx/apm/command_started_event.hpp>

namespace mongocxx {
MONGOCXX_INLINE_NAMESPACE_BEGIN

// Default behavior to be overloaded by user
void command_listener::command_started(mongocxx::command_started_event event) {
    std::cerr << "In original command_started function" << std::endl;
}

MONGOCXX_INLINE_NAMESPACE_END
}  // namespace mongocxx
