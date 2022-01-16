#include <algorithm>
#include "terrainops.h"

namespace terrainops {
	bool save_all = true;
	bool save_swap_zup = false;
	bool save_swap_uv = false;
	bool save_centered = false;
	int save_density = 1;
	float save_width = 1;
	float save_height = 1;
	float save_scale = 1;

	const char* version() {
		return __DRAGO_TERRAIN_OP;
	}

	void to_heightmap(float* data, unsigned int* out, int len, float scale) {
		int z;
		for (int i = 0; i < len; i++) {
			z = std::clamp((int)(data[i] * scale), 0, 255);
			out[i] = 0xff000000 | (z | (z << 8) | (z << 16));
		}
	}

	void from_heightmap(float* data, unsigned int* in, int len, float scale) {
		int z;
		for (int i = 0; i < len; i++) {
			// maybe you want to use the other channels to store some other information idk
			z = in[i] & 0x000000ff;
			data[i] = z / scale;
		}
	}

	void flatten(float* data, float* vertex, int len, float height) {
		for (int i = 0; i < len; i++) {
			data[i] = height;
			vertex[i * 18 + 2] = height;
			vertex[i * 18 + 5] = height;
			vertex[i * 18 + 8] = height;
			vertex[i * 18 + 11] = height;
			vertex[i * 18 + 14] = height;
			vertex[i * 18 + 17] = height;
		}
	}

	void apply_scale(float* data, float* vertex, int len, float scale) {
		for (int i = 0; i < len; i++) {
			data[i] *= scale;
			vertex[i * 18 + 2] *= scale;
			vertex[i * 18 + 5] *= scale;
			vertex[i * 18 + 8] *= scale;
			vertex[i * 18 + 11] *= scale;
			vertex[i * 18 + 14] *= scale;
			vertex[i * 18 + 17] *= scale;
		}
	}

	void build_settings(bool save_all, bool swap_zup, bool swap_uv, bool centered, int density, float width, float height, float scale) {
		terrainops::save_all = save_all;
		terrainops::save_swap_zup = swap_zup;
		terrainops::save_swap_uv = swap_uv;
		terrainops::save_centered = centered;
		terrainops::save_density = density;
		terrainops::save_width = width;
		terrainops::save_height = height;
		terrainops::save_scale = scale;
	}

	long build(float* data, float* out, int len) {
		bool all = terrainops::save_all;
		bool swap_uv = terrainops::save_swap_uv;
		bool swap_zup = terrainops::save_swap_zup;
		int density = terrainops::save_density;
		float w = terrainops::save_width;
		float h = terrainops::save_height;
		float xoff = terrainops::save_centered ? (-w / 2) : 0;
		float yoff = terrainops::save_centered ? (-h / 2) : 0;
		float scale = terrainops::save_scale;
		
		float x00, x01, x10, x11, y00, y01, y10, y11, z00, z01, z10, z11;
		unsigned int c00, c01, c10, c11;
		float xt00, xt01, xt10, xt11, yt00, yt01, yt10, yt11;

		int float_count = 0;

		for (int i = 0; i < w - density; i += density) {
			for (int j = 0; j < h - density; j += density) {
				x00 = floor(i);
				y00 = floor(j);
				z00 = get_z(data, x00, y00, h);
				x01 = floor(i);
				y01 = fmin(ceil(j + density), h);
				z01 = get_z(data, x01, y01, h);
				x10 = fmin(ceil(i + density), w);
				y10 = floor(j);
				z10 = get_z(data, x10, y10, h);
				x11 = fmin(ceil(i + density), w);
				y11 = fmin(ceil(j + density), h);
				z11 = get_z(data, x11, y11, h);

				x00 = (x00 + xoff) * scale;
				x01 = (x01 + xoff) * scale;
				x10 = (x10 + xoff) * scale;
				x11 = (x11 + xoff) * scale;
				y00 = (y00 + yoff) * scale;
				y01 = (y01 + yoff) * scale;
				y10 = (y10 + yoff) * scale;
				y11 = (y11 + yoff) * scale;

				// @todo figure out texture UVs
				xt00 = 0;
				xt01 = 0;
				xt10 = 0;
				xt11 = 0;

				if (swap_uv) {
					yt00 = 1 - 0;
					yt01 = 1 - 0;
					yt10 = 1 - 0;
					yt11 = 1 - 0;
				} else {
					yt00 = 0;
					yt01 = 0;
					yt10 = 0;
					yt11 = 0;
				}

				c00 = 0xffffffff;
				c01 = 0xffffffff;
				c10 = 0xffffffff;
				c11 = 0xffffffff;

				if (all || z00 > 0 || z10 > 0 || z11 > 0) {
					write_vertex(out, &float_count, x00, y00, z00, xt00, yt00, c00, 1, 0, 0);
					write_vertex(out, &float_count, x10, y10, z10, xt10, yt10, c10, 0, 1, 0);
					write_vertex(out, &float_count, x11, y11, z11, xt11, yt11, c11, 0, 0, 1);
				}

				if (all || z11 > 0 || z01 > 0 || z00 > 0) {
					write_vertex(out, &float_count, x11, y11, z11, xt11, yt11, c11, 1, 0, 0);
					write_vertex(out, &float_count, x01, y01, z01, xt01, yt01, c01, 0, 1, 0);
					write_vertex(out, &float_count, x00, y00, z00, xt00, yt00, c00, 0, 0, 1);
				}
			}
		}

		return float_count * 4;
	}

