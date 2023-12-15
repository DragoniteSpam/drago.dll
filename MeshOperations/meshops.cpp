#include "meshops.h"

namespace meshops {
	Matrix4x4* transform_data = new Matrix4x4();
	int vertex_size = 9;
	std::map<std::string, Vector3>* normal_cache = new std::map<std::string, Vector3>();
	Vector2* uvStart1 = new Vector2();
	Vector2* uvStart2 = new Vector2();
	Vector2* uvEnd1 = new Vector2();
	Vector2* uvEnd2 = new Vector2();

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

	void transform_set_matrix_raw(float i11, float i12, float i13, float i14, float i21, float i22, float i23, float i24, float i31, float i32, float i33, float i34, float i41, float i42, float i43, float i44) {
		transform_data->asArray[0] = i11;
		transform_data->asArray[1] = i12;
		transform_data->asArray[2] = i13;
		transform_data->asArray[3] = i14;
		transform_data->asArray[4] = i21;
		transform_data->asArray[5] = i22;
		transform_data->asArray[6] = i23;
		transform_data->asArray[7] = i24;
		transform_data->asArray[8] = i31;
		transform_data->asArray[9] = i32;
		transform_data->asArray[10] = i33;
		transform_data->asArray[11] = i34;
		transform_data->asArray[12] = i41;
		transform_data->asArray[13] = i42;
		transform_data->asArray[14] = i43;
		transform_data->asArray[15] = i44;
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

		for (int i = 0; i < len; i += vsize) {
			position.w = 1;
			normal.w = 0;
			tangent.w = 0;
			bitangent.w = 0;

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

	void reverse(float* data, int len) {
		// this is by far the least troublesome way to reverse faces
		mirror_axis_generic(data, len, 1.0, 1.0, 1.0);
	}

	// UV transform
	void transform_set_uvs(float startx1, float starty1, float startx2, float starty2, float endx1, float endy1, float endx2, float endy2) {
		meshops::uvStart1->x = startx1;
		meshops::uvStart1->y = starty1;
		meshops::uvStart2->x = startx2;
		meshops::uvStart2->y = starty2;
		meshops::uvEnd1->x = endx1;
		meshops::uvEnd1->y = endy1;
		meshops::uvEnd2->x = endx2;
		meshops::uvEnd2->y = endy2;
	}

	void transform_uvs(float* data, int offset, int vertex_count) {
		int vsize = meshops::vertex_size;
		for (int i = offset; i < offset + vertex_count; i += vsize) {
		}
	}

	// axes
	void rotate_up(float* data, int len) {
		float x, y, z, nx, ny, nz, tx, ty, tz, bix, biy, biz;
		int vsize = meshops::vertex_size;

		for (int i = 0; i < len; i += vsize) {
			x = data[i + 0];
			y = data[i + 1];
			z = data[i + 2];
			nx = data[i + 3];
			ny = data[i + 4];
			nz = data[i + 5];
			tx = data[i + 9];
			ty = data[i + 10];
			tz = data[i + 11];
			bix = data[i + 12];
			biy = data[i + 13];
			biz = data[i + 14];

			data[i + 0] = z;
			data[i + 1] = x;
			data[i + 2] = y;
			data[i + 3] = nz;
			data[i + 4] = nx;
			data[i + 5] = ny;
			data[i + 9] = tz;
			data[i + 10] = tx;
			data[i + 11] = ty;
			data[i + 12] = biz;
			data[i + 13] = bix;
			data[i + 14] = biy;
		}
	}

	void mirror_axis_generic(float* data, int len, float xs, float ys, float zs) {
		Vector3 position1{}, normal1{}, texcoord1{}, tangent1{}, bitangent1{}, barycentric1{};
		Vector3 position2{}, normal2{}, texcoord2{}, tangent2{}, bitangent2{}, barycentric2{};
		Vector3 position3{}, normal3{}, texcoord3{}, tangent3{}, bitangent3{}, barycentric3{};
		unsigned int color1, color2, color3;

		int vsize = meshops::vertex_size;

		// you would hope that this would be simpler, but you have to reverse the
		// triangle direction, so you have to mess with every attribute like this
		for (int i = 0; i < len; i += vsize * 3) {
			position1.x = data[i + 0];
			position1.y = data[i + 1];
			position1.z = data[i + 2];
			normal1.x = data[i + 3];
			normal1.y = data[i + 4];
			normal1.z = data[i + 5];
			texcoord1.x = data[i + 6];
			texcoord1.y = data[i + 7];
			color1 = ((unsigned int*)data)[i + 8];
			tangent1.x = data[i + 9];
			tangent1.y = data[i + 10];
			tangent1.z = data[i + 11];
			bitangent1.x = data[i + 12];
			bitangent1.y = data[i + 13];
			bitangent1.z = data[i + 14];
			barycentric1.x = data[i + 15];
			barycentric1.y = data[i + 16];
			barycentric1.z = data[i + 17];
			position2.x = data[i + 0 + vsize];
			position2.y = data[i + 1 + vsize];
			position2.z = data[i + 2 + vsize];
			normal2.x = data[i + 3 + vsize];
			normal2.y = data[i + 4 + vsize];
			normal2.z = data[i + 5 + vsize];
			texcoord2.x = data[i + 6 + vsize];
			texcoord2.y = data[i + 7 + vsize];
			color2 = ((unsigned int*)data)[i + 8 + vsize];
			tangent2.x = data[i + 9 + vsize];
			tangent2.y = data[i + 10 + vsize];
			tangent2.z = data[i + 11 + vsize];
			bitangent2.x = data[i + 12 + vsize];
			bitangent2.y = data[i + 13 + vsize];
			bitangent2.z = data[i + 14 + vsize];
			barycentric2.x = data[i + 15 + vsize];
			barycentric2.y = data[i + 16 + vsize];
			barycentric2.z = data[i + 17 + vsize];
			position3.x = data[i + 0 + vsize * 2];
			position3.y = data[i + 1 + vsize * 2];
			position3.z = data[i + 2 + vsize * 2];
			normal3.x = data[i + 3 + vsize * 2];
			normal3.y = data[i + 4 + vsize * 2];
			normal3.z = data[i + 5 + vsize * 2];
			texcoord3.x = data[i + 6 + vsize * 2];
			texcoord3.y = data[i + 7 + vsize * 2];
			color3 = ((unsigned int*)data)[i + 8 + vsize * 2];
			tangent3.x = data[i + 9 + vsize * 2];
			tangent3.y = data[i + 10 + vsize * 2];
			tangent3.z = data[i + 11 + vsize * 2];
			bitangent3.x = data[i + 12 + vsize * 2];
			bitangent3.y = data[i + 13 + vsize * 2];
			bitangent3.z = data[i + 14 + vsize * 2];
			barycentric3.x = data[i + 15 + vsize * 2];
			barycentric3.y = data[i + 16 + vsize * 2];
			barycentric3.z = data[i + 17 + vsize * 2];
			data[i + 0] = xs * position1.x;
			data[i + 1] = ys * position1.y;
			data[i + 2] = zs * position1.z;
			data[i + 3] = xs * normal1.x;
			data[i + 4] = ys * normal1.y;
			data[i + 5] = zs * normal1.z;
			data[i + 6] = texcoord1.x;
			data[i + 7] = texcoord1.y;
			((unsigned int*)data)[i + 8] = color1;
			data[i + 9] = xs *  tangent1.x;
			data[i + 10] = ys * tangent1.y;
			data[i + 11] = zs * tangent1.z;
			data[i + 12] = xs * bitangent1.x;
			data[i + 13] = ys * bitangent1.y;
			data[i + 14] = zs * bitangent1.z;
			data[i + 15] = barycentric1.x;
			data[i + 16] = barycentric1.y;
			data[i + 17] = barycentric1.z;
			data[i + 0 + vsize] = xs * position3.x;
			data[i + 1 + vsize] = ys * position3.y;
			data[i + 2 + vsize] = zs * position3.z;
			data[i + 3 + vsize] = xs * normal3.x;
			data[i + 4 + vsize] = ys * normal3.y;
			data[i + 5 + vsize] = zs * normal3.z;
			data[i + 6 + vsize] = texcoord3.x;
			data[i + 7 + vsize] = texcoord3.y;
			((unsigned int*)data)[i  + vsize + 8] = color3;
			data[i + 9 + vsize] = xs * tangent3.x;
			data[i + 10 + vsize] = ys * tangent3.y;
			data[i + 11 + vsize] = zs * tangent3.z;
			data[i + 12 + vsize] = xs * bitangent3.x;
			data[i + 13 + vsize] = ys * bitangent3.y;
			data[i + 14 + vsize] = zs * bitangent3.z;
			data[i + 15 + vsize] = barycentric3.x;
			data[i + 16 + vsize] = barycentric3.y;
			data[i + 17 + vsize] = barycentric3.z;
			data[i + 0 + vsize * 2] = xs * position2.x;
			data[i + 1 + vsize * 2] = ys * position2.y;
			data[i + 2 + vsize * 2] = zs * position2.z;
			data[i + 3 + vsize * 2] = xs * normal2.x;
			data[i + 4 + vsize * 2] = ys * normal2.y;
			data[i + 5 + vsize * 2] = zs * normal2.z;
			data[i + 6 + vsize * 2] = texcoord2.x;
			data[i + 7 + vsize * 2] = texcoord2.y;
			((unsigned int*)data)[i  + vsize * 2 + 8] = color2;
			data[i + 9 + vsize * 2] = xs * tangent2.x;
			data[i + 10 + vsize * 2] = ys * tangent2.y;
			data[i + 11 + vsize * 2] = zs * tangent2.z;
			data[i + 12 + vsize * 2] = xs * bitangent2.x;
			data[i + 13 + vsize * 2] = ys * bitangent2.y;
			data[i + 14 + vsize * 2] = zs * bitangent2.z;
			data[i + 15 + vsize * 2] = barycentric2.x;
			data[i + 16 + vsize * 2] = barycentric2.y;
			data[i + 17 + vsize * 2] = barycentric2.z;
		}
	}

	void mirror_axis_x(float* data, int len) {
		mirror_axis_generic(data, len, -1.0, 1.0, 1.0);
	}

	void mirror_axis_y(float* data, int len) {
		mirror_axis_generic(data, len, 1.0, -1.0, 1.0);
	}

	void mirror_axis_z(float* data, int len) {
		mirror_axis_generic(data, len, 1.0, 1.0, -1.0);
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
			((unsigned int*)data)[i + 8] &= 0xff000000;
			((unsigned int*)data)[i + 8] |= colour;
		}
	}

	void set_alpha(float* data, int len, int alpha) {
		int vsize = meshops::vertex_size;
		unsigned int a = alpha << 24;
		for (int i = 0; i < len; i += vsize) {
			((unsigned int*)data)[i + 8] &= 0x00ffffff;
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

	void blend_colour(float* data, int len, unsigned int target, float amount) {
		int vsize = meshops::vertex_size;
		for (int i = 0; i < len; i += vsize) {
			unsigned int color = ((unsigned int*)data)[i + 8];
			unsigned int alpha = color & 0xff000000;
			color &= 0x00ffffff;
			((unsigned int*)data)[i + 8] = alpha | spriteops::merge(color, target, amount);
		}
	}

	void multiply_colour(float* data, int len, unsigned int target) {
		int vsize = meshops::vertex_size;
		unsigned int tr = target & 0xff;
		unsigned int tg = (target >> 8) & 0xff;
		unsigned int tb = (target >> 16) & 0xff;
		for (int i = 0; i < len; i += vsize) {
			unsigned int color = ((unsigned int*)data)[i + 8];
			unsigned int r = ((color & 0xff) * tr) >> 8;
			unsigned int g = (((color >> 8) & 0xff) * tg) >> 8;
			unsigned int b = (((color >> 16) & 0xff) * tb) >> 8;
			unsigned int a = color & 0xff000000;
			color &= 0x00ffffff;
			((unsigned int*)data)[i + 8] = a | (b << 16) | (g << 8) | r;
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

	void set_normals_smooth_prepare() {
		normal_cache->clear();
	}

	void set_normals_smooth_calculate(float* data, int len) {
		Triangle triangle{ };
		Vector3 vertex{ }, normal{ }, cached{ };
		Vector3 e1{ }, e2{ };
		int vsize = meshops::vertex_size;

		for (int i = 0; i < len; i += vsize * 3) {
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
				if (normal_cache->contains(keys[i])) {
					Vector3* pcached = &(*normal_cache)[keys[i]];
					pcached->x += normal.x;
					pcached->y += normal.y;
					pcached->z += normal.z;
				} else {
					normal_cache->insert(std::pair(keys[i], normal));
				}
			}
		}
	}

	void set_normals_smooth_finalize(float* data, int len, float threshold) {
		Vector3 vertex{ }, normal{ }, cached{ };
		int vsize = meshops::vertex_size;

		for (int i = 0; i < len; i += vsize) {
			vertex.x = data[i + 0];
			vertex.y = data[i + 1];
			vertex.z = data[i + 2];
			normal.x = data[i + 3];
			normal.y = data[i + 4];
			normal.z = data[i + 5];

			cached = (*normal_cache)[std::format("{},{},{}", vertex.x, vertex.y, vertex.z)];
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
		s << "100\r\n" << (vertices + 2) << "\r\n0 4 0 0 0 0 0 0 0 0 0\r\n";

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

		s << "1 0 0 0 0 0 0 0 0 0 0\r\n";
		std::string result = s.str();
		int bytes = (int)result.length();
		result.copy(out, bytes);

		return bytes;
	}
}

#undef DOT
#undef CROSS
#undef MAGNITUDE