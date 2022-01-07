#ifndef __DRAGO_TERRAIN_OP
#define __DRAGO_TERRAIN_OP "0.0.1"

#include "main/core.h"

namespace terrainops {
	extern bool save_swap_zup;
	extern bool save_swap_uv;
	extern bool save_centered;
	extern int save_density;
	extern float save_width;
	extern float save_height;
	extern float save_scale;

	void to_heightmap(float*, unsigned int*, int, float);
	void from_heightmap(float*, unsigned int*, int, float);
	void build_settings(bool, bool, bool, int, float, float, float);
	long build(float*, float*, int);

	float get_z(float*, int, int);
}

#endif