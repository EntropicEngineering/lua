
#include "zephyr/compat/math/openlibm/internal.h"

// BEGIN SUN/OPENLIBM DERIVED CODE - License: Permissive
static const float one=1.0, two=2.0, tiny = 1.0e-30, huge = 1.0e30;
OLM_DLLEXPORT float
tanhf(float x)
{
	float t,z;
	int32_t jx,ix;

	GET_FLOAT_WORD(jx,x);
	ix = jx&0x7fffffff;

    /* x is INF or NaN */
	if(ix>=0x7f800000) {
	    if (jx>=0) return one/x+one;    /* tanh(+-inf)=+-1 */
	    else       return one/x-one;    /* tanh(NaN) = NaN */
	}

    /* |x| < 9 */
	if (ix < 0x41100000) {		/* |x|<9 */
	    if (ix<0x39800000) {	/* |x|<2**-12 */
		if(huge+x>one) return x; /* tanh(tiny) = tiny with inexact */
	    }
	    if (ix>=0x3f800000) {	/* |x|>=1  */
		t = expm1f(two*fabsf(x));
		z = one - two/(t+two);
	    } else {
	        t = expm1f(-two*fabsf(x));
	        z= -t/(t+two);
	    }
    /* |x| >= 9, return +-1 */
	} else {
	    z = one - tiny;		/* raise inexact flag */
	}
	return (jx>=0)? z: -z;
}
