#pragma once

#include <mongoc.h>
#include <mongocxx/config/config.hpp>
#include <mongocxx/config/prelude.hpp>
#include "command_started_event.hpp"

#include <iostream>

namespace mongocxx {
MONGOCXX_INLINE_NAMESPACE_BEGIN

class MONGOCXX_API command_listener {
   public:
    // Default function to be overloaded by user
    virtual void command_started(command_started_event event);
};

MONGOCXX_INLINE_NAMESPACE_END
}  // namespace mongocxx

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * NOTE: A user-facing implementation of the Command Monitoring API might could look like this:
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *   class my_command_listener : public command_listener {
 *       public:
 *           void command_started (mongocxx::command_started_event event) {
 *               std::cerr << "Command name: " << event.get_command_name() << std::endl;
 *               // ... and so on
 *           }
 *   };
 *   my_command_listener my_cl;
 *
 *   mongocxx::options::client client_options;
 *   client_options.command_listener_opts(&my_cl);
 *   client x{uri{}, client_options};
 *
 *   auto db = x["test"];
 *   bsoncxx::document::value doc = make_document(kvp("x", 1));
 *   db["test"].insert_one(std::move(doc));
 */
