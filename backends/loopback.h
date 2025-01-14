#include "midimonster.h"

int init();
static int loopback_configure(char* option, char* value);
static int loopback_configure_instance(instance* inst, char* option, char* value);
static instance* loopback_instance();
static channel* loopback_channel(instance* inst, char* spec);
static int loopback_set(instance* inst, size_t num, channel** c, channel_value* v);
static int loopback_handle(size_t num, managed_fd* fds);
static int loopback_start();
static int loopback_shutdown();

typedef struct /*_loopback_instance_data*/ {
	size_t n;
	char** name;
} loopback_instance_data;
