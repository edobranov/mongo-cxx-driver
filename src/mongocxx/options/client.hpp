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

    ///
    /// Sets the command-listening-related options.
    ///
    /// @param cl_opts
    ///   The APM (application performance monitoring) related options.
    ///
    /// @return
    ///   A reference to the object on which this member function is being called.  This facilitates
    ///   method chaining.
    ///
    client& command_listener_opts(command_listener* cl_opts);

    ///
    /// The current command-listening class options.
    ///
    /// @return The command-listening class options.
    ///
    const stdx::optional<command_listener*>& command_listener_opts() const;

   private:
    stdx::optional<ssl> _ssl_opts;
    stdx::optional<command_listener*> _cl_callbacks;

    friend MONGOCXX_API bool MONGOCXX_CALL operator==(const client&, const client&);
    friend MONGOCXX_API bool MONGOCXX_CALL operator!=(const client&, const client&);
};

}  // namespace options
MONGOCXX_INLINE_NAMESPACE_END
}  // namespace mongocxx

#include <mongocxx/config/postlude.hpp>
