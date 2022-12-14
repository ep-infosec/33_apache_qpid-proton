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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#include <benchmark/benchmark.h>

#include "proton/connection_driver.h"
#include "proton/engine.h"
#include "proton/listener.h"
#include "proton/log.h"
#include "proton/message.h"
#include "proton/netaddr.h"
#include "proton/object.h"
#include "proton/proactor.h"
#include "proton/sasl.h"

#define MAX_SIZE 1024

typedef char str[MAX_SIZE];

const bool VERBOSE = false;
const bool ERRORS = true;

static void decode_message_buffer(pn_rwbytes_t data) {
  pn_message_t *m = pn_message();
  int err = pn_message_decode(m, data.start, data.size);
  if (!err) {
    /* Print the decoded message */
    char *s = pn_tostring(pn_message_body(m));
    if (VERBOSE) {
      printf("%s\n", s);
      fflush(stdout);
    }
    free(s);
    pn_message_free(m);
    free(data.start);
  } else {
    fprintf(stderr, "decode error: %s\n", pn_error_text(pn_message_error(m)));
    exit(EXIT_FAILURE);
  }
}

static void BM_EncodeMapMessage(benchmark::State &state) {
  if (VERBOSE)
    printf("BEGIN BM_EncodeMapMessage\n");

  uint64_t entries = 0;

  pn_message_t *message = pn_message();

  for (auto _ : state) {
    pn_message_clear(message);
    pn_data_t *body;
    body = pn_message_body(message);
    pn_data_put_map(body);
    pn_data_enter(body);
    for (size_t i = 0; i < state.range(0); ++i) {
      pn_data_put_int(body, i);
      pn_data_put_string(
          body, pn_bytes(sizeof("some key value") - 1, "some key value"));
      entries += 2;
    }
    pn_data_exit(body);
    pn_rwbytes_t buf{};
    if (pn_message_encode2(message, &buf) == 0) {
      state.SkipWithError(pn_error_text(pn_message_error(message)));
    }
    if (buf.start)
      free(buf.start);
  }
  pn_message_free(message);

  state.SetLabel("entries");
  state.SetItemsProcessed(entries);

  if (VERBOSE)
    printf("END BM_EncodeMapMessage\n");
}

BENCHMARK(BM_EncodeMapMessage)
    ->Arg(10)
    ->Arg(100)
    ->Arg(1000)
    ->Arg(10000)
    ->ArgName("entries")
    ->Unit(benchmark::kMillisecond);

static void BM_CreateMapMessage(benchmark::State &state) {
  if (VERBOSE)
    printf("BEGIN BM_CreateMapMessage\n");

  uint64_t entries = 0;

  pn_message_t *message = pn_message();

  pn_message_clear(message);
  pn_data_t *body;
  body = pn_message_body(message);
  pn_data_put_map(body);
  pn_data_enter(body);
  for (auto _ : state) {
    pn_data_put_int(body, entries);
    pn_data_put_string(
        body, pn_bytes(sizeof("some key value") - 1, "some key value"));
    entries += 2;
  }
  pn_data_exit(body);
  pn_message_free(message);

  state.SetLabel("entries");
  state.SetItemsProcessed(entries);

  if (VERBOSE)
    printf("END BM_CreateMapMessage\n");
}

BENCHMARK(BM_CreateMapMessage);


static void decode_message(pn_delivery_t *dlv) {
  static char buffer[MAX_SIZE];
  ssize_t len;
  // try to decode the message body
  if (pn_delivery_pending(dlv) < MAX_SIZE) {
    // read in the raw data
    len = pn_link_recv(pn_delivery_link(dlv), buffer, MAX_SIZE);
    if (len > 0) {
      // decode it into a proton message
      pn_message_t *m = pn_message();
      if (PN_OK == pn_message_decode(m, buffer, len)) {
        char *s = pn_tostring(pn_message_body(m));
        if (VERBOSE)
          printf("%s\n", s);
        free(s);
      }
      pn_message_free(m);
    }
  }
}
