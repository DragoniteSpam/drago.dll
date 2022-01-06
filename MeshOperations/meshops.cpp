#include "meshops.h"

namespace meshops {
	float trans_x = 0;
	float trans_y = 0;
	float trans_z = 0;
	int vertex_size = 9;

	const char* version() {
		return __DRAGO_MESH_OP;
	}

	void init(int vertex_size) {
		meshops::vertex_size = vertex_size;
	}

	// transform
	void transform_position_set(float x, float y, float z) {
		meshops::trans_x = x;
		meshops::trans_y = y;
		meshops::trans_z = z;
	}

	void transform_position(float* data, int len) {
		for (int i = 0; i < len; i += meshops::vertex_size) {
			data[i + 0] += meshops::trans_x;
			data[i + 1] += meshops::trans_y;
			data[i + 2] += meshops::trans_z;
		}
	}

	void transform_center(float* data, int len) {
		float total_x = 0;
		float total_y = 0;

		for (int i = 0; i < len; i += meshops::vertex_size) {
			total_x += data[i + 0];
			total_y += data[i + 1];
		}

		total_x /= len;
		total_y /= len;

		for (int i = 0; i < len; i += meshops::vertex_size) {
			data[i + 0] -= total_x;
			data[i + 1] -= total_y;
		}
	}

	// could do these with matrices but for set axes i'm pretty sure this is faster
	void transform_rotate_x(float* data, int len, float angle) {
		for (int i = 0; i < len; i += meshops::vertex_size) {
			data[i + 1] = data[i + 1] * cosf(angle) - data[i + 2] * sinf(angle);
			data[i + 2] = data[i + 1] * sinf(angle) - data[i + 2] * cosf(angle);
		}
	}

	void transform_rotate_y(float* data, int len, float angle) {
		for (int i = 0; i < len; i += meshops::vertex_size) {
			data[i + 0] = data[i + 2] * sinf(angle) - data[i + 0] * cosf(angle);
			data[i + 2] = data[i + 2] * cosf(angle) - data[i + 0] * sinf(angle);
		}
	}

	void transform_rotate_z(float* data, int len, float angle) {
		for (int i = 0; i < len; i += meshops::vertex_size) {
			data[i + 0] = data[i + 0] * cosf(angle) - data[i + 1] * sinf(angle);
			data[i + 1] = data[i + 0] * sinf(angle) - data[i + 1] * cosf(angle);
		}
	}

	void transform_scale(float* data, int len, float scale) {
		for (int i = 0; i < len; i += meshops::vertex_size) {
			data[i + 0] *= scale;
			data[i + 1] *= scale;
			data[i + 2] *= scale;
		}
	}

	// mirror on an axis
	void mirror_axis_x(float* data, int len) {
		float x1, x2, x3, y1, y2, y3, z1, z2, z3;

		for (int i = 0; i < len; i += meshops::vertex_size * 3) {
			x1 = data[i + 0];
			y1 = data[i + 1];
			z1 = data[i + 2];
			x2 = data[i + 0 + meshops::vertex_size];
			y2 = data[i + 1 + meshops::vertex_size];
			z2 = data[i + 2 + meshops::vertex_size];
			x3 = data[i + 0 + meshops::vertex_size * 2];
			y3 = data[i + 1 + meshops::vertex_size * 2];
			z3 = data[i + 2 + meshops::vertex_size * 2];
			data[i + 0] = -x1;
			data[i + 1] = y1;
			data[i + 2] = z1;
			data[i + 0 + meshops::vertex_size] = -x3;
			data[i + 1 + meshops::vertex_size] = y3;
			data[i + 2 + meshops::vertex_size] = z3;
			data[i + 0 + meshops::vertex_size * 2] = -x2;
			data[i + 1 + meshops::vertex_size * 2] = y2;
			data[i + 2 + meshops::vertex_size * 2] = z2;
		}
	}

	void mirror_axis_y(float* data, int len) {
		float x1, x2, x3, y1, y2, y3, z1, z2, z3;

		for (int i = 0; i < len; i += meshops::vertex_size * 3) {
			x1 = data[i + 0];
			y1 = data[i + 1];
			z1 = data[i + 2];
			x2 = data[i + 0 + meshops::vertex_size];
			y2 = data[i + 1 + meshops::vertex_size];
			z2 = data[i + 2 + meshops::vertex_size];
			x3 = data[i + 0 + meshops::vertex_size * 2];
			y3 = data[i + 1 + meshops::vertex_size * 2];
			z3 = data[i + 2 + meshops::vertex_size * 2];
			data[i + 0] = x1;
			data[i + 1] = -y1;
			data[i + 2] = z1;
			data[i + 0 + meshops::vertex_size] = x3;
			data[i + 1 + meshops::vertex_size] = -y3;
			data[i + 2 + meshops::vertex_size] = z3;
			data[i + 0 + meshops::vertex_size * 2] = x2;
			data[i + 1 + meshops::vertex_size * 2] = -y2;
			data[i + 2 + meshops::vertex_size * 2] = z2;
		}
	}

