
#include <logging/log.h>
#include "zephyr/compat/compat.h"
#include <kernel.h>
#include <random/rand32.h>
#include <stdlib.h>

LOG_MODULE_REGISTER(lua_compat, LOG_LEVEL_DBG);

#define STUB() LOG_ERR("lua/zephyrcompat/compat.c: %s invoked!", __func__); while (1) abort();

l_noret lua_compat_throw(lua_State *L, struct lua_longjmp *errorJmp) { STUB(); }

const char * strerror(int e) {
	LOG_ERR("strerror -> %d", e);
	return "E???";
}

const char * strpbrk (const char * s, const char * accept ) {
	// TODO: More efficient implementation?

	while ((*s) != 0) {
		const char* c = accept;
		while ((*c) != 0) {
			if ((*s) == (*c)) return s;
			c++;
		}
		s++;
	}

	return NULL;
}

int strcoll (const char * str1, const char * str2 ) {
	// TODO: More efficient implementation?

	while (((*str1) != 0) && ((*str2) != 0)) {
		int d = (*str1) - (*str2);
		if (d!=0) return d;
		str1++;
		str2++;
	}

	return 0;
}

int isdigit(char x) {
	return (x >= '0') && (x <= '9');
}

int islower(char c) { return ('a' <= c) && ('z' >= c); }
int ispunct(char c) {
	char *s = "~!@#$%^&*()_+`-=;:'\"\\|[]{},./<>?";
	while ((*s) != 0) {
		if ((*s) == c) return 1;
		s++;
	}
	return 0;
}


unsigned int lua_compat_get_cycle32() {
	// TODO: Need to reimplement these so that they don't cause MPU fault in userland
	return k_cycle_get_32();
}

unsigned int lua_compat_get_rand32() {
	// TODO: Need to reimplement these so that they don't cause MPU fault in userland
	return sys_rand32_get();
}

__weak void lua_compat_writestring(void *ud, const char* s, const int l) {
	LOG_INF("lua: %.*s", l, s);
}

__weak void lua_compat_writestringerror(void *ud, const char* f, const char* s){
	LOG_ERR("lua: ERROR: %s", s);
}

