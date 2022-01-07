#include "main/core.h"
#include "terrainops.h"

ex double terrainops_to_heightmap(float* data, unsigned int* out, double len) {
	terrainops::to_heightmap(data, out, BYTES2FLOATS(len));
	return 1.0;
}

ex double terrainops_from_heightmap(float* data, unsigned int* in, double len) {
	terrainops::from_heightmap(data, in, BYTES2FLOATS(len));
	return 1.0;
}