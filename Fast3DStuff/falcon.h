#ifndef __DRAGO_FALCON
#define __DRAGO_FALCON "1.0.2"

#define FALCON_BATCH_DATA_SIZE 4
#define FALCON_BATCH_DATA_SIZE_COLOR 5

#include "falcon.h"

namespace falcon {
	extern int vertex_size;
	extern int vertex_color_offset;

	const char* version();
	void set_vertex_size(int);
	void combine(float*, float*, double);

	void combine_color(float*, float*, double);
}

#endif