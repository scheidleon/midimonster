#include "midimonster.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

//OSX and Windows don't have the cool new toys...
#ifdef __linux__
	#define MMBACKEND_LUA_TIMERFD
#endif

int init();
static int lua_configure(char* option, char* value);
static int lua_configure_instance(instance* inst, char* option, char* value);
static instance* lua_instance();
static channel* lua_channel(instance* inst, char* spec);
static int lua_set(instance* inst, size_t num, channel** c, channel_value* v);
static int lua_handle(size_t num, managed_fd* fds);
static int lua_start();
static int lua_shutdown();
static uint32_t lua_interval();

typedef struct /*_lua_instance_data*/ {
	size_t channels;
	char** channel_name;
	int* reference;
	double* input;
	double* output;
	lua_State* interpreter;
} lua_instance_data;

typedef struct /*_lua_interval_callback*/ {
	uint64_t interval;
	uint64_t delta;
	lua_State* interpreter;
	int reference;
} lua_timer;
