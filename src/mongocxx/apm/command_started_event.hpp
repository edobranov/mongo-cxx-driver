#pragma once

#include <bsoncxx/document/view.hpp>
#include <mongocxx/config/config.hpp>

#include <mongocxx/config/prelude.hpp>

namespace mongocxx {
MONGOCXX_INLINE_NAMESPACE_BEGIN

// User facing command event
struct command_started_event {
    bsoncxx::document::view command;
    bsoncxx::stdx::string_view database_name;
    bsoncxx::stdx::string_view command_name;
    std::int64_t request_id;
    std::int64_t operation_id;
    bsoncxx::stdx::string_view host;
    std::uint16_t port;
};

MONGOCXX_INLINE_NAMESPACE_END
}  // namespace

#include <mongocxx/config/postlude.hpp>
