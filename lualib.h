/*
** $Id: lualib.h $
** Lua standard libraries
** See Copyright Notice in lua.h
*/


#ifndef lualib_h
#define lualib_h

#include "lua.h"


/* version suffix for environment variable names */
#define LUA_VERSUFFIX          "_" LUA_VERSION_MAJOR "_" LUA_VERSION_MINOR

#ifdef CONFIG_LUA_ENABLE_LIB_BASE
LUAMOD_API int (luaopen_base) (lua_State *L);
#endif // CONFIG_LUA_ENABLE_LIB_BASE

#ifdef CONFIG_LUA_ENABLE_LIB_COROUTINE
#define LUA_COLIBNAME	"coroutine"
LUAMOD_API int (luaopen_coroutine) (lua_State *L);
#endif // CONFIG_LUA_ENABLE_LIB_COROUTINE

#ifdef CONFIG_LUA_ENABLE_LIB_TABLE
#define LUA_TABLIBNAME	"table"
LUAMOD_API int (luaopen_table) (lua_State *L);
#endif // CONFIG_LUA_ENABLE_LIB_TABLE

#ifdef CONFIG_LUA_ENABLE_LIB_IO
#define LUA_IOLIBNAME	"io"
LUAMOD_API int (luaopen_io) (lua_State *L);
#endif // CONFIG_LUA_ENABLE_LIB_IO

#ifdef CONFIG_LUA_ENABLE_LIB_OS
#define LUA_OSLIBNAME	"os"
LUAMOD_API int (luaopen_os) (lua_State *L);
#endif // CONFIG_LUA_ENABLE_LIB_OS

#ifdef CONFIG_LUA_ENABLE_LIB_STRING
#define LUA_STRLIBNAME	"string"
LUAMOD_API int (luaopen_string) (lua_State *L);
#endif // CONFIG_LUA_ENABLE_LIB_STRING

#ifdef CONFIG_LUA_ENABLE_LIB_UTF8
#define LUA_UTF8LIBNAME	"utf8"
LUAMOD_API int (luaopen_utf8) (lua_State *L);
#endif // CONFIG_LUA_ENABLE_LIB_UTF8

#ifdef CONFIG_LUA_ENABLE_LIB_MATH
#define LUA_MATHLIBNAME	"math"
LUAMOD_API int (luaopen_math) (lua_State *L);
#endif // CONFIG_LUA_ENABLE_LIB_MATH

#ifdef CONFIG_LUA_ENABLE_LIB_DEBUG
#define LUA_DBLIBNAME	"debug"
LUAMOD_API int (luaopen_debug) (lua_State *L);
#endif // CONFIG_LUA_ENABLE_LIB_DEBUG

#ifdef CONFIG_LUA_ENABLE_LIB_PACKAGE
#define LUA_LOADLIBNAME	"package"
LUAMOD_API int (luaopen_package) (lua_State *L);
#endif // CONFIG_LUA_ENABLE_LIB_DEBUG


/* open all previous libraries */
LUALIB_API void (luaL_openlibs) (lua_State *L);


#endif
