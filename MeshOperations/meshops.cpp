#include "meshops.h"

namespace meshops {
	Matrix4x4* transform_data = new Matrix4x4();
	int vertex_size = 9;

	const char* version() {
		return __DRAGO_MESH_OP;
	}

	void init(int vertex_size) {
		meshops::vertex_size = vertex_size;
	}

	// get information
	void get_bounds(float* data, float* out, int len) {
		float minx = 10000000, miny = 10000000, minz = 10000000;
		float maxx = -10000000, maxy = -10000000, maxz = -10000000;
		int vsize = meshops::vertex_size;
		for (int i = 0; i < len; i += vsize) {
			minx = std::min(minx, data[i + 0]);
			miny = std::min(miny, data[i + 1]);
			minz = std::min(minz, data[i + 2]);
			maxx = std::max(maxx, data[i + 0]);
			maxy = std::max(maxy, data[i + 1]);
			maxz = std::max(maxz, data[i + 2]);
		}
		out[0] = minx;
		out[1] = miny;
		out[2] = minz;
		out[3] = maxx;
		out[4] = maxy;
		out[5] = maxz;
	}
	
	// transform
	void transform_center(float* data, int len) {
		int vsize = meshops::vertex_size;
		float total_x = 0;
		float total_y = 0;

		for (int i = 0; i < len; i += vsize) {
			total_x += data[i + 0];
			total_y += data[i + 1];
		}

		total_x /= (float)(len / vsize);
		total_y /= (float)(len / vsize);

		for (int i = 0; i < len; i += vsize) {
			data[i + 0] -= total_x;
			data[i + 1] -= total_y;
		}
	}

	void transform_set_matrix(float x, float y, float z, float xrot, float yrot, float zrot, float xscale, float yscale, float zscale) {
		Matrix4x4 let_me_use_pointers_dammit = Matrix4x4::Transform(x, y, z, xrot, yrot, zrot, xscale, yscale, zscale);
		for (int i = 0; i < 16; i++) {
			meshops::transform_data->asArray[i] = let_me_use_pointers_dammit.asArray[i];
		}
	}

	void transform(float* data, int len) {
		int vsize = meshops::vertex_size;
		Vector4 position{}, normal{}, tangent{}, bitangent{};
		Matrix4x4 mat = *meshops::transform_data;
		position.w = 1;
		normal.w = 0;
		tangent.w = 0;
		bitangent.w = 0;

		for (int i = 0; i < len; i += vsize) {
			position.x = data[i + 0];
			position.y = data[i + 1];
			position.z = data[i + 2];
			normal.x = data[i + 3];
			normal.y = data[i + 4];
			normal.z = data[i + 5];
			tangent.x = data[i + 9];
			tangent.y = data[i + 10];
			tangent.z = data[i + 11];
			bitangent.x = data[i + 12];
			bitangent.y = data[i + 13];
			bitangent.z = data[i + 14];

			position.Transform(&mat);
			normal.Transform(&mat);
			tangent.Transform(&mat);
			bitangent.Transform(&mat);
			normal.Normalize();
			tangent.Normalize();
			bitangent.Normalize();

			data[i + 0] = position.x;
			data[i + 1] = position.y;
			data[i + 2] = position.z;
			if (!CMP(normal.Dot(&normal), 0.0f)) {
				data[i + 3] = normal.x;
				data[i + 4] = normal.y;
				data[i + 5] = normal.z;
				data[i + 9] = tangent.x;
				data[i + 10] = tangent.y;
				data[i + 11] = tangent.z;
				data[i + 12] = bitangent.x;
				data[i + 13] = bitangent.y;
				data[i + 14] = bitangent.z;
			}
		}
	}

