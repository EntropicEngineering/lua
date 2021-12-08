
#include "zephyr/compat/math/openlibm/internal.h"

// BEGIN SUN/OPENLIBM DERIVED CODE - License: Permissive
OLM_DLLEXPORT float
fabsf(float x)
{
	u_int32_t ix;
	GET_FLOAT_WORD(ix,x);
	SET_FLOAT_WORD(x,ix&0x7fffffff);
        return x;
}