#include "meshops.h"

#define DOT(vec3) (vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z)
#define MAGNITUDE(vec3) sqrtf(DOT(vec3))
#define NORMALIZE(vec3) { float mag = MAGNITUDE(vec3); vec3.x /= mag; vec3.y /= mag; vec3.z /= mag; }

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

		total_x /= len / meshops::vertex_size;
		total_y /= len / meshops::vertex_size;

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
			data[i + 4] = data[i + 4] * cosf(angle) - data[i + 5] * sinf(angle);
			data[i + 5] = data[i + 4] * sinf(angle) - data[i + 5] * cosf(angle);
		}
	}

	void transform_rotate_y(float* data, int len, float angle) {
		for (int i = 0; i < len; i += meshops::vertex_size) {
			data[i + 0] = data[i + 2] * sinf(angle) - data[i + 0] * cosf(angle);
			data[i + 2] = data[i + 2] * cosf(angle) - data[i + 0] * sinf(angle);
			data[i + 3] = data[i + 5] * sinf(angle) - data[i + 3] * cosf(angle);
			data[i + 5] = data[i + 5] * cosf(angle) - data[i + 3] * sinf(angle);
		}
	}

	void transform_rotate_z(float* data, int len, float angle) {
		for (int i = 0; i < len; i += meshops::vertex_size) {
			data[i + 0] = data[i + 0] * cosf(angle) - data[i + 1] * sinf(angle);
			data[i + 1] = data[i + 0] * sinf(angle) - data[i + 1] * cosf(angle);
			data[i + 3] = data[i + 3] * cosf(angle) - data[i + 4] * sinf(angle);
			data[i + 4] = data[i + 3] * sinf(angle) - data[i + 4] * cosf(angle);
		}
	}

	void transform_scale(float* data, int len, float scale) {
		for (int i = 0; i < len; i += meshops::vertex_size) {
			data[i + 0] *= scale;
			data[i + 1] *= scale;
			data[i + 2] *= scale;
		}
	}

	// axes
	void rotate_up(float* data, int len) {
		float x, y, z, nx, ny, nz;

		for (int i = 0; i < len; i += meshops::vertex_size) {
			x = data[i + 0];
			y = data[i + 1];
			z = data[i + 2];
			nx = data[i + 3];
			ny = data[i + 4];
			nz = data[i + 5];
			data[i + 0] = y;
			data[i + 1] = z;
			data[i + 2] = x;
			data[i + 3] = ny;
			data[i + 4] = nz;
			data[i + 5] = nx;
		}
	}

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
			data[i + 1] = -y1;
			data[i + 2] = -z1;
			data[i + 0 + meshops::vertex_size] = -x3;
			data[i + 1 + meshops::vertex_size] = -y3;
			data[i + 2 + meshops::vertex_size] = -z3;
			data[i + 0 + meshops::vertex_size * 2] = -x2;
			data[i + 1 + meshops::vertex_size * 2] = -y2;
			data[i + 2 + meshops::vertex_size * 2] = -z2;
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
			data[i + 0] = -x1;
			data[i + 1] = -y1;
			data[i + 2] = -z1;
			data[i + 0 + meshops::vertex_size] = -x3;
			data[i + 1 + meshops::vertex_size] = -y3;
			data[i + 2 + meshops::vertex_size] = -z3;
			data[i + 0 + meshops::vertex_size * 2] = -x2;
			data[i + 1 + meshops::vertex_size * 2] = -y2;
			data[i + 2 + meshops::vertex_size * 2] = -z2;
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
			data[i + 0] = -x1;
			data[i + 1] = -y1;
			data[i + 2] = -z1;
			data[i + 0 + meshops::vertex_size] = -x3;
			data[i + 1 + meshops::vertex_size] = -y3;
			data[i + 2 + meshops::vertex_size] = -z3;
			data[i + 0 + meshops::vertex_size * 2] = -x2;
			data[i + 1 + meshops::vertex_size * 2] = -y2;
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
		Triangle triangle;
		Vector3 cross, e1, e2;
		float cpl;

		for (int i = 0; i < len; i += meshops::vertex_size * 3) {
			triangle.a.x = data[i + 0];
			triangle.a.y = data[i + 1];
			triangle.a.z = data[i + 2];
			triangle.b.x = data[i + 0 + meshops::vertex_size];
			triangle.b.y = data[i + 1 + meshops::vertex_size];
			triangle.b.z = data[i + 2 + meshops::vertex_size];
			triangle.c.x = data[i + 0 + meshops::vertex_size * 2];
			triangle.c.y = data[i + 1 + meshops::vertex_size * 2];
			triangle.c.z = data[i + 2 + meshops::vertex_size * 2];

			e1.x = triangle.b.x - triangle.a.x;
			e1.y = triangle.b.y - triangle.a.y;
			e1.z = triangle.b.z - triangle.a.z;
			e2.x = triangle.c.x - triangle.a.x;
			e2.y = triangle.c.y - triangle.a.y;
			e2.z = triangle.c.z - triangle.a.z;

			Vector3 normal{
				e1.y * e2.z - e1.z * e2.y,
				-e1.x * e2.z + e1.z * e2.x,
				e1.x * e2.y - e1.y * e2.x,
			};

			NORMALIZE(normal);

			data[i + 3] = normal.x;
			data[i + 4] = normal.y;
			data[i + 5] = normal.z;
			data[i + 3 + meshops::vertex_size] = normal.x;
			data[i + 4 + meshops::vertex_size] = normal.y;
			data[i + 5 + meshops::vertex_size] = normal.z;
			data[i + 3 + meshops::vertex_size * 2] = normal.x;
			data[i + 4 + meshops::vertex_size * 2] = normal.y;
			data[i + 5 + meshops::vertex_size * 2] = normal.z;
		}
	}

	void set_normals_smooth(float* data, int len, float threshold) {
		Triangle triangle;
		Vector3 cross, e1, e2;
		float cpl;

		std::map<std::string, Vector3> cache;

		for (int i = 0; i < len; i += meshops::vertex_size * 3) {
			triangle.a.x = data[i + 0];
			triangle.a.y = data[i + 1];
			triangle.a.z = data[i + 2];
			triangle.b.x = data[i + 0 + meshops::vertex_size];
			triangle.b.y = data[i + 1 + meshops::vertex_size];
			triangle.b.z = data[i + 2 + meshops::vertex_size];
			triangle.c.x = data[i + 0 + meshops::vertex_size * 2];
			triangle.c.y = data[i + 1 + meshops::vertex_size * 2];
			triangle.c.z = data[i + 2 + meshops::vertex_size * 2];

			e1.x = triangle.b.x - triangle.a.x;
			e1.y = triangle.b.y - triangle.a.y;
			e1.z = triangle.b.z - triangle.a.z;
			e2.x = triangle.c.x - triangle.a.x;
			e2.y = triangle.c.y - triangle.a.y;
			e2.z = triangle.c.z - triangle.a.z;
			
			Vector3 normal {
				e1.y * e2.z - e1.z * e2.y,
				-e1.x * e2.z + e1.z * e2.x,
				e1.x * e2.y - e1.y * e2.x,
			};

			NORMALIZE(normal);

			data[i + 3] = normal.x;
			data[i + 4] = normal.y;
			data[i + 5] = normal.z;
			data[i + 3 + meshops::vertex_size] = normal.x;
			data[i + 4 + meshops::vertex_size] = normal.y;
			data[i + 5 + meshops::vertex_size] = normal.z;
			data[i + 3 + meshops::vertex_size * 2] = normal.x;
			data[i + 4 + meshops::vertex_size * 2] = normal.y;
			data[i + 5 + meshops::vertex_size * 2] = normal.z;

			std::string keys[] = {
				std::format("{},{},{}", triangle.a.x, triangle.a.y, triangle.a.z),
				std::format("{},{},{}", triangle.b.x, triangle.b.y, triangle.b.z),
				std::format("{},{},{}", triangle.c.x, triangle.c.y, triangle.c.z)
			};

			for (int i = 0; i < 3; i++) {
				if (cache.contains(keys[i])) {
					Vector3* cached = &cache[keys[i]];
					cached->x += normal.x;
					cached->y += normal.y;
					cached->z += normal.z;
				} else {
					cache.insert(std::pair(keys[i], normal));
				}
			}
		}

		Vector3 vertex, normal;
		for (int i = 0; i < len; i += meshops::vertex_size) {
			vertex.x = data[i + 0];
			vertex.y = data[i + 1];
			vertex.z = data[i + 2];
			normal.x = data[i + 3];
			normal.y = data[i + 4];
			normal.z = data[i + 5];

			Vector3 cached = cache[std::format("{},{},{}", vertex.x, vertex.y, vertex.z)];
			NORMALIZE(cached);
			if (DOT(normal, cached) > threshold) {
				data[i + 3] = cached.z;
				data[i + 4] = cached.y;
				data[i + 5] = cached.x;
			}
		}
	}
}

#undef DOT
#undef CROSS
#undef MAGNITUDE