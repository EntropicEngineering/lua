
#include <logging/log.h>
#include "zephyr/compat/compat.h"
#include <kernel.h>
#include <stdlib.h>

LOG_MODULE_REGISTER(lua_compat, LOG_LEVEL_DBG);

#define STUB() LOG_ERR("lua/zephyrcompat/compat.c: %s invoked!", __func__); while (1) abort();

l_noret lua_compat_throw(lua_State *L, struct lua_longjmp *errorJmp) { STUB(); }

const char * strerror(int e) {
	LOG_ERR("strerror -> %d", e);
	return "E???";
}

const char * strpbrk (const char * s, const char * accept ) {
	// TODO: More efficient implementation?

	while ((*s) != 0) {
		const char* c = accept;
		while ((*c) != 0) {
			if ((*s) == (*c)) return s;
			c++;
		}
		s++;
	}

	return NULL;
}

int strcoll (const char * str1, const char * str2 ) {
	// TODO: More efficient implementation?

	while (((*str1) != 0) && ((*str2) != 0)) {
		int d = (*str1) - (*str2);
		if (d!=0) return d;
		str1++;
		str2++;
	}

	return 0;
}

int isdigit(char x) {
	return (x >= '0') && (x <= '9');
}

double strtod (const char* str, char** endptr) {
	// TODO: This is SO NOT a standards-conformant (or even good) implementation
	//  (no infs, no nan, no e+, etc.) but good enough for 1, 1.2, and .2
	//  The newlib and others impl involve dynamic allocation (!?!?) and it was
	//  expedient to just write one

	char* cursor = (char*) str;
	while (isdigit(*cursor)) {
		cursor++;
	}

	char* point_or_end = cursor;

	double number = 0;
	double mul = 1;
	while (cursor > str) {
		cursor--;
		number += ((*cursor) - '0') * mul;
		mul *= 10;
	}

	cursor = point_or_end;
	mul = 0.1;
	if ((*cursor) == '.') {
		cursor++;

		while (isdigit(*cursor)) {
			number += ((*cursor) - '0') * mul;
			mul /= 10;
			cursor++;
		}
	}

	if (endptr != NULL) *endptr = cursor;

	return number;
}

double floor (double x) {
	// TODO: This is a terrible implementation

	int i = 0;
	if (x > 0) {
		while (i <= x) {
			i++;
		}

		if (i != x) i--;
	} else {
		while (x < i) {
			i--;
		}
	}

	return (double)i;
}

double fabs(double x) {
	if (x<0) x*=-1;
	return x;
}

double frexp (double x, int* exp) {
	// TODO: NOT a good implementation

	if (x==0) {
		*exp = 0;
		return 0;
	}

	int e = 0;
	if (fabs(x) > 1) {
		while (fabs(x) > 1) {
			x /= 2;
			e++;
		}
	} else {
		while (fabs(x) < 0.5) {
			x *= 2;
			e--;
		}
	}

	if (!((fabs(x) >= 0.5) && (fabs(x) < 1))) {
		LOG_ERR("OOPS! Gotta write a real frexp");
		STUB();
	}

	*exp = e;
	return x;
}


double fmod (double numer, double denom) {
	// TODO: NOT a good implementation

	denom = fabs(denom);
	double sign = 1;
	if (numer < 1) sign = -1;
	numer = fabs(numer);


	while (numer > 0) {
		numer -= denom;
	}

	numer += denom;

	return numer * sign;
}

double ldexp (double x, int exp) {
	while (exp > 0) {
		x *= 2;
		exp--;
	}
	while (exp < 0) {
		x /= 2;
		exp++;
	}
	return x;
}

double pow (double base, double exponent) {
	if (fabs(((double)((int)exponent)) - exponent) > 0.01) {
		LOG_ERR("Gotta write a real pow");
		STUB();
	}

	double v = base;

	int i = exponent;
	while (i > 0) {
		v *= base;
		i--;
	}

	while (i < 0) {
		v /= base;
		i++;
	}

	return v;
}

int islower(char c) { return ('a' <= c) && ('z' >= c); }
int ispunct(char c) {
	char *s = "~!@#$%^&*()_+`-=;:'\"\\|[]{},./<>?";
	while ((*s) != 0) {
		if ((*s) == c) return 1;
		s++;
	}
	return 0;
}


unsigned int lua_compat_get_cycle32() {
	// TODO: Need to reimplement these so that they don't cause MPU fault in userland
	return k_cycle_get_32();
}

unsigned int lua_compat_get_rand32() {
	// TODO: Need to reimplement these so that they don't cause MPU fault in userland
	return sys_rand32_get();
}

void lua_compat_writestring(const char* s, const int l) {
	LOG_INF("lua_compat_writestring: %.*s", l, s);
}
void lua_compat_writestringerror(const char* f, const char* s){
	LOG_ERR("lua_compat_writestringerror: %s", s);
}

