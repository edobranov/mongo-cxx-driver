#pragma once

#include <mongocxx/apm/command_started_event.hpp>

#include <mongocxx/config/prelude.hpp>

namespace mongocxx {
MONGOCXX_INLINE_NAMESPACE_BEGIN

class MONGOCXX_API default_listener_policy {
   public:
    // Default function to be overloaded by user
    virtual void command_started(const command_started_event& event) {
        (void)event;
    };
};

MONGOCXX_INLINE_NAMESPACE_END
}  // namespace mongocxx

/*
 * --------------------------------------------------------------------------------------------
 * NOTE: A user-facing implementation of the Command Monitoring API might could look like this:
 * --------------------------------------------------------------------------------------------

    class my_command_listener : public command_listener {
     public:
         void command_started (const mongocxx::command_started_event& event) {
           std::cerr << "Command:       " << bsoncxx::to_json(event.command) << std::endl;
           std::cerr << "Database name: " << event.database_name << std::endl;
           std::cerr << "Command name:  " << event.command_name << std::endl;
           std::cerr << "Request ID:    " << event.request_id << std::endl;
           std::cerr << "Operation ID:  " << event.operation_id << std::endl;
           std::cerr << "Host:          " << event.host << std::endl;
           std::cerr << "Port:          " << event.port << std::endl;
         }
    };

    my_command_listener my_cl;
    mongocxx::options::client client_options;
    client_options.command_listener(&my_cl);

    client x{uri{}, client_options};
    auto db = x["test"];
    bsoncxx::document::value doc = make_document(kvp("x", 1));
    db["test"].insert_one(std::move(doc));

 */
