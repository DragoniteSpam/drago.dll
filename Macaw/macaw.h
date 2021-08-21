#ifndef __DRAGO_MACAW
#define __DRAGO_MACAW "0.0.1"

#include "main/core.h"

namespace macaw {
	const char* version();

	void seed_set(unsigned int);
	void generate(float*, int, int, int);
	float* _gen_white_noise(int, int);
	float* _gen_smooth_noise(float*, int, int, int);
	float interpolate(float, float, float);
}

#endif