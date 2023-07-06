#include "main/core.h"
#include "meshops.h"
#include "building.h"

dllex double meshops_init(double vertex_size) {
	// in gamemaker, our vertex size is in bytes; here we don't care about
	// bytes and would prefer our vertex size to be in floats
	meshops::init(BYTES2FLOATS(vertex_size));
	return 1.0;
}

dllex const char* meshops_version() {
	return meshops::version();
}

// general information
dllex double meshops_get_bounds(float* data, float* out, double len) {
	meshops::get_bounds(data, out, BYTES2FLOATS(len));
	return 1.0;
}

// basic transforms
dllex double meshops_transform_center(float* data, double len) {
	meshops::transform_center(data, BYTES2FLOATS(len));
	return 1.0;
}

dllex double meshops_transform_set_matrix(double x, double y, double z, double xrot, double yrot, double zrot, double xscale, double yscale, double zscale) {
	meshops::transform_set_matrix((float)x, (float)y, (float)z, (float)-xrot, (float)-yrot, (float)-zrot, (float)xscale, (float)yscale, (float)zscale);
	return 1.0;
}

dllex double meshops_transform_set_matrix_raw(double i11, double i12, double i13, double i14, double i21, double i22, double i23, double i24, double i31, double i32, double i33, double i34, double i41, double i42, double i43, double i44) {
	meshops::transform_set_matrix_raw((float)i11, (float)i12, (float)i13, (float)i14, (float)i21, (float)i22, (float)i23, (float)i24, (float)i31, (float)i32, (float)i33, (float)i34, (float)i41, (float)i42, (float)i43, (float)i44);
	return 1.0;
}

dllex double meshops_transform(float* data, double len) {
	meshops::transform(data, BYTES2FLOATS(len));
	return 1.0;
}

dllex double meshops_reverse(float* data, double len) {
	meshops::reverse(data, BYTES2FLOATS(len));
	return 1.0;
}

// axes
dllex double meshops_rotate_up(float* data, double len) {
	meshops::rotate_up(data, BYTES2FLOATS(len));
	return 1.0;
}

dllex double meshops_mirror_axis_x(float* data, double len) {
	meshops::mirror_axis_x(data, BYTES2FLOATS(len));
	return 1.0;
}

dllex double meshops_mirror_axis_y(float* data, double len) {
	meshops::mirror_axis_y(data, BYTES2FLOATS(len));
	return 1.0;
}

dllex double meshops_mirror_axis_z(float* data, double len) {
	meshops::mirror_axis_z(data, BYTES2FLOATS(len));
	return 1.0;
}

// texture
dllex double meshops_flip_tex_u(float* data, double len) {
	meshops::flip_tex_u(data, BYTES2FLOATS(len));
	return 1.0;
}

dllex double meshops_flip_tex_v(float* data, double len) {
	meshops::flip_tex_v(data, BYTES2FLOATS(len));
	return 1.0;
}

// colour
dllex double meshops_set_colour(float* data, double len, double colour) {
	meshops::set_colour(data, BYTES2FLOATS(len), (int)colour);
	return 1.0;
}

dllex double meshops_set_alpha(float* data, double len, double alpha) {
	meshops::set_alpha(data, BYTES2FLOATS(len), (int)(alpha * 255));
	return 1.0;
}

dllex double meshops_set_colour_and_alpha(float* data, double len, double colour, double alpha) {
	meshops::set_colour_and_alpha(data, BYTES2FLOATS(len), (int)colour, (int)(alpha * 255));
	return 1.0;
}

dllex double meshops_invert_alpha(float* data, double len) {
	meshops::invert_alpha(data, BYTES2FLOATS(len));
	return 1.0;
}

dllex double meshops_blend_colour(float* data, double len, double target, double amount) {
	meshops::blend_colour(data, BYTES2FLOATS(len), (unsigned int)target, (float)amount);
	return 1.0;
}

dllex double meshops_multiply_colour(float* data, double len, double target) {
	meshops::multiply_colour(data, BYTES2FLOATS(len), (unsigned int)target);
	return 1.0;
}

// normals
dllex double meshops_set_normals_flat(float* data, double len) {
	meshops::set_normals_flat(data, BYTES2FLOATS(len));
	return 1.0;
}

dllex double meshops_set_normals_smooth(float* data, double len, double threshold) {
	meshops::set_normals_smooth_prepare();
	meshops::set_normals_smooth_calculate(data, BYTES2FLOATS(len));
	meshops::set_normals_smooth_finalize(data, BYTES2FLOATS(len), (float)threshold);
	return 1.0;
}

dllex double meshops_set_normals_smooth_multi_prepare() {
	meshops::set_normals_smooth_prepare();
	return 1.0;
}

dllex double meshops_set_normals_smooth_multi_calculate(float* data, double len) {
	meshops::set_normals_smooth_calculate(data, BYTES2FLOATS(len));
	return 1.0;
}

dllex double meshops_set_normals_smooth_multi_finalize(float* data, double len, double threshold) {
	meshops::set_normals_smooth_finalize(data, BYTES2FLOATS(len), (float)threshold);
	return 1.0;
}

// output
dllex double meshops_export_d3d(float* data, double len, char* out) {
	return (double)(meshops::export_d3d(data, BYTES2FLOATS(len), out));
}

// vertex building
dllex double meshops_vertex_formatted(float* data, float* out, double len, double format) {
	return (double)FLOATS2BYTES((meshops::vertex_formatted(data, out, BYTES2FLOATS(len), (int)format)));
}

dllex double meshops_chunk_settings(double chunk_size, double startx, double starty, double endx, double endy) {
	meshops::chunk_settings((int)chunk_size, (float)startx, (float)starty, (float)endx, (float)endy);
	return 1.0;
}

dllex double meshops_chunk_analyze(float* data, long long* meta, double data_len, double meta_len) {
	meshops::chunk_analyze(data, meta, BYTES2FLOATS(data_len), BYTES2FLOATS(meta_len));
	return 1.0;
}

dllex double meshops_chunk(float* data, long long* meta, double len) {
	meshops::chunk(data, meta, BYTES2FLOATS(len));
	return 1.0;
}