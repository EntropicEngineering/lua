#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define assert0(x) assert(x==0);

static int noop(lua_State *l)
{
    luaL_checktype(l, 1, LUA_TTABLE);
    // Make sure passed value is a table, do not change otherwise
    // Todo: enforce proper keys are set

    return 1;
}

// Adapted from https://gist.github.com/yorung/3df1274632f4fa7fabfc
void _dumpStack(lua_State* L, const char* func, int line)
{
    int top = lua_gettop(L);
    printf("(%s,%d) top=%d\n", func, line, top);
    for (int i = 0; i < top; i++) {
        int positive = top - i;
        int negative = -(i + 1);
        int type = lua_type(L, positive);
        int typeN = lua_type(L, negative);
        assert(type == typeN);
        const char* typeName = lua_typename(L, type);
        printf("%d/%d: type=%s", positive, negative, typeName);
        switch (type) {
        case LUA_TNUMBER:
            printf(" value=%f", lua_tonumber(L, positive));
            break;
        case LUA_TSTRING:
            printf(" value=%s", lua_tostring(L, positive));
            break;
        case LUA_TFUNCTION:
            if (lua_iscfunction(L, positive)) {
                printf(" C:%p", lua_tocfunction(L, positive));
            }
            break;
        }
        printf("\n");
    }
    printf("done\n");
}

#define dumpStack(l) _dumpStack(l, __func__, __LINE__)

void table_to_string(lua_State* l, char* s) {
    lua_getglobal(l, "table_to_string");
    lua_pushvalue(l, -2); // push the previous top
    lua_call(l, 1, 1);
    printf("%s%s\n", s, lua_tostring(l, -1));
    lua_pop(l, 1);
}

#define LUA_OUTPUT_TYPE_TENS 1
#define LUA_OUTPUT_TYPE_ERM 2
#define LUA_OUTPUT_TYPE_LED 3

void create_toyOS(lua_State* l) {
    lua_newtable(l);

    lua_pushstring(l, "TENS");
    lua_pushcfunction(l, noop);
    lua_settable(l, -3);

    lua_pushstring(l, "ERM");
    lua_pushcfunction(l, noop);
    lua_settable(l, -3);

    lua_pushstring(l, "LED");
    lua_pushcfunction(l, noop);
    lua_settable(l, -3);

    lua_pushstring(l, "OUTPUT_TYPE_TENS");
    lua_pushinteger(l, LUA_OUTPUT_TYPE_TENS);
    lua_settable(l, -3);

    lua_pushstring(l, "OUTPUT_TYPE_ERM");
    lua_pushinteger(l, LUA_OUTPUT_TYPE_ERM);
    lua_settable(l, -3);

    lua_pushstring(l, "OUTPUT_TYPE_LED");
    lua_pushinteger(l, LUA_OUTPUT_TYPE_LED);
    lua_settable(l, -3);

    lua_setglobal(l, "toyOS");
}

#define DUMP_BUF_BLOCK_SIZE 1024
typedef struct {
    char*  buf;
    size_t size;
    size_t written;
} dump_buf_t;

int dump_buf_writer(lua_State* l, void* p, size_t sz, void* ud) {
    dump_buf_t* buf = (dump_buf_t*)ud;
    if ((buf->written + sz) >= buf->size) {
        size_t newsize = buf->size;
        while (newsize < (buf->written + sz)) {
            newsize += DUMP_BUF_BLOCK_SIZE;
        }
        buf->buf = realloc(buf->buf, newsize);
        if (buf->buf == 0) {
            return 1;
        }
    }

    memcpy(buf->buf + buf->written, p, sz);
    buf->written += sz;

    return 0;
}

int main (void)
{
    lua_State *l = luaL_newstate();
    luaL_openlibs(l);

    create_toyOS(l);

    assert0(luaL_dofile(l, "util.lua"));

    // load script
    assert0(luaL_loadfile(l, "waves_functional_prototype.lua"));
    lua_call(l, 0, 2); // 0 arguments, 2 returns

    lua_pushvalue(l, -2); // metadata
    table_to_string(l, "metadata table:");
    lua_pop(l, 1);

    dumpStack(l);

    dump_buf_t buf = {
        malloc(DUMP_BUF_BLOCK_SIZE),
        DUMP_BUF_BLOCK_SIZE,
        0
    };

    lua_dump(l, (lua_Writer)dump_buf_writer, &buf, 1); // 1 = strip

    lua_close(l);

    printf("buf.written = %d\n", buf.written);
    printf(" --- Creating new state --- \n");

    l = luaL_newstate();
    luaL_openlibs(l);

    create_toyOS(l);

    assert0(luaL_dofile(l, "util.lua"));

    assert0(luaL_loadbufferx(l, buf.buf, buf.written, "script", "b"));

    dumpStack(l);

    // set up setup
    // setup = {
	// 	timestamp = 0,
	// 	adjust_max = 0xffff,
	// 	active_channels = {
	// 		'OUTPUT_TYPE_TENS',
	// 		'OUTPUT_TYPE_ERM',
	// 		'OUTPUT_TYPE_LED'
	// 	}
	// }
    lua_newtable(l);

    lua_pushstring(l, "timestamp");
    lua_pushinteger(l, 0);
    lua_settable(l, -3);

    lua_pushstring(l, "adjust_max");
    lua_pushinteger(l, 0xffff);
    lua_settable(l, -3);

    lua_pushstring(l, "active_channels");
    { // Create active_channels
	    lua_newtable(l);

	    lua_pushinteger(l, 1); // Indexes start at 1
        lua_pushinteger(l, LUA_OUTPUT_TYPE_TENS);
        lua_settable(l, -3);

        lua_pushinteger(l, 2);
        lua_pushinteger(l, LUA_OUTPUT_TYPE_ERM);
        lua_settable(l, -3);

        lua_pushinteger(l, 3);
        lua_pushinteger(l, LUA_OUTPUT_TYPE_LED);
        lua_settable(l, -3);
	}

    lua_settable(l, -3);
    
    // call script(setup) to get closure, one argument (setup), one result
    lua_call(l, 1, 1);
    int periodic = lua_gettop(l);

    for (float ts=0; ts<10; ts+=0.1) {
        lua_pushvalue(l, periodic);
        lua_pushnumber(l, ts); // timestamp
        lua_pushinteger(l, 0xffff); // adjust
        lua_call(l, 2, 1); // 2 args (timestamp, adjust) one return

        printf("ts: %f, top=%d\n", ts, lua_gettop(l));
        table_to_string(l, "output: "); // print table on top of stack

        lua_pop(l, 1); // pop table
    }

    // Make sure stack is clean (that we haven't been leaking memory). Should be only the `periodic' function.
    lua_pop(l, 1);
    assert(lua_gettop(l) == 0);

    lua_close(l);
    return 0;
}
