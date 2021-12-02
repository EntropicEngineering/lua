
// Included by luaconf.h

// Silly workaround because Kconfig parameter is quoted
#define lua_getlocaledecpoint() ( CONFIG_LUA_LOCALE_DECPOINT[0] )
