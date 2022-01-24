#include "main/core.h"
#include "terrainops.h"
#include "main/dragomath.h"

ex const char* terrainops_version() {
	return terrainops::version();
}

// setup
ex double terrainops_set_active_data(float* data, double w, double h) {
	terrainops::set_active_data(data, (int)w, (int)h);
	return 1.0;
}

ex double terrainops_set_active_vertex_buffers(float* vertex) {
	terrainops::set_active_vertex_buffers(vertex);
	return 1.0;
}

// heightmap
ex double terrainops_to_heightmap(unsigned int* out, double scale) {
	terrainops::to_heightmap(out, (float)scale);
	return 1.0;
}

ex double terrainops_from_heightmap(unsigned int* in, double scale) {
	terrainops::from_heightmap(in, (float)scale);
	return 1.0;
}

// deformation
ex double terrainops_flatten(double height) {
	terrainops::flatten((float)height);
	return 1.0;
}

ex double terrainops_apply_scale(double scale) {
	terrainops::apply_scale((float)scale);
	return 1.0;
}

ex double terrainops_deform_brush(unsigned int* brush, double w, double h) {
	terrainops::deform_brush(brush, (float)w, (float)h);
	return 1.0;
}

ex double terrainops_deform_brush_settings(double radius, double velocity) {
	terrainops::deform_brush_settings((float)radius, (float)velocity);
	return 1.0;
}

ex double terrainops_deform_brush_position(double x, double y) {
	terrainops::deform_brush_set_position((float)x, (float)y);
	return 1.0;
}

ex double terrainops_deform_mold() {
	terrainops::invoke_deformation(false, &terrainops::deform_mold);
	return 1.0;
}

ex double terrainops_deform_average() {
	terrainops::invoke_deformation(true, &terrainops::deform_average);
	return 1.0;
}

ex double terrainops_deform_zero() {
	terrainops::invoke_deformation(false, &terrainops::deform_zero);
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

ex double terrainops_mutate() {
	terrainops::mutate();
	return 1.0;
}

// vertex buffer generation
ex double terrainops_generate_internal(float* out) {
	terrainops::generate_internal(out);
	return 1.0;
}

ex double terrainops_build_settings(double save_all, double swap_zup, double swap_uv, double center, double density, double width, double height, double scale) {
	terrainops::build_settings((bool)save_all, (bool)swap_zup, (bool)swap_uv, (bool)center, (int)density, (int)width, (int)height, (float)scale);
	return 1.0;
}

ex double terrainops_build(long long* meta, double meta_len) {
	return (double)terrainops::build(meta, BYTES2DOUBLES(meta_len));
}