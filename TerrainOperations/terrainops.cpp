#include <algorithm>
#include "terrainops.h"
#include <main/dragomath.h>

namespace terrainops {
	bool save_all = true;
	bool save_swap_zup = false;
	bool save_swap_uv = false;
	bool save_centered = false;
	int save_density = 1;
	int save_width = 1;
	int save_height = 1;
	float save_scale = 1;

	float* mutate_noise = NULL;
	Vector3 mutate_noise_data;
	unsigned int* mutate_texture = NULL;
	Vector3 mutate_texture_data;

	const char* version() {
		return __DRAGO_TERRAIN_OP;
	}

	// general
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

	// deformation
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

	void deform_mold(float* data, int len, float direction, float radius) {

	}

	void deform_average(float* data, int len, float direction, float radius) {

	}

	void deform_average_flat(float* data, int len, float direction, float radius) {

	}

	void deform_zero(float* data, int len, float radius) {

	}

	// mutation
	void mutate_set_noise(float* noise, int w, int h, float strength) {
		terrainops::mutate_noise = noise;
		terrainops::mutate_noise_data.a = w;
		terrainops::mutate_noise_data.b = h;
		terrainops::mutate_noise_data.z = strength;
	}

	void mutate_set_texture(unsigned int* texture, int w, int h, float strength) {
		terrainops::mutate_texture = texture;
		terrainops::mutate_texture_data.a = w;
		terrainops::mutate_texture_data.b = h;
		terrainops::mutate_texture_data.z = strength;
	}

	void mutate(float* data, float* vertex, int w, int h) {
		unsigned int* texture = terrainops::mutate_texture;
		int texture_w = terrainops::mutate_texture_data.a;
		int texture_h = terrainops::mutate_texture_data.b;
		float texture_strength = terrainops::mutate_texture_data.z;
		float* noise = terrainops::mutate_noise;
		int noise_w = terrainops::mutate_noise_data.a;
		int noise_h = terrainops::mutate_noise_data.b;
		float noise_strength = terrainops::mutate_noise_data.z;

		float samp_noise = 0;
		unsigned int samp_texture = 0;
		float samp_texture_r = 0;
		float samp_texture_g = 0;
		float samp_texture_b = 0;
		float samp_texture_a = 0;

		for (int i = 0; i < w; i++) {
			for (int j = 0; j < h; j++) {
				if (noise != NULL) {
					samp_noise = spriteops::sample_float(noise, noise_w, noise_h, i / (float)w, j / (float)h) - noise_strength / 2;
				}
				
				if (texture != NULL) {
					samp_texture = spriteops::sample(texture, texture_w, texture_h, i / (float)w, j / (float)h);
					samp_texture_r = ((((samp_texture >> 0x00) & 0xff) / 127.0f) - 1) * texture_strength;
					samp_texture_g = ((((samp_texture >> 0x08) & 0xff) / 127.0f) - 1) * texture_strength;
					samp_texture_b = ((((samp_texture >> 0x10) & 0xff) / 127.0f) - 1) * texture_strength;
					samp_texture_a = ((((samp_texture >> 0x18) & 0xff) / 127.0f) - 1) * texture_strength;
				}
				
				add_z(data, vertex, i, j, h, w, samp_noise + samp_texture_r);
			}
		}
	}

	// build vertex data
	void build_settings(bool save_all, bool swap_zup, bool swap_uv, bool centered, int density, int width, int height, float scale) {
		terrainops::save_all = save_all;
		terrainops::save_swap_zup = swap_zup;
		terrainops::save_swap_uv = swap_uv;
		terrainops::save_centered = centered;
		terrainops::save_density = density;
		terrainops::save_width = width;
		terrainops::save_height = height;
		terrainops::save_scale = scale;
	}

