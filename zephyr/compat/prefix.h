
// Included by lprefix.h, and so by most lua files

#include "zephyr/compat/compat.h"
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

#define lua_writestring(s, l) lua_compat_writestring(s, l)
#define lua_writestringerror(s, p) lua_compat_writestringerror(s, p)
#define lua_writeline()
