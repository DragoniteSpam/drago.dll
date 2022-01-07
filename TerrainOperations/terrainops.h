#ifndef __DRAGO_TERRAIN_OP
#define __DRAGO_TERRAIN_OP "0.0.1"

#include "main/core.h"

namespace terrainops {
	extern bool swap_zup;
	extern bool swap_uv;
	extern float save_scale;

	void to_heightmap(float*, unsigned int*, int, float);
	void from_heightmap(float*, unsigned int*, int, float);
	void build_settings(bool, bool, double);
	long build(float*, float*, int);
}

#endif