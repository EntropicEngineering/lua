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
#     CMake sub-project defining 'lua' target which represents Lua library
#     as well as 'prv_lua' which is the public interface of 'lua' accessible
#     from zephyr.
#     It is assumed that find_package(Zephyr) has been called before
#     including this file.
#

if (CONFIG_PRV_LUA)

    zephyr_library_named(lua)

    zephyr_link_interface(lua)

    set(SOURCE_FILES
            ${ZEPHYR_CURRENT_MODULE_DIR}/lapi.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lauxlib.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lbaselib.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lcode.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lcorolib.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lctype.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/ldblib.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/ldebug.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/ldo.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/ldump.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lfunc.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lgc.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/linit.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/liolib.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/llex.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lmathlib.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lmem.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/loadlib.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lobject.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lopcodes.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/loslib.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lparser.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lstate.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lstring.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lstrlib.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/ltable.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/ltablib.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/ltests.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/ltm.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lundump.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lutf8lib.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lvm.c
            ${ZEPHYR_CURRENT_MODULE_DIR}/lzio.c)

    zephyr_library_sources(${SOURCE_FILES})

    zephyr_library_include_directories(${ZEPHYR_CURRENT_MODULE_DIR})

    # ====================================================================
    # Define 'prv_lua' target that exposes Lua headers to the application.
    # ====================================================================

    zephyr_interface_library_named(prv-lua)

    set(INTERFACE_HEADERS
            ${ZEPHYR_CURRENT_MODULE_DIR}/lauxlib.h
            ${ZEPHYR_CURRENT_MODULE_DIR}/lua.h
            ${ZEPHYR_CURRENT_MODULE_DIR}/luaconf.h
            ${ZEPHYR_CURRENT_MODULE_DIR}/lualib.h)

    set(INTERFACE_INCLUDE_DIR ${ZEPHYR_BINARY_DIR}/include/generated/prv)

    file(COPY ${INTERFACE_HEADERS} DESTINATION ${INTERFACE_INCLUDE_DIR})

    target_include_directories(prv-lua INTERFACE ${INTERFACE_INCLUDE_DIR})

    zephyr_library_link_libraries(prv-lua)

endif()
