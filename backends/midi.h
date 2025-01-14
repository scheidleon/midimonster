#include "midimonster.h"

int init();
static int midi_configure(char* option, char* value);
static int midi_configure_instance(instance* instance, char* option, char* value);
static instance* midi_instance();
static channel* midi_channel(instance* instance, char* spec);
static int midi_set(instance* inst, size_t num, channel** c, channel_value* v);
static int midi_handle(size_t num, managed_fd* fds);
static int midi_start();
static int midi_shutdown();

typedef struct /*_midi_instance_data*/ {
	int port;
	char* read;
	char* write;
} midi_instance_data;

typedef union {
	struct {
		uint8_t pad[5];
		uint8_t type;
		uint8_t channel;
		uint8_t control;
	} fields;
	uint64_t label;
} midi_channel_ident;

