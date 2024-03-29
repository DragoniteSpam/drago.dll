#ifndef __DRAGO_MESH_OP
#define __DRAGO_MESH_OP "1.0.1"

#include "main/core.h"
#include "main/dragomath.h"
#include <SpriteOperations/spriteops.h>
#include <math.h>
#include <map>
#include <string>
#include <format>
#include <sstream>

namespace meshops {
	extern Matrix4x4* transform_data;
	extern int vertex_size;
	extern std::map<std::string, Vector3>* normal_cache;
	extern Vector2* uvStart1;
	extern Vector2* uvStart2;
	extern Vector2* uvEnd1;
	extern Vector2* uvEnd2;
	
	const char* version();
	void init(int);

	// general information
	void get_bounds(float*, float*, int);

	// transform
	void transform_center(float*, int);
	void transform_set_matrix(float, float, float, float, float, float, float, float, float);
	void transform_set_matrix_raw(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
	void transform(float*, int);
	void reverse(float*, int);
	// UV transform
	void transform_set_uvs(float, float, float, float, float, float, float, float);
	void transform_uvs(float*, int, int);
	// axes
	void rotate_up(float*, int);
	void mirror_axis_generic(float*, int, float, float, float);
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
	void blend_colour(float*, int, unsigned int, float);
	void multiply_colour(float*, int, unsigned int);

	// normals
	void set_normals_flat(float*, int);
	void set_normals_smooth_prepare();
	void set_normals_smooth_calculate(float*, int);
	void set_normals_smooth_finalize(float*, int, float);

	// output
	int export_d3d(float*, int, char*);
}

#endif