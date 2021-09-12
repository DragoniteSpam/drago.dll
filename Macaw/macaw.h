#ifndef __DRAGO_MACAW
#define __DRAGO_MACAW "1.0.2"

#include "main/core.h"

namespace macaw {
	extern double setting_height;
	extern int setting_octaves;

	const char* version();

	void seed_set(unsigned int);
	void generate(float*, int, int);
	void set_height(double);
	void set_octaves(int);
	float* _gen_white_noise(int, int);
	float* _gen_smooth_noise(float*, int, int, int);
	float interpolate(float, float, float);
}

#endif