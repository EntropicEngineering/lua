
#ifndef __LUA_ZEPHYRCOMPAT_COMPAT_H__
#define __LUA_ZEPHYRCOMPAT_COMPAT_H__

#include "lstate.h"
#include "zephyr/compat/prefix.h"

l_noret lua_compat_throw( lua_State* L, struct lua_longjmp* errorJmp );

double	    ldexp( double x, int exp );
double	    pow( double base, double exponent );
double	    floor( double x );
double	    strtod( char const* str, char** endptr );
char const* strpbrk( char const* str1, char const* str2 );
double	    frexp( double x, int* exp );
int	    strcoll( char const* str1, char const* str2 );
double	    fmod( double numer, double denom );
char const* strerror( int e );
int	    islower( char c );
int	    ispunct( char c );

unsigned int lua_compat_get_cycle32();
unsigned int lua_compat_get_rand32();

// User must implement the following in application code:
void lua_compat_writestring( void* ud, char const* s, const int l );
void lua_compat_writestringerror( void* ud, char const* m, char const* s );

#endif	//__LUA_ZEPHYRCOMPAT_COMPAT_H__
