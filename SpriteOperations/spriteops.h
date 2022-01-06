#ifndef __DRAGO_SPRITE_OP
#define __DRAGO_SPRITE_OP "0.0.1"

#include "main/core.h"

#define BYTES2FLOATS(bytes) (((int)bytes) / 4)

namespace spriteops {
	const char* version();
	
	void get_cropped_dimensions(float*, int, float*);
	void spriteops_remove_transparent_colour(float*, int, int);
}

#endif