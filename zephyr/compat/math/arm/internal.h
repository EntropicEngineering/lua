
#include <stdint.h>
#include <float.h>

#ifndef __ZEPHYR_LUA_COMPAT_MATH_ARM_INTERNAL_H__
#define __ZEPHYR_LUA_COMPAT_MATH_ARM_INTERNAL_H__

// BEGIN CMSIS-DSP DERIVED CODE - LICENSE: Apache 2.0
// Copyright (C) 2010-2021 ARM Limited or its affiliates
#define FAST_MATH_TABLE_SIZE 512
#define float32_t float
#define float64_t double
// END CMSIS-DSP CODE

_Static_assert(sizeof(float32_t)==4);
_Static_assert(sizeof(float64_t)==8);

float arm_sqrt_f32(const float);
float arm_cos_f32(const float);
float arm_sin_f32(const float);
float arm_tan_f32(const float);

#endif // __ZEPHYR_LUA_COMPAT_MATH_ARM_INTERNAL_H__
