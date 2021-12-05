
// Included by luaconf.h, prefix.h

// Silly workaround because Kconfig parameter is quoted
#define lua_getlocaledecpoint() (CONFIG_LUA_LOCALE_DECPOINT[0])

#ifdef CONFIG_LUA_32BITS
#define LUA_32BITS 1
#endif // CONFIG_LUA_32BITS

// Need these so LUA_32BITS will be effective because otherwise luaconf will think
//  we are a C89 system and auto-select usage of doubles in every case.
#define HUGE_VAL (__builtin_inf())
#define HUGE_VALF (__builtin_inff())