	void generate(float* data, float* out, int w, int h) {
		int index = 0;
		// the barycentric coordinate gets squeezed into the fractional part of the X coordinate:
		//  - BC0: 0.5
		//  - BC1: 0.25
		//  - BC2: 0.125
		// the texture offset gets squeezed into the fractional part of the Y coordinate
		//  - First triangle (coordinates stored in the RG channels): 0.0
		//  - Second triangle (coordinates stored in the BA channels): 0.5
		// the triangle internal texture offset gets squeezed into the fractional part of the Y coordinate, also
		//  - (U + tile size) coordinate: 0.25
		//  - (V + tile size) coordinate: 0.125

#define BC0 0.5
#define BC1 0.25
#define BC2 0.125
#define T0 0.0
#define T1 0.5
#define U 0.25
#define V 0.125

		for (float i = 0; i < w - 1; i++) {
			for (float j = 0; j < h - 1; j++) {
				out[index++] = i + 0 + BC0;
				out[index++] = j + 0 + T0;
				out[index++] = get_z(data, i + 0, j + 0, h);

				out[index++] = i + 1 + BC1;
				out[index++] = j + 0 + T0 + U;
				out[index++] = get_z(data, i + 1, j + 0, h);

				out[index++] = i + 1 + BC2;
				out[index++] = j + 1 + T0 + U + V;
				out[index++] = get_z(data, i + 1, j + 1, h);

				out[index++] = i + 1 + BC0;
				out[index++] = j + 1 + T1 + U + V;
				out[index++] = get_z(data, i + 1, j + 1, h);

				out[index++] = i + 0 + BC1;
				out[index++] = j + 1 + T1 + V;
				out[index++] = get_z(data, i + 0, j + 1, h);

				out[index++] = i + 0 + BC2;
				out[index++] = j + 0 + T1;
				out[index++] = get_z(data, i + 0, j + 0, h);
			}
		}

#undef BC0
#undef BC1
#undef BC2
#undef T0
#undef T1
#undef U
#undef V
	}

	float get_z(float* data, int x, int y, int h) {
		return data[x * h + y];
	}

	inline void write_vertex(float* out, int* byte, float x, float y, float z, float u, float v, unsigned int c, float bc1, float bc2, float bc3) {
		// position
		out[(*byte)++] = x;
		out[(*byte)++] = y;
		out[(*byte)++] = z;
		// normals oughta be calculated later anyway
		out[(*byte)++] = 0;
		out[(*byte)++] = 0;
		out[(*byte)++] = 0;
		// texture and color
		out[(*byte)++] = u;
		out[(*byte)++] = v;
		((unsigned int*)out)[(*byte)++] = c;
		// tangent and bitangent, we calculate these later
		out[(*byte)++] = 0;
		out[(*byte)++] = 0;
		out[(*byte)++] = 0;
		out[(*byte)++] = 0;
		out[(*byte)++] = 0;
		out[(*byte)++] = 0;
		// barycentrics
		out[(*byte)++] = bc1;
		out[(*byte)++] = bc2;
		out[(*byte)++] = bc3;
	}
}