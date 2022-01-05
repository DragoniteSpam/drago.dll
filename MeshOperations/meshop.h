#ifndef __DRAGO_MESH_OP
#define __DRAGO_MESH_OP "0.0.1"

#include "main/core.h"

namespace meshop {
	float trans_x = 0;
	float trans_y = 0;
	float trans_z = 0;

	const char* version();

	// transform
	void transform_position_set(float, float, float);
	void transform_position(float*, int);
	void transform_center(float*, int);
	void transform_rotate_x(float*, int, float);
	void transform_rotate_y(float*, int, float);
	void transform_rotate_z(float*, int, float);
	void transform_scale(float*, int, float);

	// mirror on axis
	void mirror_axis_x(float*, int);
	void mirror_axis_y(float*, int);
	void mirror_axis_z(float*, int);

	// texture
	void flip_tex_u(float*, int);
	void flip_tex_v(float*, int);

	// color and alpha
	void reset_colour(float*, int);
	void reset_alpha(float*, int);
	void reset_colour_and_alpha(float*, int);
	void invert_alpha(float*, int);

	// normals
	void set_normals_flat(float*, int);
}

#endif