
#include "zephyr/compat/math/arm/internal.h"

// BEGIN CMSIS-DSP DERIVED CODE - LICENSE: Apache 2.0
// Copyright (C) 2010-2021 ARM Limited or its affiliates
float32_t arm_sqrt_f32(float32_t in)
{
  float32_t out;
  __asm__("VSQRT.F32 %0,%1" : "=t"(out) : "t"(in));
  return out;
}
// END CMSIS-DSP CODE