	void mirror_axis_z(float* data, int len) {
		float x1, x2, x3, y1, y2, y3, z1, z2, z3;

		for (int i = 0; i < len; i += meshops::vertex_size * 3) {
			x1 = data[i + 0];
			y1 = data[i + 1];
			z1 = data[i + 2];
			x2 = data[i + 0 + meshops::vertex_size];
			y2 = data[i + 1 + meshops::vertex_size];
			z2 = data[i + 2 + meshops::vertex_size];
			x3 = data[i + 0 + meshops::vertex_size * 2];
			y3 = data[i + 1 + meshops::vertex_size * 2];
			z3 = data[i + 2 + meshops::vertex_size * 2];
			data[i + 0] = x1;
			data[i + 1] = y1;
			data[i + 2] = -z1;
			data[i + 0 + meshops::vertex_size] = x3;
			data[i + 1 + meshops::vertex_size] = y3;
			data[i + 2 + meshops::vertex_size] = -z3;
			data[i + 0 + meshops::vertex_size * 2] = x2;
			data[i + 1 + meshops::vertex_size * 2] = y2;
			data[i + 2 + meshops::vertex_size * 2] = -z2;
		}
	}

	// texture
	void flip_tex_u(float* data, int len) {
		for (int i = 0; i < len; i += meshops::vertex_size) {
			data[i + 6] = 1 - data[i + 6];
		}
	}

	void flip_tex_v(float* data, int len) {
		for (int i = 0; i < len; i += meshops::vertex_size) {
			data[i + 7] = 1 - data[i + 7];
		}
	}

	// colour
	void set_colour(float* data, int len, int colour) {
		for (int i = 0; i < len; i += meshops::vertex_size) {
			((unsigned int*)data)[i + 8] |= colour;
		}
	}

	void set_alpha(float* data, int len, int alpha) {
		unsigned int a = alpha << 24;
		for (int i = 0; i < len; i += meshops::vertex_size) {
			((unsigned int*)data)[i + 8] |= a;
		}
	}

	void set_colour_and_alpha(float* data, int len, int colour, int alpha) {
		unsigned int value = colour | (alpha << 24);
		for (int i = 0; i < len; i += meshops::vertex_size) {
			((int*)data)[i + 8] = value;
		}
	}

	void invert_alpha(float* data, int len) {
		for (int i = 0; i < len; i += meshops::vertex_size) {
			unsigned int value = ((unsigned int*)data)[i + 8];
			unsigned int a = (0xff - (value >> 24)) << 24;
			((unsigned int*)data)[i + 8] = a | (value & 0x00ffffff);
		}
	}

	// normals
	void set_normals_flat(float* data, int len) {
		float x1, x2, x3, y1, y2, y3, z1, z2, z3;
		float v1x, v1y, v1z, v2x, v2y, v2z;
		float cx, cy, cz;
		float cpl;
		float nx, ny, nz;

		for (int i = 0; i < len; i += meshops::vertex_size * 3) {
			x1 = data[i + 0];
			y1 = data[i + 1];
			z1 = data[i + 2];
			x2 = data[i + 0 + meshops::vertex_size];
			y2 = data[i + 1 + meshops::vertex_size];
			z2 = data[i + 2 + meshops::vertex_size];
			x3 = data[i + 0 + meshops::vertex_size * 2];
			y3 = data[i + 1 + meshops::vertex_size * 2];
			z3 = data[i + 2 + meshops::vertex_size * 2];

			v1x = x2 - x1;
			v1y = y2 - y1;
			v1z = z2 - z1;
			v2x = x3 - x1;
			v2y = y3 - y1;
			v2z = z3 - z1;
			cx = v1y * v2z - v1z * v2y;
			cy = -v1x * v2z + v1z * v2x;
			cz = v1x * v2y - v1y * v2x;

			cpl = sqrtf(cx * cx + cy * cy + cz * cz);

			nx = cx / cpl;
			ny = cy / cpl;
			nz = cz / cpl;

			data[i + 3] = nx;
			data[i + 4] = ny;
			data[i + 5] = nz;
			data[i + 3 + meshops::vertex_size] = nx;
			data[i + 4 + meshops::vertex_size] = ny;
			data[i + 5 + meshops::vertex_size] = nz;
			data[i + 3 + meshops::vertex_size * 2] = nx;
			data[i + 4 + meshops::vertex_size * 2] = ny;
			data[i + 5 + meshops::vertex_size * 2] = nz;
		}
	}
}