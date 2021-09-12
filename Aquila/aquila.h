#ifndef __DRAGO_AQUILA
#define __DRAGO_AQUILA "0.0.1"

#include "main/core.h"

namespace aquila {
	const char* version();

	void add_node(int);
	void remove_node(int);
	void connect_nodes(int, int);
	void disconnect_nodes(int, int);
	void clear_nodes();
	void navigate();
}

#endif