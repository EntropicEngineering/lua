
#include "zephyr/compat/math/openlibm/internal.h"

// BEGIN SUN/OPENLIBM DERIVED CODE - License: Permissive
static const u_int32_t k = 235;			/* constant for reduction */
static const float kln2 =  162.88958740F;	/* k * ln2 */

/*
 * See k_exp.c for details.
 *
 * Input:  ln(FLT_MAX) <= x < ln(2 * FLT_MAX / FLT_MIN_DENORM) ~= 192.7
 * Output: 2**127 <= y < 2**128
 */
static float
__frexp_expf(float x, int *expt)
{
	double exp_x;
	u_int32_t hx;

	exp_x = expf(x - kln2);
	GET_FLOAT_WORD(hx, exp_x);
	*expt = (hx >> 23) - (0x7f + 127) + k;
	SET_FLOAT_WORD(exp_x, (hx & 0x7fffff) | ((0x7f + 127) << 23));
	return (exp_x);
}

OLM_DLLEXPORT float
__ldexp_expf(float x, int expt)
{
	float exp_x, scale;
	int ex_expt;

	exp_x = __frexp_expf(x, &ex_expt);
	expt += ex_expt;
	SET_FLOAT_WORD(scale, (0x7f + expt) << 23);
	return (exp_x * scale);
}