#include "main/core.h"
#include "terrainops.h"
#include "main/dragomath.h"

ex const char* terrainops_version() {
	return terrainops::version();
}

// heightmap
ex double terrainops_to_heightmap(float* data, unsigned int* out, double len, double scale) {
	terrainops::to_heightmap(data, out, BYTES2FLOATS(len), (float)scale);
	return 1.0;
}

ex double terrainops_from_heightmap(float* data, unsigned int* in, double len, double scale) {
	terrainops::from_heightmap(data, in, BYTES2FLOATS(len), (float)scale);
	return 1.0;
}

// deformation
ex double terrainops_flatten(float* data, float* vertex, double len, double height) {
	terrainops::flatten(data, vertex, BYTES2FLOATS(len), (float)height);
	return 1.0;
}

ex double terrainops_apply_scale(float* data, float* vertex, double len, double scale) {
	terrainops::apply_scale(data, vertex, BYTES2FLOATS(len), (float)scale);
	return 1.0;
}

ex double terrainops_deform_brush(float* brush, double w, double h) {
	terrainops::deform_brush(brush, (int)w, (int)h);
	return 1.0;
}

ex double terrainops_deform_brush_settings(double radius, double velocity) {
	terrainops::deform_brush_settings((float)radius, (float)velocity);
	return 1.0;
}

ex double terrainops_deform_brush_position(double x, double y) {
	terrainops::deform_brush_set_position((int)x, (int)y);
	return 1.0;
}

ex double terrainops_deform_mold(float* data, double w, double h) {
	terrainops::deform_mold(data, (int)w, (int)h);
	return 1.0;
}

ex double terrainops_deform_average(float* data, double w, double h) {
	terrainops::deform_average(data, (int)w, (int)h);
	return 1.0;
}

ex double terrainops_deform_average_flat(float* data, double w, double h) {
	terrainops::deform_average_flat(data, (int)w, (int)h);
	return 1.0;
}

ex double terrainops_deform_zero(float* data, double w, double h) {
	terrainops::deform_zero(data, (int)w, (int)h);
	return 1.0;
}

// mutation
ex double terrainops_mutate_set_noise(float* noise, double w, double h, double strength) {
	terrainops::mutate_set_noise(noise, (int)w, (int)h, (float)strength);
	return 1.0;
}

ex double terrainops_mutate_set_texture(unsigned int* texture, double w, double h, double strength) {
	terrainops::mutate_set_texture(texture, (int)w, (int)h, (float)strength);
	return 1.0;
}

ex double terrainops_mutate(float* data, float* vertex, double w, double h) {
	terrainops::mutate(data, vertex, (int)w, (int)h);
	return 1.0;
}

// vertex buffer generation
ex double terrainops_generate(float* data, float* out, double width, double height) {
	terrainops::generate(data, out, (int)width, (int)height);
	return 1.0;
}

ex double terrainops_build_settings(double save_all, double swap_zup, double swap_uv, double center, double density, double width, double height, double scale) {
	terrainops::build_settings((bool)save_all, (bool)swap_zup, (bool)swap_uv, (bool)center, (int)density, (int)width, (int)height, (float)scale);
	return 1.0;
}

ex double terrainops_build(float* data, long long* meta, double len, double meta_len) {
	return (double)terrainops::build(data, meta, BYTES2FLOATS(len), BYTES2DOUBLES(meta_len));
}