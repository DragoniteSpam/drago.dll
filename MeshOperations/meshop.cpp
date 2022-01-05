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
		for (int i = 0; i < len; i += meshop::vertex_size) {
			data[i + 0] += meshop::trans_x;
			data[i + 1] += meshop::trans_y;
			data[i + 2] += meshop::trans_z;
		}
	}

	void transform_center(float* data, int len) {
	}

	// could do these with matrices but for set axes i'm pretty sure this is faster
	void transform_rotate_x(float* data, int len, float angle) {
		for (int i = 0; i < len; i += meshop::vertex_size) {
			data[i + 1] = data[i + 1] * cos(angle) - data[i + 2] * sin(angle);
			data[i + 2] = data[i + 1] * sin(angle) - data[i + 2] * cos(angle);
		}
	}

	void transform_rotate_y(float* data, int len, float angle) {
		for (int i = 0; i < len; i += meshop::vertex_size) {
			data[i + 0] = data[i + 2] * sin(angle) - data[i + 0] * cos(angle);
			data[i + 2] = data[i + 2] * cos(angle) - data[i + 0] * sin(angle);
		}
	}

	void transform_rotate_z(float* data, int len, float angle) {
		for (int i = 0; i < len; i += meshop::vertex_size) {
			data[i + 0] = data[i + 0] * cos(angle) - data[i + 1] * sin(angle);
			data[i + 1] = data[i + 0] * sin(angle) - data[i + 1] * cos(angle);
		}
	}

	void transform_scale(float* data, int len, float scale) {
		for (int i = 0; i < len; i += meshop::vertex_size) {
			data[i + 0] *= scale;
			data[i + 1] *= scale;
			data[i + 2] *= scale;
		}
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
		for (int i = 0; i < len; i += meshop::vertex_size) {
			((int*)data)[i + 8] |= 0x00ffffff;
		}
	}

	void reset_alpha(float* data, int len) {
		for (int i = 0; i < len; i += meshop::vertex_size) {
			((int*)data)[i + 8] |= 0xff000000;
		}
	}

	void reset_colour_and_alpha(float* data, int len) {
		for (int i = 0; i < len; i += meshop::vertex_size) {
			((int*)data)[i + 8] = 0xffffffff;
		}
	}

	void invert_alpha(float* data, int len) {
		for (int i = 0; i < len; i += meshop::vertex_size) {
			int value = ((int*)data)[i + 8];
			int a = (0xff - (value >> 24)) << 24;
			((int*)data)[i + 8] = a | (value & 0x00ffffff);
		}
	}

	// normals
	void set_normals_flat(float* data, int len) {
	}
}