	// axes
	void rotate_up(float* data, int len) {
		float x, y, z, nx, ny, nz;
		int vsize = meshops::vertex_size;

		for (int i = 0; i < len; i += vsize) {
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
		int vsize = meshops::vertex_size;
		int iteration = vsize * 3;

		for (int i = 0; i < len; i += iteration) {
			x1 = data[i + 0];
			y1 = data[i + 1];
			z1 = data[i + 2];
			x2 = data[i + 0 + vsize];
			y2 = data[i + 1 + vsize];
			z2 = data[i + 2 + vsize];
			x3 = data[i + 0 + vsize * 2];
			y3 = data[i + 1 + vsize * 2];
			z3 = data[i + 2 + vsize * 2];
			data[i + 0] = -x1;
			data[i + 1] = -y1;
			data[i + 2] = -z1;
			data[i + 0 + vsize] = -x3;
			data[i + 1 + vsize] = -y3;
			data[i + 2 + vsize] = -z3;
			data[i + 0 + vsize * 2] = -x2;
			data[i + 1 + vsize * 2] = -y2;
			data[i + 2 + vsize * 2] = -z2;
		}
	}

	void mirror_axis_y(float* data, int len) {
		float x1, x2, x3, y1, y2, y3, z1, z2, z3;
		int vsize = meshops::vertex_size;
		int iteration = vsize * 3;

		for (int i = 0; i < len; i += iteration) {
			x1 = data[i + 0];
			y1 = data[i + 1];
			z1 = data[i + 2];
			x2 = data[i + 0 + vsize];
			y2 = data[i + 1 + vsize];
			z2 = data[i + 2 + vsize];
			x3 = data[i + 0 + vsize * 2];
			y3 = data[i + 1 + vsize * 2];
			z3 = data[i + 2 + vsize * 2];
			data[i + 0] = -x1;
			data[i + 1] = -y1;
			data[i + 2] = -z1;
			data[i + 0 + vsize] = -x3;
			data[i + 1 + vsize] = -y3;
			data[i + 2 + vsize] = -z3;
			data[i + 0 + vsize * 2] = -x2;
			data[i + 1 + vsize * 2] = -y2;
			data[i + 2 + vsize * 2] = -z2;
		}
	}

	void mirror_axis_z(float* data, int len) {
		float x1, x2, x3, y1, y2, y3, z1, z2, z3;
		int vsize = meshops::vertex_size;
		int iteration = vsize * 3;

		for (int i = 0; i < len; i += iteration) {
			x1 = data[i + 0];
			y1 = data[i + 1];
			z1 = data[i + 2];
			x2 = data[i + 0 + vsize];
			y2 = data[i + 1 + vsize];
			z2 = data[i + 2 + vsize];
			x3 = data[i + 0 + vsize * 2];
			y3 = data[i + 1 + vsize * 2];
			z3 = data[i + 2 + vsize * 2];
			data[i + 0] = -x1;
			data[i + 1] = -y1;
			data[i + 2] = -z1;
			data[i + 0 + vsize] = -x3;
			data[i + 1 + vsize] = -y3;
			data[i + 2 + vsize] = -z3;
			data[i + 0 + vsize * 2] = -x2;
			data[i + 1 + vsize * 2] = -y2;
			data[i + 2 + vsize * 2] = -z2;
		}
	}

	// texture
	void flip_tex_u(float* data, int len) {
		int vsize = meshops::vertex_size;
		for (int i = 0; i < len; i += vsize) {
			data[i + 6] = 1 - data[i + 6];
		}
	}

	void flip_tex_v(float* data, int len) {
		int vsize = meshops::vertex_size;
		for (int i = 0; i < len; i += vsize) {
			data[i + 7] = 1 - data[i + 7];
		}
	}

	// colour
	void set_colour(float* data, int len, int colour) {
		int vsize = meshops::vertex_size;
		for (int i = 0; i < len; i += vsize) {
			((unsigned int*)data)[i + 8] |= colour;
		}
	}

	void set_alpha(float* data, int len, int alpha) {
		int vsize = meshops::vertex_size;
		unsigned int a = alpha << 24;
		for (int i = 0; i < len; i += vsize) {
			((unsigned int*)data)[i + 8] |= a;
		}
	}

	void set_colour_and_alpha(float* data, int len, int colour, int alpha) {
		int vsize = meshops::vertex_size;
		unsigned int value = colour | (alpha << 24);
		for (int i = 0; i < len; i += vsize) {
			((int*)data)[i + 8] = value;
		}
	}

	void invert_alpha(float* data, int len) {
		int vsize = meshops::vertex_size;
		for (int i = 0; i < len; i += vsize) {
			unsigned int value = ((unsigned int*)data)[i + 8];
			unsigned int a = (0xff - (value >> 24)) << 24;
			((unsigned int*)data)[i + 8] = a | (value & 0x00ffffff);
		}
	}

	// normals
	void set_normals_flat(float* data, int len) {
		Triangle triangle{ };
		Vector3 e1{ }, e2{ };
		Vector3 normal{ };
		int vsize = meshops::vertex_size;

		for (int i = 0; i < len; i += meshops::vertex_size * 3) {
			triangle.a.x = data[i + 0];
			triangle.a.y = data[i + 1];
			triangle.a.z = data[i + 2];
			triangle.b.x = data[i + 0 + vsize];
			triangle.b.y = data[i + 1 + vsize];
			triangle.b.z = data[i + 2 + vsize];
			triangle.c.x = data[i + 0 + vsize * 2];
			triangle.c.y = data[i + 1 + vsize * 2];
			triangle.c.z = data[i + 2 + vsize * 2];

			e1.x = triangle.b.x - triangle.a.x;
			e1.y = triangle.b.y - triangle.a.y;
			e1.z = triangle.b.z - triangle.a.z;
			e2.x = triangle.c.x - triangle.a.x;
			e2.y = triangle.c.y - triangle.a.y;
			e2.z = triangle.c.z - triangle.a.z;

			CROSS(normal, e1, e2);
			NORMALIZE(normal);

			data[i + 3] = normal.x;
			data[i + 4] = normal.y;
			data[i + 5] = normal.z;
			data[i + 3 + vsize] = normal.x;
			data[i + 4 + vsize] = normal.y;
			data[i + 5 + vsize] = normal.z;
			data[i + 3 + vsize * 2] = normal.x;
			data[i + 4 + vsize * 2] = normal.y;
			data[i + 5 + vsize * 2] = normal.z;
		}
	}

	void set_normals_smooth(float* data, int len, float threshold) {
		Triangle triangle{ };
		Vector3 vertex{ }, normal{ }, cached{ };
		Vector3 e1{ }, e2{ };
		int vsize = meshops::vertex_size;

		std::map<std::string, Vector3> cache;

		for (int i = 0; i < len; i += meshops::vertex_size * 3) {
			triangle.a.x = data[i + 0];
			triangle.a.y = data[i + 1];
			triangle.a.z = data[i + 2];
			triangle.b.x = data[i + 0 + vsize];
			triangle.b.y = data[i + 1 + vsize];
			triangle.b.z = data[i + 2 + vsize];
			triangle.c.x = data[i + 0 + vsize * 2];
			triangle.c.y = data[i + 1 + vsize * 2];
			triangle.c.z = data[i + 2 + vsize * 2];

			e1.x = triangle.b.x - triangle.a.x;
			e1.y = triangle.b.y - triangle.a.y;
			e1.z = triangle.b.z - triangle.a.z;
			e2.x = triangle.c.x - triangle.a.x;
			e2.y = triangle.c.y - triangle.a.y;
			e2.z = triangle.c.z - triangle.a.z;

			CROSS(normal, e1, e2);
			NORMALIZE(normal);

			data[i + 3] = normal.x;
			data[i + 4] = normal.y;
			data[i + 5] = normal.z;
			data[i + 3 + vsize] = normal.x;
			data[i + 4 + vsize] = normal.y;
			data[i + 5 + vsize] = normal.z;
			data[i + 3 + vsize * 2] = normal.x;
			data[i + 4 + vsize * 2] = normal.y;
			data[i + 5 + vsize * 2] = normal.z;
			
			std::string keys[] = {
				std::format("{},{},{}", triangle.a.x, triangle.a.y, triangle.a.z),
				std::format("{},{},{}", triangle.b.x, triangle.b.y, triangle.b.z),
				std::format("{},{},{}", triangle.c.x, triangle.c.y, triangle.c.z)
			};

			for (int i = 0; i < 3; i++) {
				if (cache.contains(keys[i])) {
					Vector3* pcached = &cache[keys[i]];
					pcached->x += normal.x;
					pcached->y += normal.y;
					pcached->z += normal.z;
				} else {
					cache.insert(std::pair(keys[i], normal));
				}
			}
		}

		for (int i = 0; i < len; i += meshops::vertex_size) {
			vertex.x = data[i + 0];
			vertex.y = data[i + 1];
			vertex.z = data[i + 2];
			normal.x = data[i + 3];
			normal.y = data[i + 4];
			normal.z = data[i + 5];

			cached = cache[std::format("{},{},{}", vertex.x, vertex.y, vertex.z)];
			NORMALIZE(cached);
			if (DOT(normal, cached) > threshold) {
				data[i + 3] = cached.z;
				data[i + 4] = cached.y;
				data[i + 5] = cached.x;
			}
		}
	}

	// output
	int export_d3d(float* data, int len, char* out) {
		std::stringstream s;
		int vertices = len / meshops::vertex_size;
		s << "100\r\n" << (vertices + 2) << "\r\n0 4\r\n";

		for (int i = 0; i < len; i += vertex_size) {
			unsigned int c = ((unsigned int*)data)[i + 8];
			s << std::format(
				"9 {:.6f} {:.6f} {:.6f} {:.6f} {:.6f} {:.6f} {:.6f} {:.6f} {} {:.2f}\r\n",
				data[i + 0], data[i + 1], data[i + 2],
				data[i + 3], data[i + 4], data[i + 5],
				data[i + 6], data[i + 7],
				c & 0x00ffffff, (c >> 24) / 255.0
			);
		}

		s << "1\r\n";
		std::string result = s.str();
		int bytes = (int)result.length();
		result.copy(out, bytes);

		return bytes;
	}
}

#undef DOT
#undef CROSS
#undef MAGNITUDE