#ifndef __DRAGO_MACAW
#define __DRAGO_MACAW "0.0.1"

#include "main/core.h"

namespace macaw {
	const char* version();

	void generate(int, int, int);
	float[][] _gen_white_noise(int, int);
	float[][] _gen_smooth_noise(float[][], int);
}

#endif