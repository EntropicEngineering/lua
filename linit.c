/*
** $Id: linit.c $
** Initialization of libraries for lua.c and other clients
** See Copyright Notice in lua.h
*/


#define linit_c
#define LUA_LIB

/*
** If you embed Lua in your program and need to open the standard
** libraries, call luaL_openlibs in your program. If you need a
** different set of libraries, copy this file to your project and edit
** it to suit your needs.
**
** You can also *preload* libraries, so that a later 'require' can
** open the library, which is already linked to the application.
** For that, do the following code:
**
**  luaL_getsubtable(L, LUA_REGISTRYINDEX, LUA_PRELOAD_TABLE);
**  lua_pushcfunction(L, luaopen_modname);
**  lua_setfield(L, -2, modname);
**  lua_pop(L, 1);  // remove PRELOAD table
*/

#include "lprefix.h"


#include <stddef.h>

#include "lua.h"

#include "lualib.h"
#include "lauxlib.h"


/*
** these libs are loaded by lua.c and are readily available to any Lua
** program
*/
static const luaL_Reg loadedlibs[] = {
#ifdef CONFIG_LUA_ENABLE_LIB_BASE
  {LUA_GNAME, luaopen_base},
#endif // CONFIG_LUA_ENABLE_LIB_BASE

#ifdef CONFIG_LUA_ENABLE_LIB_PACKAGE
  {LUA_LOADLIBNAME, luaopen_package},
#endif // CONFIG_LUA_ENABLE_LIB_PACKAGE

#ifdef CONFIG_LUA_ENABLE_LIB_COROUTINE
  {LUA_COLIBNAME, luaopen_coroutine},
#endif // CONFIG_LUA_ENABLE_LIB_COROUTINE

#ifdef CONFIG_LUA_ENABLE_LIB_TABLE
  {LUA_TABLIBNAME, luaopen_table},
#endif // CONFIG_LUA_ENABLE_LIB_TABLE

#ifdef CONFIG_LUA_ENABLE_LIB_IO
  {LUA_IOLIBNAME, luaopen_io},
#endif // CONFIG_LUA_ENABLE_LIB_IO

#ifdef CONFIG_LUA_ENABLE_LIB_OS
  {LUA_OSLIBNAME, luaopen_os},
#endif // CONFIG_LUA_ENABLE_LIB_OS

#ifdef CONFIG_LUA_ENABLE_LIB_STRING
  {LUA_STRLIBNAME, luaopen_string},
#endif // CONFIG_LUA_ENABLE_LIB_STRING

#ifdef CONFIG_LUA_ENABLE_LIB_MATH
  {LUA_MATHLIBNAME, luaopen_math},
#endif // CONFIG_LUA_ENABLE_LIB_MATH

#ifdef CONFIG_LUA_ENABLE_LIB_UTF8
  {LUA_UTF8LIBNAME, luaopen_utf8},
#endif // CONFIG_LUA_ENABLE_LIB_UTF8

#ifdef CONFIG_LUA_ENABLE_LIB_DEBUG
  {LUA_DBLIBNAME, luaopen_debug},
#endif // CONFIG_LUA_ENABLE_LIB_DEBUG

  {NULL, NULL}
};


LUALIB_API void luaL_openlibs (lua_State *L) {
  const luaL_Reg *lib;
  /* "require" functions from 'loadedlibs' and set results to global table */
  for (lib = loadedlibs; lib->func; lib++) {
    luaL_requiref(L, lib->name, lib->func, 1);
    lua_pop(L, 1);  /* remove lib */
  }
}

