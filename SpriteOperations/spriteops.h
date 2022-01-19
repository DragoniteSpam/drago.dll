#ifndef __DRAGO_SPRITE_OP
#define __DRAGO_SPRITE_OP "0.0.1"

#include "main/core.h"
#include "main/dragomath.h"
#include <math.h>
#include <algorithm>

#define GET_INDEX(i, j, w) ((j) * (w) + (i))

namespace spriteops {
	extern int* cropped_dimensions_output;

	const char* version();
	
	void set_cropped_dimensions_output(int*);
	void get_cropped_dimensions(int*, int, int, int);
	void spriteops_remove_transparent_colour(int*, int, int);

	// sprite sampling
	int sample(int*, int, int, float, float);
	int sample_pixel(int*, int, int, float, float);
	
	int merge(int, int, float);
}

#endif