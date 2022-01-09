#ifndef __DRAGO_TERRAIN_OP
#define __DRAGO_TERRAIN_OP "0.0.1"

#include "main/core.h"
#include <math.h>

namespace terrainops {
	extern bool save_all;
	extern bool save_swap_zup;
	extern bool save_swap_uv;
	extern bool save_centered;
	extern int save_density;
	extern float save_width;
	extern float save_height;
	extern float save_scale;

	const char* version();

	void to_heightmap(float*, unsigned int*, int, float);
	void from_heightmap(float*, unsigned int*, int, float);
	void build_settings(bool, bool, bool, bool, int, float, float, float);
	long build(float*, float*, int);
	void generate(float*, float*, int, int);

	float get_z(float*, int, int, int h);
	inline void write_vertex(float*, int*, float, float, float, float, float, unsigned int, float, float, float);
}

#endif