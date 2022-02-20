#include "terrainops.h"
#include <main/dragomath.h>
#include <MeshOperations/building.h>

namespace terrainops {
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

		for (int x = x1; x < x2; x += density) {
			for (int y = y1; y < y2; y += density) {
				x00 = (float)x;
				y00 = (float)y;
				z00 = get_z(data, x, y, h);

				x01 = (float)x;
				y01 = (float)std::min(y + density, h);
				z01 = get_z(data, x, std::min(y + density, h - 1), h);

				x10 = (float)std::min(x + density, w);
				y10 = (float)y;
				z10 = get_z(data, std::min(x + density, w - 1), y, h);

				x11 = (float)std::min(x + density, w);
				y11 = (float)std::min(y + density, h);
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

				terrainops::get_texcoord(texture_data, &texcoord, x, y, h, swap_uv);

				c00 = terrainops::get_colour(colour_data, x, y, w, h, color_scale);
				c01 = terrainops::get_colour(colour_data, x, y + density, w, h, color_scale);
				c10 = terrainops::get_colour(colour_data, x + density, y, w, h, color_scale);
				c11 = terrainops::get_colour(colour_data, x + density, y + density, w, h, color_scale);

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

		for (int x = x1; x <= x2; x += density) {
			for (int y = y1; y <= y2; y += density) {
				char line[100]{ };

				if (swap_zup) {
					sprintf_s(line, FORMATTED_POSITION,
						std::min((float)(w - 1), x + xoff) * scale,
						get_z(data, std::min(w - 1, x), std::min(h - 1, y), h) * scale,
						std::min((float)h, y + yoff) * scale
					);
				} else {
					sprintf_s(line, FORMATTED_POSITION,
						std::min((float)w, x + xoff) * scale,
						std::min((float)h, y + yoff) * scale,
						get_z(data, std::min(w - 1, x), std::min(h - 1, y), h) * scale
					);
				}

				position_hash = std::string(line);
				position_map.insert(std::pair(position_hash, (int)position_map.size()));

				// the final column/row of positions in a chunk are only needed to write out the positions
				if (x >= x2 - density || y >= y2 - density) continue;

				terrainops::get_texcoord(texture_data, &texcoord, x, y, h, swap_uv);

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

				terrainops::get_normal(data, &t1norm, x, y, x + density, y, x + density, y + density, h);
				terrainops::get_normal(data, &t2norm, x + density, y + density, x, y + density, x, y, h);

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

		for (int x = x1; x < x2; x += density) {
			for (int y = y1; y < y2; y += density) {
				float x00 = (float)x;
				float y00 = (float)y;
				float z00 = get_z(data, x, y, h);

				float x01 = (float)x;
				float y01 = (float)std::min(y + density, h);
				float z01 = get_z(data, x, std::min(y + density, h - 1), h);

				float x10 = (float)std::min(x + density, w);
				float y10 = (float)y;
				float z10 = get_z(data, std::min(x + density, w - 1), y, h);

				float x11 = (float)std::min(x + density, w);
				float y11 = (float)std::min(y + density, h);
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

				terrainops::get_texcoord(texture_data, &texcoord, x, y, h, swap_uv);

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
	
	void build_write_vertex_vbuff(
		float* out, std::stringstream* content, unsigned int format, long long* address,
		float x, float y, float z,
		float nx, float ny, float nz,
		float u, float v,
		unsigned int c,
		float tx, float ty, float tz,
		float bx, float by, float bz,
		float bc1, float bc2, float bc3
	) {
		if (format & VFX_POSITION_2D) {
			out[(*address)++] = x;
			out[(*address)++] = y;
		}
		if (format & VFX_POSITION_3D) {
			out[(*address)++] = x;
			out[(*address)++] = y;
			out[(*address)++] = z;
		}
		if (format & VFX_NORMAL) {
			out[(*address)++] = nx;
			out[(*address)++] = ny;
			out[(*address)++] = nz;
		}
		if (format & VFX_TEXCOORD) {
			out[(*address)++] = u;
			out[(*address)++] = v;
		}
		if (format & VFX_COLOUR) {
			((unsigned int*)out)[(*address)++] = c;
		}
		if (format & VFX_TANGENT) {
			out[(*address)++] = tx;
			out[(*address)++] = ty;
			out[(*address)++] = tz;
		}
		if (format & VFX_BITANGENT) {
			out[(*address)++] = bx;
			out[(*address)++] = by;
			out[(*address)++] = bz;
		}
		if (format & VFX_BARYCENTRIC) {
			out[(*address)++] = bc1;
			out[(*address)++] = bc2;
			out[(*address)++] = bc3;
		}
		if (format & VFX_SMALL_NORMAL) {
			nx = ADJUST(nx, 0.0f, 255.0f, -1.0f, 1.0f);
			ny = ADJUST(ny, 0.0f, 255.0f, -1.0f, 1.0f);
			nz = ADJUST(nz, 0.0f, 255.0f, -1.0f, 1.0f);
			((unsigned int*)out)[(*address)++] = (unsigned int)(nx + ny * 256.0 + nz * 65536.0);
		}
		if (format & VFX_SMALL_TANGENT) {
			tx = ADJUST(tx, 0.0f, 255.0f, -1.0f, 1.0f);
			ty = ADJUST(ty, 0.0f, 255.0f, -1.0f, 1.0f);
			tz = ADJUST(tz, 0.0f, 255.0f, -1.0f, 1.0f);
			((unsigned int*)out)[(*address)++] = (unsigned int)(tx + ty * 256.0 + tz * 65536.0);
		}
		if (format & VFX_SMALL_BITANGENT) {
			bx = ADJUST(bx, 0.0f, 255.0f, -1.0f, 1.0f);
			by = ADJUST(by, 0.0f, 255.0f, -1.0f, 1.0f);
			bz = ADJUST(bz, 0.0f, 255.0f, -1.0f, 1.0f);
			((unsigned int*)out)[(*address)++] = (unsigned int)(bx + by * 256.0 + bz * 65536.0);
		}
		if (format & VFX_SMALL_TEXCOORD) {
			u = floor(u * 255.0f);
			v = floor(v * 255.0f);
			((unsigned int*)out)[(*address)++] = (unsigned int)(u + v * 256.0);
		}
		if (format & VFX_SMALL_NORMAL_PAL) {
			nx = ADJUST(nx, 0.0f, 255.0f, -1.0f, 1.0f);
			ny = ADJUST(ny, 0.0f, 255.0f, -1.0f, 1.0f);
			nz = ADJUST(nz, 0.0f, 255.0f, -1.0f, 1.0f);
			u = floor(u * 255.0f);
			((unsigned int*)out)[(*address)++] = (unsigned int)(nx + ny * 256.0 + nz * 65536.0 + u * 16777216.0);
		}
	}

	void build_write_vertex_d3d(
		float* out, std::stringstream* content, unsigned int format, long long* address,
		float x, float y, float z,
		float nx, float ny, float nz,
		float u, float v,
		unsigned int c,
		float tx, float ty, float tz,
		float bx, float by, float bz,
		float bc1, float bc2, float bc3
	) {
		char line[160];
		sprintf_s(line, "9 %.1f %.1f %.5f %.3f %.3f %.3f %.6f %.6f %d %.3f\r\n", x, y, z, nx, ny, nz, u, v, c & 0x00ffffff, (c >> 24) / 255.0);
		*content << std::string(line);
	}

	void build_setup_vbuff(float* out) {

	}

	void build_cleanup_vbuff(float* out, long long* length, int) {
		*length = (long long)FLOATS2BYTES(*length);
	}

	void build_setup_d3d(float* out, std::stringstream* content) {

	}

	void build_cleanup_d3d(float* out, std::stringstream* content, long long* length, int vertices) {
		std::stringstream header, footer;
		header << std::format("100\r\n{}\r\n0 4\r\n", vertices + 2);
		footer << "0\r\n";

		std::string result = header.str() + content->str() + footer.str();
		*length = (int)result.length();
		result.copy((char*)out, *length);
	}

	void build_setup_obj(float* out, std::stringstream* content) {
		*content << "# Terrain generated by dragonite's terrain editor: https://dragonite.itch.io/terrain\r\n" <<
			"mtllib terrian.mtl\r\n" <<
			"usemtl terrain\t\n\r\n";
	}

	void build_cleanup_obj(float* out, std::stringstream* content, long long* length, int vertices) {
		std::string result = content->str();
		long long bytes = (int)result.length();
		*length = (int)result.length();
		result.copy((char*)out, *length);
	}
}