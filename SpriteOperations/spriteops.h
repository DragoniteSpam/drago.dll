#ifndef __DRAGO_SPRITE_OP
#define __DRAGO_SPRITE_OP "0.0.1"

#include "main/core.h"
#include "main/dragomath.h"
#include <math.h>
#include <algorithm>
#include "main/dragomath.h"

#define GET_INDEX(x, y, w) ((y) * (w) + (x))

namespace spriteops {
	extern int* cropped_dimensions_output;

	const char* version();
	
	void set_cropped_dimensions_output(int*);
	void get_cropped_dimensions(int*, int, int, int);
	void remove_transparent_colour(int*, int, int);
	void set_alpha(unsigned int*, int, int);

	// if you try to inline these the universe will explode
	// sprite sampling
	unsigned int sample(unsigned int*, int, int, float, float);
	unsigned int sample_pixel(unsigned int*, int, int, float, float);
	unsigned int sample_unfiltered(unsigned int*, int, int, float, float);
	unsigned int sample_pixel_unfiltered(unsigned int*, int, int, float, float);

	Vector4 sample_vec4(unsigned int*, int, int, float, float);
	Vector4 sample_vec4_pixel(unsigned int*, int, int, float, float);
	Vector4 sample_vec4_unfiltered(unsigned int*, int, int, float, float);
	Vector4 sample_vec4_pixel_unfiltered(unsigned int*, int, int, float, float);

	float sample_float(float*, int, int, float, float);
	float sample_float_pixel(float*, int, int, float, float);
	float sample_float_unfiltered(float*, int, int, float, float);
	float sample_float_pixel_unfiltered(float*, int, int, float, float);
	
	// help
	unsigned int merge(unsigned int, unsigned int, float);
	Vector4 merge(Vector4, Vector4, float);
}

#endif