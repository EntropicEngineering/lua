
// Included by luaconf.h, bounces settings to KConfig options

// Silly workaround because Kconfig parameter is quoted
#define lua_getlocaledecpoint() (CONFIG_LUA_LOCALE_DECPOINT[0])

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

#ifdef CONFIG_LUA_ENABLE_MATH_TRUE_RANDOM
#define lua_compat_randseed() lua_compat_get_rand32()
#else
#define lua_compat_randseed() lua_compat_get_cycle32()
#endif
