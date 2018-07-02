// Copyright 2014 MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <list>

#include <mongocxx/client.hpp>
#include <mongocxx/private/libmongoc.hh>
#include <mongocxx/private/write_concern.hh>

#include <mongocxx/config/private/prelude.hh>

namespace mongocxx {
MONGOCXX_INLINE_NAMESPACE_BEGIN

class client::impl {
   public:
    impl(mongoc_client_t* client) : client_t(client) {}

    ~impl() {
        libmongoc::client_destroy(client_t);
    }

    mongoc_client_t* client_t;
    std::list<bsoncxx::string::view_or_value> ssl_options;

    // This is passed to the callbacks struct and then passed to the C driver using
    // mongoc_apm_set_command_started_cb() in mongocxx/client.cpp
    static void command_started_wrapper(const mongoc_apm_command_started_t* event) {
        std::cerr << "In command_started_wrapper function" << std::endl;

        // TODO: Fields from mongoc_apm_command_started_t *event should be copied into _event
        command_started_event _event;

        // Call user's overloaded function
        auto context = (command_listener*)mongoc_apm_command_started_get_context(event);
        context->command_started(_event);
    }
};

MONGOCXX_INLINE_NAMESPACE_END
}  // namespace mongocxx

#include <mongocxx/config/private/postlude.hh>
