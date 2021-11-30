
// Included by luaconf.h, bounces settings to KConfig options

// Silly workaround because Kconfig parameter is quoted
#define lua_getlocaledecpoint() (CONFIG_LUA_LOCALE_DECPOINT[0])
