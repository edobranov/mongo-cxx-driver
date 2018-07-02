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

#include <string>

#include <mongoc-apm.h>
#include <bsoncxx/stdx/optional.hpp>
#include <mongocxx/apm/command_listener.hpp>
#include <mongocxx/options/ssl.hpp>

#include <mongocxx/config/prelude.hpp>

namespace mongocxx {
MONGOCXX_INLINE_NAMESPACE_BEGIN
namespace options {

// NOTE: client options interface still evolving

///
/// Class representing the optional arguments to a MongoDB driver client object.
///
class MONGOCXX_API client {
   public:
    ///
    /// Sets the SSL-related options.
    ///
    /// @param ssl_opts
    ///   The SSL related options.
    ///
    /// @return
    ///   A reference to the object on which this member function is being called.  This facilitates
    ///   method chaining.
    ///
    client& ssl_opts(ssl ssl_opts);

    ///
    /// The current SSL-related options.
    ///
    /// @return The SSL-related options.
    ///
    const stdx::optional<ssl>& ssl_opts() const;

    template <typename T>
    client& command_listener(T& policy) {
        _callbacks = mongoc_apm_callbacks_new();
        _context = static_cast<void*>(&policy);

        if (typeid(&T::command_started) != typeid(&default_listener_policy::command_started)) {
            mongoc_apm_set_command_started_cb(
                _callbacks, [](const mongoc_apm_command_started_t* event) {
                    command_started_event _event;
                    auto command = mongoc_apm_command_started_get_command(event);
                    _event.command = bsoncxx::document::view(bson_get_data(command), command->len);
                    _event.database_name = mongoc_apm_command_started_get_database_name(event);
                    _event.command_name = mongoc_apm_command_started_get_command_name(event);
                    _event.request_id = mongoc_apm_command_started_get_request_id(event);
                    _event.operation_id = mongoc_apm_command_started_get_operation_id(event);
                    auto host = mongoc_apm_command_started_get_host(event);
                    _event.host = host->host;
                    _event.port = host->port;

                    auto context = static_cast<T*>(mongoc_apm_command_started_get_context(event));
                    context->command_started(_event);
                });
        }

        return *this;
    }

    mongoc_apm_callbacks_t* callbacks() const {
        return _callbacks;
    }

    void* context() const {
        return _context;
    }

   private:
    stdx::optional<ssl> _ssl_opts;
    mongoc_apm_callbacks_t* _callbacks;
    void* _context;

    friend MONGOCXX_API bool MONGOCXX_CALL operator==(const client&, const client&);
    friend MONGOCXX_API bool MONGOCXX_CALL operator!=(const client&, const client&);
};

}  // namespace options
MONGOCXX_INLINE_NAMESPACE_END
}  // namespace mongocxx

#include <mongocxx/config/postlude.hpp>
