#include "main/core.h"
#include "meshops.h"
#include "building.h"

ex double meshops_init(double vertex_size) {
	// in gamemaker, our vertex size is in bytes; here we don't care about
	// bytes and would prefer our vertex size to be in floats
	meshops::init(BYTES2FLOATS(vertex_size));
	return 1.0;
}

ex const char* meshops_version() {
	return meshops::version();
}

ex double meshops_transform_position_set(double x, double y, double z) {
	meshops::transform_position_set((float)x, (float)y, (float)z);
	return 1.0;
}

ex double meshops_transform_position(float* data, double len) {
	meshops::transform_position(data, BYTES2FLOATS(len));
	return 1.0;
}

ex double meshops_transform_center(float* data, double len) {
	meshops::transform_center(data, BYTES2FLOATS(len));
	return 1.0;
}

ex double meshops_transform_rotate_x(float* data, double len, double angle) {
	meshops::transform_rotate_x(data, BYTES2FLOATS(len), (float)(angle * 3.141592653 / 180.0));
	return 1.0;
}

ex double meshops_transform_rotate_y(float* data, double len, double angle) {
	meshops::transform_rotate_y(data, BYTES2FLOATS(len), (float)(angle * 3.141592653 / 180.0));
	return 1.0;
}

ex double meshops_transform_rotate_z(float* data, double len, double angle) {
	meshops::transform_rotate_z(data, BYTES2FLOATS(len), (float)(angle * 3.141592653 / 180.0));
	return 1.0;
}

ex double meshops_transform_scale(float* data, double len, double scale) {
	meshops::transform_scale(data, BYTES2FLOATS(len), (float)scale);
	return 1.0;
}

// axes
ex double meshops_rotate_up(float* data, double len) {
	meshops::rotate_up(data, BYTES2FLOATS(len));
	return 1.0;
}

ex double meshops_mirror_axis_x(float* data, double len) {
	meshops::mirror_axis_x(data, BYTES2FLOATS(len));
	return 1.0;
}

ex double meshops_mirror_axis_y(float* data, double len) {
	meshops::mirror_axis_y(data, BYTES2FLOATS(len));
	return 1.0;
}

ex double meshops_mirror_axis_z(float* data, double len) {
	meshops::mirror_axis_z(data, BYTES2FLOATS(len));
	return 1.0;
}

// texture
ex double meshops_flip_tex_u(float* data, double len) {
	meshops::flip_tex_u(data, BYTES2FLOATS(len));
	return 1.0;
}

ex double meshops_flip_tex_v(float* data, double len) {
	meshops::flip_tex_v(data, BYTES2FLOATS(len));
	return 1.0;
}

// colour
ex double meshops_set_colour(float* data, double len, double colour) {
	meshops::set_colour(data, BYTES2FLOATS(len), (int)colour);
	return 1.0;
}

ex double meshops_set_alpha(float* data, double len, double alpha) {
	meshops::set_alpha(data, BYTES2FLOATS(len), (int)(alpha * 255));
	return 1.0;
}

ex double meshops_set_colour_and_alpha(float* data, double len, double colour, double alpha) {
	meshops::set_colour_and_alpha(data, BYTES2FLOATS(len), (int)colour, (int)(alpha * 255));
	return 1.0;
}

ex double meshops_invert_alpha(float* data, double len) {
	meshops::invert_alpha(data, BYTES2FLOATS(len));
	return 1.0;
}

// normals
ex double meshops_set_normals_flat(float* data, double len) {
	meshops::set_normals_flat(data, BYTES2FLOATS(len));
	return 1.0;
}

ex double meshops_set_normals_smooth(float* data, double len, double threshold) {
	meshops::set_normals_smooth(data, BYTES2FLOATS(len), (float)threshold);
	return 1.0;
}

// output
ex double meshops_export_d3d(float* data, double len, char* out) {
	return (double)(meshops::export_d3d(data, BYTES2FLOATS(len), out));
}

// vertex building
ex double meshops_vertex_formatted(float* data, float* out, double len, double format) {
	// don't do the BYTES2FLOATS conversion here!
	return (double)(meshops::vertex_formatted(data, out, (int)len, (int)format));
}