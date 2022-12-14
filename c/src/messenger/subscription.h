#ifndef _PROTON_SUBSCRIPTION_H
#define _PROTON_SUBSCRIPTION_H 1

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

#include <proton/messenger.h>
#include <proton/object.h>

#include "core/object_private.h"

extern const pn_class_t PN_CLASSCLASS(pn_subscription);

pn_subscription_t *pn_subscription(pn_messenger_t *messenger,
                                   const char *scheme, const char *host,
                                   const char *port);
const char *pn_subscription_scheme(pn_subscription_t *sub);
int pni_subscription_set_address(pn_subscription_t *sub, const char *address);

#endif /* subscription.h */
