#include "main/core.h"
#include "meshop.h"

ex double init(double vertex_size) {
	// in gamemaker, our vertex size is in bytes; here we don't care about
	// bytes and would prefer our vertex size to be in floats
	meshop::init(((int)vertex_size) / 9);
	return 1.0;
}

ex const char* meshop_version() {
	std::cout << "getting meshop version" << std::endl;
	return meshop::version();
}

ex double meshop_transform_position_set(double x, double y, double z) {
	meshop::transform_position_set((float)x, (float)y, (float)z);
	return 1.0;
}

ex double meshop_transform_position(float* data, double len) {
	meshop::transform_position(data, (int)len);
	return 1.0;
}

ex double meshop_transform_center(float* data, double len) {
	meshop::transform_center(data, (int)len);
	return 1.0;
}

ex double meshop_transform_rotate_x(float* data, double len, double angle) {
	meshop::transform_rotate_x(data, (int)len, (float)(angle * 3.141592653 / 180.0));
	return 1.0;
}

ex double meshop_transform_rotate_y(float* data, double len, double angle) {
	meshop::transform_rotate_y(data, (int)len, (float)(angle * 3.141592653 / 180.0));
	return 1.0;
}

ex double meshop_transform_rotate_z(float* data, double len, double angle) {
	meshop::transform_rotate_z(data, (int)len, (float)(angle * 3.141592653 / 180.0));
	return 1.0;
}

ex double meshop_transform_scale(float* data, double len, double scale) {
	meshop::transform_scale(data, (int)len, (float)scale);
	return 1.0;
}

// mirror on an axis
ex double meshop_mirror_axis_x(float* data, double len) {
	meshop::mirror_axis_x(data, (int)len);
	return 1.0;
}

ex double meshop_mirror_axis_y(float* data, double len) {
	meshop::mirror_axis_y(data, (int)len);
	return 1.0;
}

ex double meshop_mirror_axis_z(float* data, double len) {
	meshop::mirror_axis_z(data, (int)len);
	return 1.0;
}

// texture
ex double meshop_flip_tex_u(float* data, double len) {
	meshop::flip_tex_u(data, (int)len);
	return 1.0;
}

ex double meshop_flip_tex_v(float* data, double len) {
	meshop::flip_tex_v(data, (int)len);
	return 1.0;
}

// colour
ex double meshop_set_colour(float* data, double len, double colour) {
	meshop::set_colour(data, (int)len, (int)colour);
	return 1.0;
}

ex double meshop_set_alpha(float* data, double len, double alpha) {
	meshop::set_alpha(data, (int)len, (int)(alpha * 255));
	return 1.0;
}

ex double meshop_set_colour_and_alpha(float* data, double len, double colour, double alpha) {
	meshop::set_colour_and_alpha(data, (int)len, (int)colour, (int)(alpha * 255));
	return 1.0;
}

ex double meshop_invert_alpha(float* data, double len) {
	meshop::invert_alpha(data, (int)len);
	return 1.0;
}

// normals
ex double meshop_set_normals_flat(float* data, double len) {
	meshop::set_normals_flat(data, (int)len);
	return 1.0;
}