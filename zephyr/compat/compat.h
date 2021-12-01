
#ifndef __LUA_ZEPHYRCOMPAT_COMPAT_H__
#define __LUA_ZEPHYRCOMPAT_COMPAT_H__

#include "zephyr/compat/prefix.h"
#include "lstate.h"

l_noret lua_compat_throw(lua_State *L, struct lua_longjmp *errorJmp);

double ldexp (double x, int exp);
double pow (double base, double exponent);
double floor (double x);
double strtod (const char* str, char** endptr);
const char * strpbrk (const char * str1, const char * str2 );
double frexp (double x, int* exp);
int strcoll (const char * str1, const char * str2 );
double fmod (double numer, double denom);
const char * strerror(int e);
int islower(char c);
int ispunct(char c);

unsigned int lua_compat_get_cycle32();
unsigned int lua_compat_get_rand32();

// User must implement the following in application code:
void lua_compat_writestring(void *ud, const char* s, const int l);
void lua_compat_writestringerror(void *ud, const char* m, const char* s);

#endif //__LUA_ZEPHYRCOMPAT_COMPAT_H__
