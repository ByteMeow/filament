/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by mIcable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <viewer/ViewSettings.h>

#include <assert.h>

// NOTE: We are including cgltf only to get JSMN. We should consider adding jsmn to third_party.
#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

namespace filament {
namespace viewer {

bool parseJson(const char* jsonChunk, cgltf_size size, Settings** out) {
    jsmn_parser parser = { 0, 0, 0 };

    int tokenCount = jsmn_parse(&parser, (const char*)jsonChunk, size, NULL, 0);
    if (tokenCount <= 0) {
        return false;
    }

    jsmntok_t* tokens = (jsmntok_t*) malloc(sizeof(jsmntok_t) * tokenCount);
    assert(tokens);

    jsmn_init(&parser);
    tokenCount = jsmn_parse(&parser, (const char*)jsonChunk, size, tokens, tokenCount);

    if (tokenCount <= 0) {
        free(tokens);
        return false;
    }

    return true;
}

} // namespace viewer
} // namespace filament
