#ifndef PROTON_INTERNAL_TRACING_HPP
#define PROTON_INTERNAL_TRACING_HPP

/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

#include <vector>

namespace proton {

class binary;
class delivery;
class message;
class messaging_handler;
class tracker;

/// Base class for OpentelemetryTracing and StubTracing. An interface for Tracing.
class Tracing {

    static Tracing* the;

  public:
    /// Returns an object for the Tracing. If Tracing is enable, returns the object of OpentelemetryTracing.
    /// By default returns the object of StubTracing.
    inline static Tracing& getTracing() { return *the; }

    /// Initialize the Tracing object with the OpentelemetryTracing object.
    inline static void activate(Tracing& r) { Tracing::the = &r; }

    virtual void message_encode(const message &m, std::vector<char> &buf, const binary &tag, const tracker &track) = 0;
    virtual void on_message_handler(messaging_handler& h, delivery& d, message& message) = 0;
    virtual void on_settled_span(tracker& track) = 0;
};

} // namespace proton

#endif // PROTON_INTERNAL_TRACING_HPP
