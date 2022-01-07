#include <algorithm>
#include "terrainops.h"

namespace terrainops {
	bool save_swap_zup = false;
	bool save_swap_uv = false;
	bool save_centered = false;
	int save_density = 1;
	float save_width = 1;
	float save_height = 1;
	float save_scale = 1;

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

	void build_settings(bool swap_zup, bool swap_uv, bool centered, int density, float width, float height, float scale) {
		terrainops::save_swap_zup = swap_zup;
		terrainops::save_swap_uv = swap_uv;
		terrainops::save_scale = centered;
		terrainops::save_density = density;
		terrainops::save_width = width;
		terrainops::save_height = height;
		terrainops::save_scale = scale;
	}

	long build(float* data, float* out, int len) {
		int density = terrainops::save_density;
		float w = terrainops::save_width;
		float h = terrainops::save_height;
		float xoff = terrainops::save_centered ? (-w / 2) : 0;
		float yoff = terrainops::save_centered ? (-h / 2) : 0;
		float scale = terrainops::save_scale;

		float x00, x01, x10, x11, y00, y01, y10, y11, z00, z01, z10, z11;
		float c00, c01, c10, c11;
		float xt00, xt01, xt10, xt11, yt00, yt01, yt10, yt11;

		for (int i = 0; i < w; i++) {
			for (int j = 0; j < h; j++) {
				x00 = i, y00 = j;
				x00 = i, y00 = j;
				z00 = get_z(data, x00, y00);
				x01 = i, y01 = j + density;
				x01 = i, y01 = j + density;
				z01 = get_z(data, x01, y01);
				x10 = i + density, y10 = j;
				x10 = i + density, y10 = j;
				z10 = get_z(data, x10, y10);
				x11 = i + density, y11 = j + density;
				x11 = i + density, y11 = j + density;
				z11 = get_z(data, x11, y11);
			}
		}
		return 0L;
	}

	float get_z(float* data, int x, int y) {
		return data[x * ((int)terrainops::save_height + 1) + y];
	}
}