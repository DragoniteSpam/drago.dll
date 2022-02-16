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

ex double terrainops_set_active_vertex_data(float* vertex) {
	terrainops::set_active_vertex_data(vertex);
	return 1.0;
}

ex double terrainops_set_lod_vertex_data(float* lod) {
	terrainops::set_lod_vertex_data(lod);
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
ex double terrainops_generate_internal() {
	terrainops::generate_internal();
	return 1.0;
}

ex double terrainops_build_settings(double save_all, double swap_zup, double swap_uv, double center, double density, double scale, double tex_size, double color_scale, double format) {
	terrainops::build_settings((bool)save_all, (bool)swap_zup, (bool)swap_uv, (bool)center, (int)density, (float)scale, (float)tex_size, (float)color_scale, (unsigned int)format);
	return 1.0;
}

ex double terrainops_build_texture(unsigned int* save_texture_map) {
	terrainops::build_texture(save_texture_map);
	return 1.0;
}

ex double terrainops_build_vertex_colour(unsigned int* save_colour_map) {
	terrainops::build_vertex_colour(save_colour_map);
	return 1.0;
}

ex double terrainops_build_bounds(double x1, double y1, double x2, double y2) {
	terrainops::build_bounds((int)x1, (int)y1, (int)x2, (int)y2);
	return 1.0;
}

// output
ex double terrainops_build_d3d(float* out) {
	long long length = 0;
	int vertices = 0;
	std::stringstream content;
	terrainops::build_setup_d3d(out, &content);
	terrainops::build(out, &content, &length, &vertices, &terrainops::build_write_vertex_d3d);
	terrainops::build_cleanup_d3d(out, &content, &length, vertices);
	return (double)length;
}

ex double terrainops_build_obj(float* out) {
	long long length = 0;
	int vertices = 0;
	std::stringstream content;
	terrainops::build_setup_obj(out, &content);
	terrainops::build_obj(out, &content, &length, &vertices);
	terrainops::build_cleanup_obj(out, &content, &length, vertices);
	return (double)length;
}

ex double terrainops_build_vbuff(float* out) {
	long long length = 0;
	int vertices = 0;
	terrainops::build_setup_vbuff(out);
	terrainops::build(out, NULL, &length, &vertices, &terrainops::build_write_vertex_vbuff);
	terrainops::build_cleanup_vbuff(out, &length, vertices);
	return (double)length;
}

// other stuff

ex double terrainops_set_cursor_location_output(float* out) {
	terrainops::set_cursor_location_output(out);
	return 1.0;
}

ex double terrainops_get_cursor_location(double ox, double oy, double oz, double dx, double dy, double dz) {
	terrainops::get_intersecting_triangle((float)ox, (float)oy, (float)oz, (float)dx, (float)dy, (float)dz);
	return 1.0;
}