#include "meshop.h"

namespace meshop {
	const char* version() {
		return __DRAGO_MESH_OP;
	}

	void init(int vertex_size) {
		meshop::vertex_size = vertex_size;
	}

	// transform
	void transform_position_set(float x, float y, float z) {
		meshop::trans_x = x;
		meshop::trans_y = y;
		meshop::trans_z = z;
	}

	void transform_position(float* data, int len) {
	}

	void transform_center(float* data, int len) {
	}

	void transform_rotate_x(float* data, int len, float angle) {
	}

	void transform_rotate_y(float* data, int len, float angle) {
	}

	void transform_rotate_z(float* data, int len, float angle) {
	}

	void transform_scale(float* data, int len, float scale) {
	}

	// mirror on an axis
	void mirror_axis_x(float* data, int len) {
		for (int i = 0; i < len; i += meshop::vertex_size) {
			data[i + 0] *= -1;
			data[i + 3] *= -1;
		}
	}

	void mirror_axis_y(float* data, int len) {
		for (int i = 0; i < len; i += meshop::vertex_size) {
			data[i + 1] *= -1;
			data[i + 4] *= -1;
		}
	}

	void mirror_axis_z(float* data, int len) {
		for (int i = 0; i < len; i += meshop::vertex_size) {
			data[i + 2] *= -1;
			data[i + 5] *= -1;
		}
	}

	// texture
	void flip_tex_u(float* data, int len) {
		for (int i = 0; i < len; i += meshop::vertex_size) {
			data[i + 6] = 1.0 - data[i + 6];
		}
	}

	void flip_tex_v(float* data, int len) {
		for (int i = 0; i < len; i += meshop::vertex_size) {
			data[i + 7] = 1.0 - data[i + 7];
		}
	}

	// colour
	void reset_colour(float* data, int len) {
	}

	void reset_alpha(float* data, int len) {
	}

	void reset_colour_and_alpha(float* data, int len) {
	}

	void invert_alpha(float* data, int len) {
	}

	// normals
	void set_normals_flat(float* data, int len) {
	}
}