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

    # ===============================================
    # Define 'lua' target that compiles Lua binaries.
    # ===============================================

    set(SOURCE_FILES
            lapi.c
            lauxlib.c
            lbaselib.c
            lcode.c
            lcorolib.c
            lctype.c
            ldblib.c
            ldebug.c
            ldo.c
            ldump.c
            lfunc.c
            lgc.c
            linit.c
            liolib.c
            llex.c
            lmathlib.c
            lmem.c
            loadlib.c
            lobject.c
            lopcodes.c
            loslib.c
            lparser.c
            lstate.c
            lstring.c
            lstrlib.c
            ltable.c
            ltablib.c
            ltests.c
            ltm.c
            lundump.c
            lutf8lib.c
            lvm.c
            lzio.c)

    add_library(lua STATIC ${SOURCE_FILES})

    target_include_directories(lua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    # ====================================================================
    # Define 'prv_lua' target that exposes Lua headers to the application.
    # ====================================================================

    zephyr_interface_library_named(prv_lua)

    set(INTERFACE_HEADERS lauxlib.h lua.h luaconf.h lualib.h)

    set(INTERFACE_INCLUDE_DIR ${ZEPHYR_BINARY_DIR}/include/generated/prv)

    file(COPY ${INTERFACE_HEADERS} DESTINATION ${INTERFACE_INCLUDE_DIR})

    target_include_directories(prv_lua INTERFACE ${INTERFACE_INCLUDE_DIR})

    target_link_libraries(prv_lua INTERFACE lua)

endif()
