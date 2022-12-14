#ifndef _PROTON_DISPATCHER_H
#define _PROTON_DISPATCHER_H 1

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

#ifndef __cplusplus
#include <stdbool.h>
#endif

#include "proton/codec.h"
#include "proton/types.h"

typedef int (pn_action_t)(pn_transport_t *transport, uint8_t frame_type, uint16_t channel, const pn_bytes_t frame_payload);

ssize_t pn_dispatcher_input(pn_transport_t* transport, const char* bytes, size_t available, bool batch, bool* halt);
ssize_t pn_dispatcher_output(pn_transport_t *transport, char *bytes, size_t size);

#endif /* dispatcher.h */
