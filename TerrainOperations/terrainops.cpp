#include "terrainops.h"
#include <main/dragomath.h>
#include <MeshOperations/building.h>

#include <iostream>

namespace terrainops {
	bool save_all = true;
	bool save_swap_zup = false;
	bool save_swap_uv = false;
	bool save_centered = false;
	int save_density = 1;
	float save_scale = 1;
	float save_tex_size = 0.0625;
	float save_color_scale = 8.0;
	Vector2 save_start;
	Vector2 save_end;
	unsigned int save_format = VFX_POSITION_3D | VFX_NORMAL | VFX_TEXCOORD | VFX_COLOUR;
	unsigned int* save_texture_map = 0;
	unsigned int* save_colour_map = 0;

	float* cursor_output = NULL;

	unsigned int* deform_brush_texture = NULL;
	Vector3 deform_brush_size;
	Vector3 deform_brush_position;
	float deform_velocity = 0;
	float deform_radius = 8;

	float* mutate_noise = NULL;
	Vector3 mutate_noise_data;
	unsigned int* mutate_texture = NULL;
	Vector3 mutate_texture_data;

	float* data = NULL;
	Vector3 data_size;
	float* vertex = NULL;
	float* vertex_lod = NULL;

	const int cell_size = 256;
	const int lod_reduction = 8;

	const char* version() {
		return __DRAGO_TERRAIN_OP;
	}

	// general
	void set_active_data(float* data, int w, int h) {
		terrainops::data = data;
		terrainops::data_size.a = w;
		terrainops::data_size.b = h;
		terrainops::data_size.c = w * h;
	}

	void set_active_vertex_data(float* vertex) {
		terrainops::vertex = vertex;
	}

	void set_lod_vertex_data(float* lod) {
		terrainops::vertex_lod = lod;
	}

	void to_heightmap(unsigned int* out, float scale) {
		float* data = terrainops::data;
		unsigned int len = terrainops::data_size.c;
		float max = terrainops::max_height(data, len);
		for (unsigned int i = 0; i < len; i++) {
			int z = std::clamp((int)(255.0f * data[i] / max), 0, 255);
			out[i] = 0xff000000 | (z | (z << 8) | (z << 16));
		}
	}

	void from_heightmap(unsigned int* in, float scale) {
		float* data = terrainops::data;
		int len = terrainops::data_size.c;
		for (int i = 0; i < len; i++) {
			// maybe you want to use the other channels to store some other information idk
			data[i] = (in[i] & 0x000000ff) / 255.0f * scale;
		}
	}

	float max_height(float* data, unsigned int len) {
		float max = -1e10f;
		for (unsigned int i = 0; i < len; i++) {
			max = std::max(max, data[i]);
		}
		return max;
	}

	float min_height(float* data, unsigned int len) {
		float min = 1e10f;
		for (unsigned int i = 0; i < len; i++) {
			min = std::min(min, data[i]);
		}
		return min;
	}

	void set_cursor_location_output(float* out) {
		terrainops::cursor_output = out;
	}

	void get_intersecting_triangle(float ox, float oy, float oz, float dx, float dy, float dz) {

	}

	// deformation
	void flatten(float height) {
		float* data = terrainops::data;
		int len = terrainops::data_size.c;
		float* vertex = terrainops::vertex;
		for (int i = 0; i < len; i++) {
			data[i] = height;
			vertex[i * 18 + 2] = height;
			vertex[i * 18 + 5] = height;
			vertex[i * 18 + 8] = height;
			vertex[i * 18 + 11] = height;
			vertex[i * 18 + 14] = height;
			vertex[i * 18 + 17] = height;
		}

		int len_lod = len / (terrainops::lod_reduction * terrainops::lod_reduction);
		float* lod = terrainops::vertex_lod;
		for (int i = 0; i < len_lod; i++) {
			lod[i * 18 + 2] = height;
			lod[i * 18 + 5] = height;
			lod[i * 18 + 8] = height;
			lod[i * 18 + 11] = height;
			lod[i * 18 + 14] = height;
			lod[i * 18 + 17] = height;
		}
	}

	void apply_scale(float scale) {
		float* data = terrainops::data;
		int len = terrainops::data_size.c;
		float* vertex = terrainops::vertex;
		for (int i = 0; i < len; i++) {
			data[i] *= scale;
			vertex[i * 18 + 2] *= scale;
			vertex[i * 18 + 5] *= scale;
			vertex[i * 18 + 8] *= scale;
			vertex[i * 18 + 11] *= scale;
			vertex[i * 18 + 14] *= scale;
			vertex[i * 18 + 17] *= scale;
		}

		int len_lod = len / (terrainops::lod_reduction * terrainops::lod_reduction);
		float* lod = terrainops::vertex_lod;
		for (int i = 0; i < len_lod; i++) {
			lod[i * 18 + 2] *= scale;
			lod[i * 18 + 5] *= scale;
			lod[i * 18 + 8] *= scale;
			lod[i * 18 + 11] *= scale;
			lod[i * 18 + 14] *= scale;
			lod[i * 18 + 17] *= scale;
		}
	}

