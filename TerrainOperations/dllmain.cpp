#include "main/core.h"
#include "terrainops.h"
#include "main/dragomath.h"

ex const char* terrainops_version() {
	return terrainops::version();
}

ex double terrainops_to_heightmap(float* data, unsigned int* out, double len, double scale) {
	terrainops::to_heightmap(data, out, BYTES2FLOATS(len), (float)scale);
	return 1.0;
}

ex double terrainops_from_heightmap(float* data, unsigned int* in, double len, double scale) {
	terrainops::from_heightmap(data, in, BYTES2FLOATS(len), (float)scale);
	return 1.0;
}

ex double terrainops_flatten(float* data, float* vertex, double len, double height) {
	terrainops::flatten(data, vertex, BYTES2FLOATS(len), (float)height);
	return 1.0;
}

ex double terrainops_apply_scale(float* data, float* vertex, double len, double scale) {
	terrainops::apply_scale(data, vertex, BYTES2FLOATS(len), (float)scale);
	return 1.0;
}

ex double terrainops_generate(float* data, float* out, double width, double height) {
	terrainops::generate(data, out, (int)width, (int)height);
	return 1.0;
}

ex double terrainops_build_settings(double save_all, double swap_zup, double swap_uv, double center, double density, double width, double height, double scale) {
	terrainops::build_settings((bool)save_all, (bool)swap_zup, (bool)swap_uv, (bool)center, (int)density, (float)width, (float)height, (float)scale);
	return 1.0;
}

ex double terrainops_build(float* data, long long* meta, double len, double meta_len) {
	return (double)terrainops::build(data, meta, BYTES2FLOATS(len), BYTES2FLOATS(meta_len));
}