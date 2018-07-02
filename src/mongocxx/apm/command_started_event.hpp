#pragma once

#include <bsoncxx/document/view.hpp>
#include <mongocxx/config/config.hpp>
#include <mongocxx/config/prelude.hpp>

namespace mongocxx {
MONGOCXX_INLINE_NAMESPACE_BEGIN

// User facing command event
// User's overridden functions should take an instance of this class as an argument
class command_started_event {
   private:
    bsoncxx::document::view command;
    std::string database_name;
    std::string command_name;
    int64_t request_id;
    int64_t operation_id;

    // TODO: mongoc_host_list_t will be populated from host and port in command_started_wrapper
    std::string host;
    uint16_t port;

   public:
    // TODO: Add functions like get_command(), get_database_name(), etc.
};

MONGOCXX_INLINE_NAMESPACE_END
}  // namespace
