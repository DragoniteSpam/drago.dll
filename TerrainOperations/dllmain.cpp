#include "main/core.h"
#include "terrainops.h"
#include "main/dragomath.h"

ex double terrainops_to_heightmap(float* data, unsigned int* out, double len, double scale) {
	terrainops::to_heightmap(data, out, BYTES2FLOATS(len), (float)scale);
	return 1.0;
}

ex double terrainops_from_heightmap(float* data, unsigned int* in, double len, double scale) {
	terrainops::from_heightmap(data, in, BYTES2FLOATS(len), (float)scale);
	return 1.0;
}

ex double terrainops_build_settings(double swap_zup, double swap_uv) {
	terrainops::build_settings((bool)swap_zup, (bool)swap_uv);
	return 1.0;
}

ex double terrainops_build(float* data, float* out, double len) {
	return (double)terrainops::build(data, out, BYTES2FLOATS(len));
}