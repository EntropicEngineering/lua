
#include <logging/log.h>
#include "zephyrcompat/compat.h"
#include <kernel.h>

LOG_MODULE_REGISTER(lua_compat, LOG_LEVEL_DBG);

#define STUB() LOG_ERR("lua/zephyrcompat/compat.c: %s invoked!", __func__); while (1) { k_msleep(1000); }

l_noret lua_compat_throw(lua_State *L, struct lua_longjmp *errorJmp) { STUB() }
int lua_compat_randseed() { return 0; }

double ldexp (double x, int exp) { STUB() }
double pow (double base, double exponent) { STUB() }
double floor (double x) { STUB() }
double strtod (const char* str, char** endptr) { STUB() }
char * strpbrk (const char * str1, const char * str2 ) { STUB() }
double frexp (double x, int* exp) { STUB() }
int strcoll (const char * str1, const char * str2 ) { STUB() }
double fmod (double numer, double denom) { STUB() }

void lua_compat_writestring(const char* s, int l) {
	LOG_INF("lua_compat_writestring: %.*s", l, s);
}
void lua_compat_writestringerror(const char* f, char* s){
	LOG_ERR("lua_compat_writestringerror: %s", s);
}

