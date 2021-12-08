/*
 * Float version of k_log.h.  See the latter for most comments.
 */

static const float
/* |(log(1+s)-log(1-s))/s - Lg(s)| < 2**-34.24 (~[-4.95e-11, 4.97e-11]). */
k_Lg1 =      0xaaaaaa.0p-24,	/* 0.66666662693 */
k_Lg2 =      0xccce13.0p-25,	/* 0.40000972152 */
k_Lg3 =      0x91e9ee.0p-25,	/* 0.28498786688 */
k_Lg4 =      0xf89e26.0p-26;	/* 0.24279078841 */

static inline float
k_log1pf(float f)
{
	float hfsq,s,z,R,w,t1,t2;

 	s = f/((float)2.0+f);
	z = s*s;
	w = z*z;
	t1= w*(k_Lg2+w*k_Lg4);
	t2= z*(k_Lg1+w*k_Lg3);
	R = t2+t1;
	hfsq=(float)0.5*f*f;
	return s*(hfsq+R);
}
