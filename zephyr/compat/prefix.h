
// Included by lprefix.h, and so by most lua files
// See also: conf.h

#include "zephyr/compat/compat.h"
#include "zephyr/compat/conf.h"
#include <stdint.h>

#define l_signalT int

#ifdef CONFIG_LUA_EXCEPTION_IMPLEMENTATION_PANIC
#define LUAI_THROW(L,c) lua_compat_throw(L,c) //panics!
#define LUAI_TRY(L,c,a) { a }
#define luai_jmpbuf int //dummy, nothing stored
#endif // CONFIG_LUA_EXCEPTION_IMPLEMENTATION_PANIC

#ifdef CONFIG_LUA_EXCEPTION_IMPLEMENTATION_GCC_LONGJMP
// Implemented per https://gcc.gnu.org/onlinedocs/gcc/Nonlocal-Gotos.html
typedef intptr_t         __jmp_buf[5];
#define LUAI_THROW(L,c)  __builtin_longjmp((c)->b, 1) 
#define LUAI_TRY(L,c,a)  if (__builtin_setjmp((c)->b) == 0) { a }
#define luai_jmpbuf      __jmp_buf
#endif // CONFIG_LUA_EXCEPTION_IMPLEMENTATION_GCC_LONGJMP

#ifdef CONFIG_LUA_ENABLE_CONSOLE_OUTPUT
#define lua_writestring(s, l) lua_compat_writestring(L->l_G->ud, s, l)
#define lua_writestringerror(s, p) lua_compat_writestringerror(L->l_G->ud, s, p)
#define lua_writeline()
#else // LUA_ENABLE_CONSOLE_OUTPUT
#define lua_writestring(s, l)
#define lua_writestringerror(s, p)
#define lua_writeline() 
#endif // LUA_ENABLE_CONSOLE_OUTPUT

#ifndef CONFIG_LUA_ENABLE_RANDOMIZE_HASHES
#define luai_makeseed(L) (~0)
#else
#define luai_makeseed(L) lua_compat_get_cycle32()
#endif

#ifndef CONFIG_LUA_ENABLE_RANDOMIZE_PIVOTS
#define l_randomizePivot() (~0)
#else
#define l_randomizePivot() lua_compat_get_cycle32()
#endif

#ifdef CONFIG_LUA_ENABLE_MATH_ZERO_RANDOM
#define lua_compat_randseed() (0)
#endif

#ifdef CONFIG_LUA_ENABLE_MATH_TRUE_RANDOM
#define lua_compat_randseed() lua_compat_get_rand32()
#endif

#ifdef LUA_ENABLE_MATH_TIME_RANDOM
#define lua_compat_randseed() lua_compat_get_cycle32()
#endif
