#ifndef __DRAGO_SPRITE_OP
#define __DRAGO_SPRITE_OP "0.0.1"

#include "main/core.h"

#define BYTES2FLOATS(bytes) (((int)bytes) / 4)

namespace spriteops {
	extern float* dimensions_output;

	const char* version();
	
	void set_cropped_dimensions_output(float*);
	void get_cropped_dimensions(float*, int, int, int, float*);
	void spriteops_remove_transparent_colour(float*, int, int);
}

#endif