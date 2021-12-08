
#ifndef __ZEPHYR_LUA_MATH_H__
#define __ZEPHYR_LUA_MATH_H__

#include "zephyr/compat/math/arm/internal.h"

#define sqrtf arm_sqrt_f32
#define cosf arm_cos_f32
#define sinf arm_sin_f32
#define tanf arm_tan_f32

#include "zephyr/compat/math/openlibm/internal.h"

#endif // __ZEPHYR_LUA_MATH_H__