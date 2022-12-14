#ifndef _PROTON_ENCODER_H
#define _PROTON_ENCODER_H 1

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

typedef struct pn_encoder_t {
  char *output;
  size_t position;
  pn_error_t *error;
  size_t size;
  unsigned null_count;
} pn_encoder_t;

void pn_encoder_initialize(pn_encoder_t *encoder);
void pn_encoder_finalize(pn_encoder_t *encoder);
ssize_t pn_encoder_encode(pn_encoder_t *encoder, pn_data_t *src, char *dst, size_t size);
ssize_t pn_encoder_size(pn_encoder_t *encoder, pn_data_t *src);

#endif /* encoder.h */
