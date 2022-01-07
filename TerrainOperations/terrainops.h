#ifndef __DRAGO_TERRAIN_OP
#define __DRAGO_TERRAIN_OP "0.0.1"

#include "main/core.h"

namespace terrainops {
	void to_heightmap(float*, unsigned int*, int, double);
	void from_heightmap(float*, unsigned int*, int, double);
}

#endif