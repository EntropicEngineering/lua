
#ifndef __LUA_ZEPHYRCOMPAT_COMPAT_H__
#define __LUA_ZEPHYRCOMPAT_COMPAT_H__

#include "zephyr/compat/prefix.h"
#include "lstate.h"

l_noret lua_compat_throw(lua_State *L, struct lua_longjmp *errorJmp);

double strtod (const char* str, char** endptr);
// WARNING: Our strtod does not implement parsing for 'inf'/'nan'
//  (this is fine for lua, since it dosen't let you use them as literals
//   anyway)
#define strtof strtod

const char * strpbrk (const char * str1, const char * str2 );
int strcoll (const char * str1, const char * str2 );
const char * strerror(int e);
int islower(char c);
int ispunct(char c);

#include "zephyr/compat/math/math.h"

unsigned int lua_compat_get_cycle32();
unsigned int lua_compat_get_rand32();

// User must implement the following in application code:
void lua_compat_writestring(void *ud, const char* s, const int l);
void lua_compat_writestringerror(void *ud, const char* m, const char* s);

#endif //__LUA_ZEPHYRCOMPAT_COMPAT_H__
