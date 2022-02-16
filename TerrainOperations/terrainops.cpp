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

	void to_heightmap(unsigned int* out, float scale) {
		float* data = terrainops::data;
		int len = terrainops::data_size.c;
		int z;
		for (int i = 0; i < len; i++) {
			z = std::clamp((int)(data[i] * scale), 0, 255);
			out[i] = 0xff000000 | (z | (z << 8) | (z << 16));
		}
	}

	void from_heightmap(unsigned int* in, float scale) {
		float* data = terrainops::data;
		int len = terrainops::data_size.c;
		int z;
		for (int i = 0; i < len; i++) {
			// maybe you want to use the other channels to store some other information idk
			z = in[i] & 0x000000ff;
			data[i] = z / scale;
		}
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
	void deform_mold(float* data, float* vertex, int w, int h, int x, int y, float sampled, float velocity, float average) {
		add_z(data, vertex, x, y, w, h, sampled * velocity);
	}

	void deform_average(float* data, float* vertex, int w, int h, int x, int y, float sampled, float velocity, float average) {
		set_z(data, vertex, x, y, w, h, std::lerp(get_z(data, x, y, h), average, (float)(std::fmax(-0.5, sampled * velocity) / 8.0)));
	}

	void deform_zero(float* data, float* vertex, int w, int h, int x, int y, float sampled, float velocity, float average) {
		set_z(data, vertex, x, y, w, h, std::lerp(get_z(data, x, y, h), 0, (float)(std::fmax(-0.5, sampled * velocity) / 8.0)));
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
					samp_texture_r = ((((samp_texture >> 0x00) & 0xff) / 127.0f) - 1.0f) * texture_strength;
					samp_texture_g = ((((samp_texture >> 0x08) & 0xff) / 127.0f) - 1.0f) * texture_strength;
					samp_texture_b = ((((samp_texture >> 0x10) & 0xff) / 127.0f) - 1.0f) * texture_strength;
					samp_texture_a = ((((samp_texture >> 0x18) & 0xff) / 127.0f) - 1.0f) * texture_strength;
				}
				
				add_z(data, vertex, i, j, w, h, samp_noise + samp_texture_r);
			}
		}
	}

	// build vertex data
	void build_settings(bool save_all, bool swap_zup, bool swap_uv, bool centered, int density, float scale, float tex_size, float color_scale, unsigned int format) {
		terrainops::save_all = save_all;
		terrainops::save_swap_zup = swap_zup;
		terrainops::save_swap_uv = swap_uv;
		terrainops::save_centered = centered;
		terrainops::save_density = density;
		terrainops::save_scale = scale;
		terrainops::save_tex_size = tex_size;
		terrainops::save_color_scale = color_scale;
		terrainops::save_format = format;
	}

	void build_bounds(int x1, int y1, int x2, int y2) {
		terrainops::save_start.a = x1;
		terrainops::save_start.b = y1;
		terrainops::save_end.a = x2;
		terrainops::save_end.b = y2;
	}

	void build_texture(unsigned int* save_texture_map) {
		terrainops::save_texture_map = save_texture_map;
	}

	void build_vertex_colour(unsigned int* save_colour_map) {
		terrainops::save_colour_map = save_colour_map;
	}

	void build(float* out, std::stringstream* content, long long* index, int* vertices, void(*callback)(float*, std::stringstream*, unsigned int, long long*, float, float, float, float, float, float, float, float, unsigned int, float, float, float, float, float, float, float, float, float)) {
		float* data = terrainops::data;
		int len = terrainops::data_size.c;

		bool all = terrainops::save_all;
		bool swap_uv = terrainops::save_swap_uv;
		bool swap_zup = terrainops::save_swap_zup;
		int density = terrainops::save_density;
		int w = terrainops::data_size.a;
		int h = terrainops::data_size.b;
		float xoff = terrainops::save_centered ? (-(float)w / 2) : 0;
		float yoff = terrainops::save_centered ? (-(float)h / 2) : 0;
		float scale = terrainops::save_scale;
		float color_scale = terrainops::save_color_scale;
		unsigned int format = terrainops::save_format;
		unsigned int* texture_data = terrainops::save_texture_map;
		unsigned int* colour_data = terrainops::save_colour_map;
		float tex_size = terrainops::save_tex_size;

		int x1 = terrainops::save_start.a;
		int y1 = terrainops::save_start.b;
		int x2 = terrainops::save_end.a;
		int y2 = terrainops::save_end.b;
		
		float x00, x01, x10, x11, y00, y01, y10, y11, z00, z01, z10, z11;
		unsigned int c00, c01, c10, c11;
		Vector3 e1{ }, e2{ };
		Vector3 normal{ }, tangent{ }, bitangent{ };
		Vector2 texcoord{ };

		// we'll deal with these later
		tangent.x = 0;
		tangent.y = 0;
		tangent.z = 0;
		bitangent.x = 0;
		bitangent.y = 0;
		bitangent.z = 0;

		for (int x =x1; x <= x2 - density; x += density) {
			for (int y = y1; y <= y2 - density; y += density) {
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
				z00 *= scale;
				z10 *= scale;
				z01 *= scale;
				z11 *= scale;

				if (swap_zup) {
					float t = y00;
					y00 = z00;
					z00 = t;
					t = y01;
					y01 = z01;
					z01 = t;
					t = y11;
					y11 = z11;
					z11 = t;
					t = y10;
					y10 = z10;
					z10 = t;
				}

				get_texcoord(texture_data, &texcoord, x, y, h, swap_uv);

				c00 = get_colour(colour_data, x, y, w, h, color_scale);
				c01 = get_colour(colour_data, x, y + density, w, h, color_scale);
				c10 = get_colour(colour_data, x + density, y, w, h, color_scale);
				c11 = get_colour(colour_data, x + density, y + density, w, h, color_scale);

				if (all || z00 >= 0 || z10 >= 0 || z11 >= 0) {
					e1.x = x10 - x00;
					e1.y = y10 - y00;
					e1.z = z10 - z00;
					e2.x = x11 - x00;
					e2.y = y11 - y00;
					e2.z = z11 - z00;

					CROSS(normal, e1, e2);
					NORMALIZE(normal);

					if (swap_zup) {
						float t = normal.z;
						normal.z = normal.y;
						normal.y = t;
					}

					// if you do smoothed normals, it should go here

					callback(out, content, format, index, x00, y00, z00, normal.x, normal.y, normal.z, texcoord.x, texcoord.y, c00, tangent.x, tangent.y, tangent.z, bitangent.x, bitangent.y, bitangent.z, 1, 0, 0);
					callback(out, content, format, index, x10, y10, z10, normal.x, normal.y, normal.z, texcoord.x + tex_size, texcoord.y, c10, tangent.x, tangent.y, tangent.z, bitangent.x, bitangent.y, bitangent.z, 0, 1, 0);
					callback(out, content, format, index, x11, y11, z11, normal.x, normal.y, normal.z, texcoord.x + tex_size, texcoord.y + tex_size, c11, tangent.x, tangent.y, tangent.z, bitangent.x, bitangent.y, bitangent.z, 0, 0, 1);
					(*vertices) += 3;
				}

				if (all || z11 >= 0 || z01 >= 0 || z00 >= 0) {
					e1.x = x01 - x11;
					e1.y = y01 - y11;
					e1.z = z01 - z11;
					e2.x = x00 - x11;
					e2.y = y00 - y11;
					e2.z = z00 - z11;

					CROSS(normal, e1, e2);
					NORMALIZE(normal);

					if (swap_zup) {
						float t = normal.z;
						normal.z = normal.y;
						normal.y = t;
					}

					callback(out, content, format, index, x11, y11, z11, normal.x, normal.y, normal.z, texcoord.x + tex_size, texcoord.y + tex_size, c11, tangent.x, tangent.y, tangent.z, bitangent.x, bitangent.y, bitangent.z, 1, 0, 0);
					callback(out, content, format, index, x01, y01, z01, normal.x, normal.y, normal.z, texcoord.x, texcoord.y + tex_size, c01, tangent.x, tangent.y, tangent.z, bitangent.x, bitangent.y, bitangent.z, 0, 1, 0);
					callback(out, content, format, index, x00, y00, z00, normal.x, normal.y, normal.z, texcoord.x, texcoord.y, c00, tangent.x, tangent.y, tangent.z, bitangent.x, bitangent.y, bitangent.z, 0, 0, 1);
					(*vertices) += 3;
				}
			}
		}
	}

	void build_obj(float* out, std::stringstream* content, long long* index, int* vertices) {
		float* data = terrainops::data;
		int len = terrainops::data_size.c;

		bool all = terrainops::save_all;
		bool swap_uv = terrainops::save_swap_uv;
		bool swap_zup = terrainops::save_swap_zup;
		int density = terrainops::save_density;
		int w = terrainops::data_size.a;
		int h = terrainops::data_size.b;
		float xoff = terrainops::save_centered ? (-(float)w / 2) : 0;
		float yoff = terrainops::save_centered ? (-(float)h / 2) : 0;
		float scale = terrainops::save_scale;
		unsigned int format = terrainops::save_format;
		unsigned int* texture_data = terrainops::save_texture_map;
		unsigned int* colour_data = terrainops::save_colour_map;
		float tex_size = terrainops::save_tex_size;

		int x1 = terrainops::save_start.a;
		int y1 = terrainops::save_start.b;
		int x2 = terrainops::save_end.a;
		int y2 = terrainops::save_end.b;

		std::map<std::string, int> position_map, normal_map, texture_map;
		std::string position_hash, texture_hash, normal_hash;

		Vector2 texcoord{ };
		Vector3 e1{ }, e2{ };
		Vector3 t1norm{ }, t2norm{ };

#define FORMATTED_POSITION "%.4f %.4f %.4f"
#define FORMATTED_TEXCOORD "%.8f %.8f"
#define FORMATTED_NORMAL "%.4f %.4f %.4f"

		for (int x = x1; x <= x2 - density; x += density) {
			for (int y = y1; y <= y2 - density; y += density) {
				char line[100]{ };

				if (swap_zup) {
					sprintf_s(line, FORMATTED_POSITION, (x + xoff) * scale, get_z(data, x, y, h) * scale, (y + yoff) * scale);
				} else {
					sprintf_s(line, FORMATTED_POSITION, (x + xoff) * scale, (y + yoff) * scale, get_z(data, x, y, h) * scale);
				}

				position_hash = std::string(line);
				position_map.insert(std::pair(position_hash, (int)position_map.size()));

				if (x >= x2 - density || y >= y2 - density) continue;

				get_texcoord(texture_data, &texcoord, x, y, h, swap_uv);

				// tex00
				memset(line, 0, sizeof(line));
				sprintf_s(line, FORMATTED_TEXCOORD, texcoord.x, texcoord.y);
				texture_hash = std::string(line);
				texture_map.insert(std::pair(texture_hash, (int)texture_map.size()));
				// tex10
				memset(line, 0, sizeof(line));
				sprintf_s(line, FORMATTED_TEXCOORD, texcoord.x + tex_size, texcoord.y);
				texture_hash = std::string(line);
				texture_map.insert(std::pair(texture_hash, (int)texture_map.size()));
				// tex11
				memset(line, 0, sizeof(line));
				sprintf_s(line, FORMATTED_TEXCOORD, texcoord.x + tex_size, texcoord.y + tex_size);
				texture_hash = std::string(line);
				texture_map.insert(std::pair(texture_hash, (int)texture_map.size()));
				// tex01
				memset(line, 0, sizeof(line));
				sprintf_s(line, FORMATTED_TEXCOORD, texcoord.x, texcoord.y + tex_size);
				texture_hash = std::string(line);
				texture_map.insert(std::pair(texture_hash, (int)texture_map.size()));

				get_normal(data, &t1norm, x, y, x + density, y, x + density, y + density, h);
				get_normal(data, &t2norm, x + density, y + density, x, y + density, x, y, h);

				// getting smooth normals in here is going to be a bit more work but hopefully not too much
				memset(line, 0, sizeof(line));
				sprintf_s(line, FORMATTED_NORMAL, t1norm.x, t1norm.y, t1norm.z);
				normal_hash = std::string(line);
				normal_map.insert(std::pair(normal_hash, (int)normal_map.size()));

				memset(line, 0, sizeof(line));
				sprintf_s(line, FORMATTED_NORMAL, t2norm.x, t2norm.y, t2norm.z);
				normal_hash = std::string(line);
				normal_map.insert(std::pair(normal_hash, (int)normal_map.size()));
			}
		}

		// technically it'd be more efficient to figure this out with math because we
		// know the structure of the grid, but also i can't be bothered to do that
		// and i don't think it'll affect performance that badly
		int position_count = (int)position_map.size();
		std::string* position_hashes = new std::string[position_count];
		for (auto const& [key, val] : position_map) {
			position_hashes[val] = key;
		}

		for (int i = 0; i < position_count; i++) {
			*content << "v " << position_hashes[i] << "\r\n";
		}

		delete[] position_hashes;

		*content << "\r\n";

		int tex_count = (int)texture_map.size();
		std::string* tex_hashes = new std::string[tex_count];
		for (auto const& [key, val] : texture_map) {
			tex_hashes[val] = key;
		}

		for (int i = 0; i < tex_count; i++) {
			*content << "vt " << tex_hashes[i] << "\r\n";
		}
		
		delete[] tex_hashes;

		*content << "\r\n";

		int normal_count = (int)normal_map.size();
		std::string* normal_hashes = new std::string[normal_count];
		for (auto const& [key, val] : normal_map) {
			normal_hashes[val] = key;
		}

		for (int i = 0; i < normal_count; i++) {
			*content << "vn " << normal_hashes[i] << "\r\n";
		}

		delete[] normal_hashes;
		
		for (int x = x1; x < std::min(x2 - density, w - 1); x += density) {
			for (int y = y1; y < std::max(y2 - density, h - 1); y += density) {
				float x00 = (float)x;
				float y00 = (float)y;
				float z00 = get_z(data, x, y, h);

				float x01 = (float)x;
				float y01 = (float)std::min(y + density, h - 1);
				float z01 = get_z(data, x, std::min(y + density, h - 1), h);

				float x10 = (float)std::min(x + density, w - 1);
				float y10 = (float)y;
				float z10 = get_z(data, std::min(x + density, w - 1), y, h);

				float x11 = (float)std::min(x + density, w - 1);
				float y11 = (float)std::min(y + density, h - 1);
				float z11 = get_z(data, std::min(x + density, w - 1), std::min(y + density, h - 1), h);
				
				x00 = (x00 + xoff) * scale;
				x01 = (x01 + xoff) * scale;
				x10 = (x10 + xoff) * scale;
				x11 = (x11 + xoff) * scale;
				y00 = (y00 + yoff) * scale;
				y01 = (y01 + yoff) * scale;
				y10 = (y10 + yoff) * scale;
				y11 = (y11 + yoff) * scale;
				z00 *= scale;
				z10 *= scale;
				z01 *= scale;
				z11 *= scale;

				if (swap_zup) {
					float t = y00;
					y00 = z00;
					z00 = t;
					t = y01;
					y01 = z01;
					z01 = t;
					t = y11;
					y11 = z11;
					z11 = t;
					t = y10;
					y10 = z10;
					z10 = t;
				}

				e1.x = x10 - x00;
				e1.y = y10 - y00;
				e1.z = z10 - z00;
				e2.x = x11 - x00;
				e2.y = y11 - y00;
				e2.z = z11 - z00;

				CROSS(t1norm, e1, e2);
				NORMALIZE(t1norm);

				e1.x = x01 - x11;
				e1.y = y01 - y11;
				e1.z = z01 - z11;
				e2.x = x00 - x11;
				e2.y = y00 - y11;
				e2.z = z00 - z11;

				CROSS(t2norm, e1, e2);
				NORMALIZE(t2norm);

				// if you do smoothed normals, it should go here

				if (swap_zup) {
					float t = t1norm.z;
					t1norm.z = t1norm.y;
					t1norm.y = t;
					t = t2norm.z;
					t2norm.z = t2norm.y;
					t2norm.y = t;
				}

				char line[100];
				sprintf_s(line, FORMATTED_POSITION, x00, y00, z00);
				std::string v1pos = std::string(line);
				memset(line, 0, sizeof(line));
				sprintf_s(line, FORMATTED_POSITION, x10, y10, z10);
				std::string v2pos = std::string(line);
				memset(line, 0, sizeof(line));
				sprintf_s(line, FORMATTED_POSITION, x11, y11, z11);
				std::string v3pos = std::string(line);
				memset(line, 0, sizeof(line));
				sprintf_s(line, FORMATTED_POSITION, x01, y01, z01);
				std::string v4pos = std::string(line);

				get_texcoord(texture_data, &texcoord, x, y, h, swap_uv);

				// tex00
				memset(line, 0, sizeof(line));
				sprintf_s(line, FORMATTED_TEXCOORD, texcoord.x, texcoord.y);
				std::string v1tex = std::string(line);
				// tex10
				memset(line, 0, sizeof(line));
				sprintf_s(line, FORMATTED_TEXCOORD, texcoord.x + tex_size, texcoord.y);
				std::string v2tex = std::string(line);
				// tex11
				memset(line, 0, sizeof(line));
				sprintf_s(line, FORMATTED_TEXCOORD, texcoord.x + tex_size, texcoord.y + tex_size);
				std::string v3tex = std::string(line);
				// tex01
				memset(line, 0, sizeof(line));
				sprintf_s(line, FORMATTED_TEXCOORD, texcoord.x, texcoord.y + tex_size);
				std::string v4tex = std::string(line);

				get_normal(data, &t1norm, x, y, x + density, y, x + density, y + density, h);
				get_normal(data, &t2norm, x + density, y + density, x, y + density, x, y, h);

				// getting smooth normals in here is going to be a bit more work but hopefully not too much
				memset(line, 0, sizeof(line));
				sprintf_s(line, FORMATTED_NORMAL, t1norm.x, t1norm.y, t1norm.z);
				std::string normt1 = std::string(line);

				memset(line, 0, sizeof(line));
				sprintf_s(line, FORMATTED_NORMAL, t2norm.x, t2norm.y, t2norm.z);
				std::string normt2 = std::string(line);

				// would use a four-vertex face for these but trying to do flat normals with that doesnt
				// seem to work very well
				if (all || (z00 >= 0 || z10 >= 0 || z11 >= 0)) {
					*content << "f " <<
						position_map[v1pos] + 1 << "/" << texture_map[v1tex] + 1 << "/" << normal_map[normt1] + 1 << " " <<
						position_map[v2pos] + 1 << "/" << texture_map[v2tex] + 1 << "/" << normal_map[normt1] + 1 << " " <<
						position_map[v3pos] + 1 << "/" << texture_map[v3tex] + 1 << "/" << normal_map[normt1] + 1 << " \r\n";
				}
				if (all || (z11 >= 0 || z01 >= 0 || z00 >= 0)) {
					*content << "f " <<
						position_map[v3pos] + 1 << "/" << texture_map[v3tex] + 1 << "/" << normal_map[normt2] + 1 << " " <<
						position_map[v4pos] + 1 << "/" << texture_map[v4tex] + 1 << "/" << normal_map[normt2] + 1 << " " <<
						position_map[v1pos] + 1 << "/" << texture_map[v1tex] + 1 << "/" << normal_map[normt2] + 1 << "\r\n";
				}
			}
		}

#undef FORMATTED_POSITION
#undef FORMATTED_TEXCOORD
#undef FORMATTED_NORMAL
	}

	void generate_internal(float* out) {
		float* data = terrainops::data;
		int w = terrainops::data_size.a;
		int h = terrainops::data_size.b;
		float* vertex = terrainops::vertex;

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

	inline void add_z(float* data, float* vertex, int x, int y, int w, int h, float value) {
		set_z(data, vertex, x, y, w, h, value + get_z(data, x, y, h));
	}

	inline void set_z(float* data, float* vertex, int x, int y, int w, int h, float value) {
		data[DATA_INDEX(x, y, h)] = value;
		
		auto get_vertex_index = [](int cell_size, int x, int y, int w, int h, int vertex) {
			int column_size = cell_size * h;
			Vector2 base_chunk{}, local_coordinates{};
			base_chunk.a = x / cell_size;
			base_chunk.b = y / cell_size;
			local_coordinates.a = x % cell_size;
			local_coordinates.b = y % cell_size;
			int local_chunk_width = std::min(cell_size, w - base_chunk.a * cell_size);
			int local_chunk_height = std::min(cell_size, h - base_chunk.b * cell_size);
			int column_address = base_chunk.a * column_size;
			int chunk_address = column_address + base_chunk.b * cell_size /* dont use the local chunk height here */ * local_chunk_width;
			int base_address = chunk_address + local_coordinates.a * local_chunk_height + local_coordinates.b;
			return (base_address * 6 + vertex) * 3;
		};

		if (x > 0 && y > 0) {
			vertex[get_vertex_index(terrainops::cell_size, x - 1, y - 1, w, h, 2) + 2] = value;
			vertex[get_vertex_index(terrainops::cell_size, x - 1, y - 1, w, h, 3) + 2] = value;
		}

		if (x < w && y > 0) {
			vertex[get_vertex_index(terrainops::cell_size, x, y - 1, w, h, 4) + 2] = value;
		}

		if (x > 0 && y < h - 1) {
			vertex[get_vertex_index(terrainops::cell_size, x - 1, y, w, h, 1) + 2] = value;
		}

		if (x < w && y < h - 1) {
			vertex[get_vertex_index(terrainops::cell_size, x, y, w, h, 0) + 2] = value;
			vertex[get_vertex_index(terrainops::cell_size, x, y, w, h, 5) + 2] = value;
		}
	}

	void invoke_deformation(bool calculate_average, void(*callback)(float*, float*, int, int, int, int, float, float, float)) {
		float* data = terrainops::data;
		int w = terrainops::data_size.a;
		int h = terrainops::data_size.b;
		float* vertex = terrainops::vertex;

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

		unsigned int pixel;
		float average = 0;

		// if the entire region is out of bounds, dont bother
		if (x1 >= w - 1 || x2 <= 0 || y1 >= h - 1 || y2 <= 0) {
			return;
		}

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
				pixel = spriteops::sample_unfiltered(brush, bw, bh, ((float)(i - bx1a)) / (bx2a - bx1a), ((float)(j - by1a)) / (by2a - by1a));
				callback(data, vertex, w, h, i, j, (pixel & 0x000000ff) / 255.0f, velocity, average);
			}
		}
	}

	void get_normal(float* data, Vector3* results, int x1, int y1, int x2, int y2, int x3, int y3, int h) {
		float z1 = get_z(data, x1, y1, h);
		float z2 = get_z(data, x2, y2, h);
		float z3 = get_z(data, x3, y3, h);

		Vector3 e1{ }, e2{ };
		e1.x = (float)(x2 - x1);
		e1.y = (float)(y2 - y1);
		e1.z = (float)(z2 - z1);
		e2.x = (float)(x3 - x1);
		e2.y = (float)(y3 - y1);
		e2.z = (float)(z3 - z1);

		CROSS(*results, e1, e2);
		NORMALIZE(*results);
	}

	inline void get_texcoord(unsigned int* texture_data, Vector2* results, int x, int y, int h, bool swap_uvs) {
		unsigned int tex = texture_data[DATA_INDEX(x + 0, y + 0, h)];

		results->x = (tex & 0xff) / 256.0f;
		results->y = ((tex >> 8) & 0xff) / 256.0f;
		if (swap_uvs)
			results->y = 1.0f - results->y;
	}

	inline unsigned int get_colour(unsigned int* colour_data, int x, int y, int w, int h, float scale) {
		return spriteops::sample_unfiltered(colour_data, (int)(w * scale), (int)(h * scale), ((float)x) / w, ((float)y) / h) | 0xff000000;
	}

	inline bool ray_tri(Vector3* start, Vector3* direction, Vector3* a, Vector3* b, Vector3* c) {
		Vector3 edge1{}, edge2{}, tvec{}, pvec{}, qvec{};
		float det, inv_det;

		/* find vectors for two edges sharing vert0 */
		SUB(edge1, (*b), (*a));
		SUB(edge2, (*c), (*a));

		/* begin calculating determinant - also used to calculate U parameter */
		CROSS(pvec, (*direction), edge2);

		/* if determinant is near zero, ray lies in plane of triangle */
		det = DOT(edge1, pvec);

		/* calculate distance from vert0 to ray origin */
		SUB(tvec, (*start), (*a));
		inv_det = 1.0f / det;

		Vector3 out{};

		if (det > 0) {
			/* calculate U parameter and test bounds */
			out.y = DOT(tvec, pvec);
			if (out.y < 0.0 || out.y > det)
				return 0;

			/* prepare to test V parameter */
			CROSS(qvec, tvec, edge1);

			/* calculate V parameter and test bounds */
			out.z = DOT((*direction), qvec);
			if (out.z < 0.0 || out.y + out.z > det)
				return 0;

		} else if (det < 0) {
			/* calculate U parameter and test bounds */
			out.y = DOT(tvec, pvec);
			if (out.y > 0.0 || out.y < det)
				return 0;

			/* prepare to test V parameter */
			CROSS(qvec, tvec, edge1);

			/* calculate V parameter and test bounds */
			out.z = DOT((*direction), qvec);
			if (out.z > 0.0 || out.y + out.z < det)
				return 0;
		} else return 0;  /* ray is parallell to the plane of the triangle */

		/* calculate t, ray intersects triangle */
		terrainops::cursor_output[0] = DOT(edge2, qvec) * inv_det;
		terrainops::cursor_output[1] = out.y * inv_det;
		terrainops::cursor_output[2] = out.z * inv_det;

		return 1;
	}
}