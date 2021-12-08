#
#   Copyright (c) 2021 Entropic Engineering
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#

#
#   @file
#     CMake sub-project defining 'prv-lua' target which represents Lua library
#     as well as 'lua' which is the public interface of 'lua' accessible
#     from zephyr.
#     It is assumed that find_package(Zephyr) has been called before
#     including this file.
#

if (CONFIG_LUA)

    # ====================================================================
    # Define 'lua' target that exposes Lua headers to the application.
    # ====================================================================

    zephyr_interface_library_named(lua)

    set(INTERFACE_HEADERS
            ${ZEPHYR_CURRENT_MODULE_DIR}/lauxlib.h
            ${ZEPHYR_CURRENT_MODULE_DIR}/lua.h
            ${ZEPHYR_CURRENT_MODULE_DIR}/luaconf.h
            ${ZEPHYR_CURRENT_MODULE_DIR}/lualib.h)

    set(INTERFACE_INCLUDE_DIR ${ZEPHYR_BINARY_DIR}/include/generated/prv/lua)

    file(COPY ${INTERFACE_HEADERS} DESTINATION ${INTERFACE_INCLUDE_DIR})
    file(COPY ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/conf.h DESTINATION ${INTERFACE_INCLUDE_DIR}/zephyr/compat)

    target_include_directories(lua INTERFACE ${INTERFACE_INCLUDE_DIR})

    # ====================================================================
    # Define 'prv-lua' target that builds Lua.
    # ====================================================================

    zephyr_library_named(prv-lua)

    zephyr_library_sources(
            ${ZEPHYR_CURRENT_MODULE_DIR}/lapi.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lcode.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lctype.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/ldebug.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/ldo.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lfunc.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lgc.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/linit.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lmem.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lobject.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lopcodes.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lstate.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lstring.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/ltable.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/ltests.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/ltm.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lvm.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lzio.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/compat.c)

    zephyr_library_sources_ifdef(CONFIG_LUA_ENABLE_LOAD_BINARY
            ${ZEPHYR_CURRENT_MODULE_DIR}/ldump.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lundump.c)

    zephyr_library_sources_ifdef(CONFIG_LUA_ENABLE_LOAD_STRING
            ${ZEPHYR_CURRENT_MODULE_DIR}/lparser.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/llex.c)

    zephyr_library_sources_ifdef(CONFIG_LUA_ENABLE_AUXLIB ${ZEPHYR_CURRENT_MODULE_DIR}/lauxlib.c)

    zephyr_library_sources_ifdef(CONFIG_LUA_ENABLE_LIB_BASE ${ZEPHYR_CURRENT_MODULE_DIR}/lbaselib.c)
    zephyr_library_sources_ifdef(CONFIG_LUA_ENABLE_LIB_DEBUG ${ZEPHYR_CURRENT_MODULE_DIR}/ldblib.c)
    zephyr_library_sources_ifdef(CONFIG_LUA_ENABLE_LIB_COROUTINE ${ZEPHYR_CURRENT_MODULE_DIR}/lcorolib.c)
    zephyr_library_sources_ifdef(CONFIG_LUA_ENABLE_LIB_PACKAGE ${ZEPHYR_CURRENT_MODULE_DIR}/loadlib.c)
    zephyr_library_sources_ifdef(CONFIG_LUA_ENABLE_LIB_TABLE ${ZEPHYR_CURRENT_MODULE_DIR}/ltablib.c)
    zephyr_library_sources_ifdef(CONFIG_LUA_ENABLE_LIB_IO ${ZEPHYR_CURRENT_MODULE_DIR}/liolib.c)
    zephyr_library_sources_ifdef(CONFIG_LUA_ENABLE_LIB_OS ${ZEPHYR_CURRENT_MODULE_DIR}/loslib.c)
    zephyr_library_sources_ifdef(CONFIG_LUA_ENABLE_LIB_STRING ${ZEPHYR_CURRENT_MODULE_DIR}/lstrlib.c)
    zephyr_library_sources_ifdef(CONFIG_LUA_ENABLE_LIB_UTF8 ${ZEPHYR_CURRENT_MODULE_DIR}/lutf8lib.c)

    zephyr_library_sources_ifdef(CONFIG_LUA_ENABLE_LIB_MATH 
            ${ZEPHYR_CURRENT_MODULE_DIR}/lmathlib.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/arm/trigf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/arm/tablesf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/arm/sqrtf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/e_acosf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/e_asinf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/e_atan2f.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/e_coshf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/e_expf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/e_fmodf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/e_log10f.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/e_log2f.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/e_logf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/e_powf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/e_sinhf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/k_expf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/s_atanf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/s_ceilf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/s_copysignf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/s_expm1f.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/s_fabsf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/s_floorf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/s_frexpf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/s_scalbnf.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/math/openlibm/s_tanhf.c)

    zephyr_library_include_directories(${ZEPHYR_CURRENT_MODULE_DIR})

    zephyr_library_include_directories(${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/compat/libc/ BEFORE)

endif()
