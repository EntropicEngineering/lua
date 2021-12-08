
#include "zephyr/compat/math/arm/tablesf.h"

// BEGIN CMSIS-DSP DERIVED CODE - LICENSE: Apache 2.0
// Copyright (C) 2010-2021 ARM Limited or its affiliates
float32_t arm_sin_f32(float32_t x)
{
  float32_t sinVal, fract, in;                   /* Temporary input, output variables */
  uint16_t index;                                /* Index variable */
  float32_t a, b;                                /* Two nearest output values */
  int32_t n;
  float32_t findex;

  /* input x is in radians */
  /* Scale input to [0 1] range from [0 2*PI] , divide input by 2*pi */
  in = x * 0.159154943092f;

  /* Calculation of floor value of input */
  n = (int32_t) in;

  /* Make negative values towards -infinity */
  if (in < 0.0f)
  {
    n--;
  }

  /* Map input value to [0 1] */
  in = in - (float32_t) n;

  /* Calculation of index of the table */
  findex = (float32_t)FAST_MATH_TABLE_SIZE * in;
  index = (uint16_t)findex;

  /* when "in" is exactly 1, we need to rotate the index down to 0 */
  if (index >= FAST_MATH_TABLE_SIZE) {
    index = 0;
    findex -= (float32_t)FAST_MATH_TABLE_SIZE;
  }

  /* fractional value calculation */
  fract = findex - (float32_t) index;

  /* Read two nearest values of input value from the sin table */
  a = sinTable_f32[index];
  b = sinTable_f32[index+1];

  /* Linear interpolation process */
  sinVal = (1.0f - fract) * a + fract * b;

  /* Return output value */
  return (sinVal);
}

float32_t arm_cos_f32(float32_t x)
{
  float32_t cosVal, fract, in;                   /* Temporary input, output variables */
  uint16_t index;                                /* Index variable */
  float32_t a, b;                                /* Two nearest output values */
  int32_t n;
  float32_t findex;

  /* input x is in radians */
  /* Scale input to [0 1] range from [0 2*PI] , divide input by 2*pi, add 0.25 (pi/2) to read sine table */
  in = x * 0.159154943092f + 0.25f;

  /* Calculation of floor value of input */
  n = (int32_t) in;

  /* Make negative values towards -infinity */
  if (in < 0.0f)
  {
    n--;
  }

  /* Map input value to [0 1] */
  in = in - (float32_t) n;

  /* Calculation of index of the table */
  findex = (float32_t)FAST_MATH_TABLE_SIZE * in;
  index = (uint16_t)findex;

  /* when "in" is exactly 1, we need to rotate the index down to 0 */
  if (index >= FAST_MATH_TABLE_SIZE) {
    index = 0;
    findex -= (float32_t)FAST_MATH_TABLE_SIZE;
  }

  /* fractional value calculation */
  fract = findex - (float32_t) index;

  /* Read two nearest values of input value from the cos table */
  a = sinTable_f32[index];
  b = sinTable_f32[index+1];

  /* Linear interpolation process */
  cosVal = (1.0f - fract) * a + fract * b;

  /* Return output value */
  return (cosVal);
}
// END CMSIS-DSP CODE

float32_t arm_tan_f32(float32_t x)
{
  // TODO: Improve
  return arm_sin_f32(x) / arm_cos_f32(x);
}
