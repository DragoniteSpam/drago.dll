#ifndef __DRAGO_MACAW
#define __DRAGO_MACAW "1.0.3"

#include "main/core.h"
#include "main/dragomath.h"

namespace macaw {
	extern float setting_height;
	extern int setting_octaves;

	const char* version();

	void seed_set(unsigned int);
	void generate(float*, int, int);
	void set_height(float);
	void set_octaves(int);
	float* _gen_white_noise(int, int);
	float* _gen_smooth_noise(float*, int, int, int);

	void to_sprite(float*, int*, int);
	void to_vbuff(float*, float*, int, int);
}

#endif