#ifndef __DRAGO_FALCON
#define __DRAGO_FALCON "1.0.2"

#define FALCON_BATCH_DATA_SIZE 4

#include "falcon.h"

namespace falcon {
	extern int vertex_size;

	const char* version();
	void set_vertex_size(int);
	void combine(float*, float*, double);
}

#endif