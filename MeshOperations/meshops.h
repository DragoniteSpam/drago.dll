#ifndef __DRAGO_MESH_OP
#define __DRAGO_MESH_OP "0.0.1"

#include "main/core.h"
#include <math.h>
#include <stdio.h>
#include <map>
#include <string>
#include <format>

#define BYTES2FLOATS(bytes) (((int)bytes) / 4)

namespace meshops {
	extern float trans_x;
	extern float trans_y;
	extern float trans_z;
	extern int vertex_size;
	
	// data structures
	struct Vector3 {
		float x, y, z;
	};

	struct Triangle {
		Vector3 a, b, c;
	};

	const char* version();
	void init(int);

	// transform
	void transform_position_set(float, float, float);
	void transform_position(float*, int);
	void transform_center(float*, int);
	void transform_rotate_x(float*, int, float);
	void transform_rotate_y(float*, int, float);
	void transform_rotate_z(float*, int, float);
	void transform_scale(float*, int, float);

	// axes
	void rotate_up(float*, int);
	void mirror_axis_x(float*, int);
	void mirror_axis_y(float*, int);
	void mirror_axis_z(float*, int);

	// texture
	void flip_tex_u(float*, int);
	void flip_tex_v(float*, int);

	// color and alpha
	void set_colour(float*, int, int);
	void set_alpha(float*, int, int);
	void set_colour_and_alpha(float*, int, int, int);
	void invert_alpha(float*, int);

	// normals
	void set_normals_flat(float*, int);
	void set_normals_smooth(float*, int, float);
}

#endif