/**
 * \file src/common.h
 * MegRay is Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Copyright (c) 2014-2020 Megvii Inc. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT ARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */

#pragma once

#include "cuda_runtime.h"

#include "debug.h"

namespace MegRay {

typedef enum {
    MEGRAY_OK = 0,
    MEGRAY_CUDA_ERR = 1,
    MEGRAY_NCCL_ERR = 2,
    MEGRAY_UCX_ERR = 3,
    MEGRAY_NOT_IMPLEMENTED = 4
} Status;

#define MEGRAY_CHECK(expr)                              \
    do {                                                \
        Status status = (expr);                         \
        if (status != MEGRAY_OK) {                      \
            MEGRAY_ERROR("error [%d]", status);         \
            return status;                              \
        }                                               \
    } while (0)

#define CUDA_CHECK(expr)                                \
    do {                                                \
        cudaError_t status = (expr);                    \
        if (status != cudaSuccess) {                    \
            MEGRAY_ERROR("cuda error [%d]: %s", status, \
                cudaGetErrorString(status));            \
            return MEGRAY_CUDA_ERR;                     \
        }                                               \
    } while (0)

#define CUDA_ASSERT(expr)                               \
    do {                                                \
        cudaError_t status = (expr);                    \
        if (status != cudaSuccess) {                    \
            MEGRAY_ERROR("cuda error [%d]: %s", status, \
                cudaGetErrorString(status));            \
            MEGRAY_THROW("cuda error");                 \
        }                                               \
    } while (0)

typedef enum {
    MEGRAY_NCCL = 0,
    MEGRAY_UCX = 1,
} Backend;

typedef enum {
    MEGRAY_INT8 = 0,
    MEGRAY_UINT8 = 1,
    MEGRAY_INT32 = 2,
    MEGRAY_UINT32 = 3,
    MEGRAY_INT64 = 4,
    MEGRAY_UINT64 = 5,
    MEGRAY_FLOAT16 = 6,
    MEGRAY_FLOAT32 = 7,
    MEGRAY_FLOAT64 = 8
} DType;

size_t get_dtype_size(DType dtype);

typedef enum {
    MEGRAY_SUM = 0,
    MEGRAY_MAX = 1,
    MEGRAY_MIN = 2
} ReduceOp;

} // namespace MegRay