	long build(float* data, long long* meta, int len, int meta_len) {
		bool all = terrainops::save_all;
		bool swap_uv = terrainops::save_swap_uv;
		bool swap_zup = terrainops::save_swap_zup;
		int density = terrainops::save_density;
		int w = terrainops::save_width;
		int h = terrainops::save_height;
		float xoff = terrainops::save_centered ? (-(float)w / 2) : 0;
		float yoff = terrainops::save_centered ? (-(float)h / 2) : 0;
		float scale = terrainops::save_scale;
		
		float x00, x01, x10, x11, y00, y01, y10, y11, z00, z01, z10, z11;
		unsigned int c00, c01, c10, c11;
		float xt00, xt01, xt10, xt11, yt00, yt01, yt10, yt11;
		Vector3 e1, e2;
		Vector3 normal, tangent, bitangent;

		// we'll deal with these later
		tangent.x = 0;
		tangent.y = 0;
		tangent.z = 0;
		bitangent.x = 0;
		bitangent.y = 0;
		bitangent.z = 0;

		// vertex count, output address, x1, y1, x2, y2
		for (int i = 0; i < meta_len; i += 6) {
			long long* index = &meta[i + 0];
			float* out = (float*)meta[i + 1];

			for (int x = (int)(meta[i + 2]); x <= (int)(meta[i + 4]) - density; x += density) {
				for (int y = (int)(meta[i + 3]); y <= (int)(meta[i + 5]) - density; y += density) {
					x00 = (float)x;
					y00 = (float)y;
					z00 = get_z(data, x, y, h);

					x01 = (float)x;
					y01 = (float)std::min(y + density, h - 1);
					z01 = get_z(data, x, std::min(y + density, h - 1), h);

					x10 = (float)std::min(x + density, w - 1);
					y10 = (float)y;
					z10 = get_z(data, std::min(x + density, w - 1), y, h);

					x11 = (float)std::min(x + density, w - 1);
					y11 = (float)std::min(y + density, h - 1);
					z11 = get_z(data, std::min(x + density, w - 1), std::min(y + density, h - 1), h);

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
						e1.x = x10 - x00;
						e1.y = y10 - y00;
						e1.z = z10 - z00;
						e2.x = x11 - x00;
						e2.y = y11 - y00;
						e2.z = z11 - z00;

						normal.x = e1.y * e2.z - e1.z * e2.y;
						normal.y = -e1.x * e2.z + e1.z * e2.x;
						normal.z = e1.x * e2.y - e1.y * e2.x;

						NORMALIZE(normal);

						write_vertex(out, index, x00, y00, z00, normal.x, normal.y, normal.z, xt00, yt00, c00, tangent.x, tangent.y, tangent.z, bitangent.x, bitangent.y, bitangent.z, 1, 0, 0);
						write_vertex(out, index, x10, y10, z10, normal.x, normal.y, normal.z, xt10, yt10, c10, tangent.x, tangent.y, tangent.z, bitangent.x, bitangent.y, bitangent.z, 0, 1, 0);
						write_vertex(out, index, x11, y11, z11, normal.x, normal.y, normal.z, xt11, yt11, c11, tangent.x, tangent.y, tangent.z, bitangent.x, bitangent.y, bitangent.z, 0, 0, 1);
					}

					if (all || z11 > 0 || z01 > 0 || z00 > 0) {
						e1.x = x01 - x11;
						e1.y = y01 - y11;
						e1.z = z01 - z11;
						e2.x = x00 - x11;
						e2.y = y00 - y11;
						e2.z = z00 - z11;

						normal.x = e1.y * e2.z - e1.z * e2.y;
						normal.y = -e1.x * e2.z + e1.z * e2.x;
						normal.z = e1.x * e2.y - e1.y * e2.x;

						NORMALIZE(normal);

						write_vertex(out, index, x11, y11, z11, normal.x, normal.y, normal.z, xt11, yt11, c11, tangent.x, tangent.y, tangent.z, bitangent.x, bitangent.y, bitangent.z, 1, 0, 0);
						write_vertex(out, index, x01, y01, z01, normal.x, normal.y, normal.z, xt01, yt01, c01, tangent.x, tangent.y, tangent.z, bitangent.x, bitangent.y, bitangent.z, 0, 1, 0);
						write_vertex(out, index, x00, y00, z00, normal.x, normal.y, normal.z, xt00, yt00, c00, tangent.x, tangent.y, tangent.z, bitangent.x, bitangent.y, bitangent.z, 0, 0, 1);
					}
				}
			}

			*index = FLOATS2BYTES(*index);
		}

		return 0;
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

#define BC0 0.5f
#define BC1 0.25f
#define BC2 0.125f
#define T0 0.0f
#define T1 0.5f
#define U 0.25f
#define V 0.125f

		for (int i = 0; i < w - 1; i++) {
			for (int j = 0; j < h - 1; j++) {
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

	// helper functions
	inline float get_z(float* data, int x, int y, int h) {
		return data[DATA_INDEX(x, y, h)];
	}

	inline void add_z(float* data, float* vertex, int x, int y, int h, int w, float value) {
		set_z(data, vertex, x, y, h, w, value + get_z(data, x, y, h));
	}

	inline void set_z(float* data, float* vertex, int x, int y, int h, int w, float value) {
		data[DATA_INDEX(x, y, h)] = value;
		
		if (x > 0 && y > 0) {
			vertex[VERTEX_INDEX(x - 1, y - 1, h, 2) + 2] = value;
			vertex[VERTEX_INDEX(x - 1, y - 1, h, 3) + 2] = value;
		}

		if (x < w && y > 0) {
			vertex[VERTEX_INDEX(x, y - 1, h, 4) + 2] = value;
		}

		if (x > 0 && y < h - 1) {
			vertex[VERTEX_INDEX(x - 1, y, h, 1) + 2] = value;
		}

		if (x < w && y < h - 1) {
			vertex[VERTEX_INDEX(x, y, h, 0) + 2] = value;
			vertex[VERTEX_INDEX(x, y, h, 5) + 2] = value;
		}
	}

	inline void write_vertex(
				float* out, long long* address,
				float x, float y, float z,
				float nx, float ny, float nz,
				float u, float v,
				unsigned int c,
				float tx, float ty, float tz,
				float bx, float by, float bz,
				float bc1, float bc2, float bc3
			) {
		// position
		out[(*address)++] = x;
		out[(*address)++] = y;
		out[(*address)++] = z;
		// normals
		out[(*address)++] = nx;
		out[(*address)++] = ny;
		out[(*address)++] = nz;
		// texture and color
		out[(*address)++] = u;
		out[(*address)++] = v;
		((unsigned int*)out)[(*address)++] = c;
		// tangent and bitangent
		out[(*address)++] = tx;
		out[(*address)++] = ty;
		out[(*address)++] = tz;
		out[(*address)++] = bx;
		out[(*address)++] = by;
		out[(*address)++] = bz;
		// barycentrics
		out[(*address)++] = bc1;
		out[(*address)++] = bc2;
		out[(*address)++] = bc3;
	}
}