	void deform_brush(unsigned int* brush, float w, float h) {
		terrainops::deform_brush_texture = brush;
		terrainops::deform_brush_size.x = w;
		terrainops::deform_brush_size.y = h;
	}

	void deform_brush_settings(float radius, float velocity) {
		terrainops::deform_radius = radius;
		terrainops::deform_velocity = velocity;
	}

	void deform_brush_set_position(float x, float y) {
		terrainops::deform_brush_position.x = x;
		terrainops::deform_brush_position.y = y;
	}

	// these are a little different, in that they aren't called directly from the
	// dll entrypoint, but rather are passed as a callback to the
	// invoke_deformation function
	void deform_mold(float* data, float* vertex, float* lod, int w, int h, int x, int y, float sampled, float velocity, float average, int reduction, int cell_size) {
		add_z(data, vertex, lod, x, y, w, h, sampled * velocity, reduction, cell_size);
	}

	void deform_average(float* data, float* vertex, float* lod, int w, int h, int x, int y, float sampled, float velocity, float average, int reduction, int cell_size) {
		set_z(data, vertex, lod, x, y, w, h, std::lerp(get_z(data, x, y, h), average, (float)(std::fmax(-0.5, sampled * velocity) / 8.0)), reduction, cell_size);
	}

	void deform_zero(float* data, float* vertex, float* lod, int w, int h, int x, int y, float sampled, float velocity, float average, int reduction, int cell_size) {
		set_z(data, vertex, lod, x, y, w, h, std::lerp(get_z(data, x, y, h), 0, (float)(std::fmax(-0.5, sampled * velocity) / 8.0)), reduction, cell_size);
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

	void mutate() {
		float* data = terrainops::data;
		int w = terrainops::data_size.a;
		int h = terrainops::data_size.b;
		float* vertex = terrainops::vertex;
		float* lod = terrainops::vertex_lod;
		int reduction = terrainops::lod_reduction;
		int cell_size = terrainops::cell_size;

		unsigned int* texture = terrainops::mutate_texture;
		int texture_w = terrainops::mutate_texture_data.a;
		int texture_h = terrainops::mutate_texture_data.b;
		float texture_strength = terrainops::mutate_texture_data.z;
		float* noise = terrainops::mutate_noise;
		int noise_w = terrainops::mutate_noise_data.a;
		int noise_h = terrainops::mutate_noise_data.b;
		float noise_strength = terrainops::mutate_noise_data.z;

		float samp_noise = 0;
		Vector4 samp_texture{};

		for (int i = 0; i < w; i++) {
			for (int j = 0; j < h; j++) {
				if (noise != NULL) {
					samp_noise = spriteops::sample_float(noise, noise_w, noise_h, i / (float)w, j / (float)h) - noise_strength / 2;
				}
				
				if (texture != NULL) {
					samp_texture = spriteops::sample_vec4(texture, texture_w, texture_h, i / (float)w, j / (float)h);
				}
				
				add_z(data, vertex, lod, i, j, w, h, samp_noise + (samp_texture.r - 0.5f) * 2 * texture_strength, reduction, cell_size);
			}
		}
	}

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

	void generate_internal(float* out) {
		int w = terrainops::data_size.a;
		int h = terrainops::data_size.b;
		float* data = terrainops::data;

		int cs = terrainops::cell_size;

		for (int i = 0; i < w - 1; i++) {
			for (int j = 0; j < h - 1; j++) {
				unsigned int base_index = get_vertex_index(cs, i, j, w, h, 0);
				out[base_index + 0] = i + 0 + BC0;
				out[base_index + 1] = j + 0 + T0;
				out[base_index + 2] = get_z(data, i + 0, j + 0, h);
				
				out[base_index + 3] = i + 1 + BC1;
				out[base_index + 4] = j + 0 + T0 + U;
				out[base_index + 5] = get_z(data, i + 1, j + 0, h);
				
				out[base_index + 6] = i + 1 + BC2;
				out[base_index + 7] = j + 1 + T0 + U + V;
				out[base_index + 8] = get_z(data, i + 1, j + 1, h);
				
				out[base_index + 9] = i + 1 + BC0;
				out[base_index + 10] = j + 1 + T1 + U + V;
				out[base_index + 11] = get_z(data, i + 1, j + 1, h);
				
				out[base_index + 12] = i + 0 + BC1;
				out[base_index + 13] = j + 1 + T1 + V;
				out[base_index + 14] = get_z(data, i + 0, j + 1, h);
				
				out[base_index + 15] = i + 0 + BC2;
				out[base_index + 16] = j + 0 + T1;
				out[base_index + 17] = get_z(data, i + 0, j + 0, h);
			}
		}
	}

	void generate_lod_internal(float* out) {
		int reduction = terrainops::lod_reduction;
		int w = terrainops::data_size.a;
		int h = terrainops::data_size.b;
		int lodw = terrainops::data_size.a / reduction;
		int lodh = terrainops::data_size.b / reduction;
		float* data = terrainops::data;

		int cs = terrainops::cell_size / reduction;

		for (int i = 0; i < lodw - 1; i++) {
			for (int j = 0; j < lodh - 1; j++) {
				unsigned int base_index = get_vertex_index(cs, i, j, lodw, lodh, 0);
				out[base_index + 0] = i * reduction + 0 + BC0;
				out[base_index + 1] = j * reduction + 0 + T0;
				out[base_index + 2] = get_z(data, (i * reduction) + 0, (j * reduction) + 0, h);

				out[base_index + 3] = i * reduction + reduction + BC1;
				out[base_index + 4] = j * reduction + 0 + T0 + U;
				out[base_index + 5] = get_z(data, (i + 1) * reduction, (j * reduction) + 0, h);

				out[base_index + 6] = i * reduction + reduction + BC2;
				out[base_index + 7] = j * reduction + reduction + T0 + U + V;
				out[base_index + 8] = get_z(data, (i + 1) * reduction, (j + 1) * reduction, h);

				out[base_index + 9] = i * reduction + reduction + BC0;
				out[base_index + 10] = j * reduction + reduction + T1 + U + V;
				out[base_index + 11] = get_z(data, (i + 1) * reduction, (j + 1) * reduction, h);

				out[base_index + 12] = i * reduction + 0 + BC1;
				out[base_index + 13] = j * reduction + reduction + T1 + V;
				out[base_index + 14] = get_z(data, (i * reduction) + 0, (j + 1) * reduction, h);

				out[base_index + 15] = i * reduction + 0 + BC2;
				out[base_index + 16] = j * reduction + 0 + T1;
				out[base_index + 17] = get_z(data, (i * reduction) + 0, (j * reduction) + 0, h);
			}
		}
	}

#undef BC0
#undef BC1
#undef BC2
#undef T0
#undef T1
#undef U
#undef V

	// helper functions
	void invoke_deformation(bool calculate_average, void(*callback)(float*, float*, float*, int, int, int, int, float, float, float, int, int)) {
		float* data = terrainops::data;
		int w = terrainops::data_size.a;
		int h = terrainops::data_size.b;
		float* vertex = terrainops::vertex;
		float* lod = terrainops::vertex_lod;
		int reduction = terrainops::lod_reduction;
		int cell_size = terrainops::cell_size;

		unsigned int* brush = terrainops::deform_brush_texture;
		int bw = (int)terrainops::deform_brush_size.x;
		int bh = (int)terrainops::deform_brush_size.y;
		int rw = (int)terrainops::deform_radius;
		int rh = (int)terrainops::deform_radius;
		int x = (int)terrainops::deform_brush_position.x;
		int y = (int)terrainops::deform_brush_position.y;
		float velocity = terrainops::deform_velocity;

		// unconstrained range of the brush
		int bx1a = x - rw;
		int by1a = y - rh;
		int bx2a = x + rw;
		int by2a = y + rh;

		// inbounds range of the brush
		int x1 = std::max(0, bx1a);
		int y1 = std::max(0, by1a);
		int x2 = std::min(w - 1, bx2a);
		int y2 = std::min(h - 1, by2a);

		Vector4 pixel;
		float average = 0;

		// if the entire region is zero area, dont bother
		if (x1 == x2 || y1 == y2) return;

		if (calculate_average) {
			for (int i = x1; i <= x2; i++) {
				for (int j = y1; j <= y2; j++) {
					average += get_z(data, i, j, h);
				}
			}

			average /= (x2 - x1) * (y2 - y1);
		}

		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				// downsampling a filtered image seems to behave strangely but the brush
				// won't likely ever be smaller than the cursor anyway
				pixel = spriteops::sample_vec4(brush, bw, bh, ((float)(i - bx1a)) / (bx2a - bx1a), ((float)(j - by1a)) / (by2a - by1a));
				callback(data, vertex, lod, w, h, i, j, pixel.r, velocity, average, reduction, cell_size);
			}
		}
	}
}